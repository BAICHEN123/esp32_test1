#include "mytcp.h"
#include <LittleFS.h>
struct Tcp_cache my_tcp_cache; // TCP缓存数组
/*
TCP阻塞，等待 timeout_ms_max ms
看看有没有TCP包返回回来，不会自动断开链接
返回值
0，TCP失效了
1，等到了TCP包
2，没有等到，超时
*/
short timeout_back_ms(WiFiClient *client, unsigned short timeout_ms_max)
{
	unsigned long timeout = millis();
	while (client->available() == 0)
	{
		if (millis() - timeout > timeout_ms_max)
		{
			Serial.println(">>> Client Timeout !");
			return 2;
		}
		if (client->connected() == 0)
		{
			return 0;
		}
	}
	return 1;
}

/*
TCP阻塞，等待 timeout_us_max ms
timeout_us_max 时间间隔为上次调用此函数的的时间
看看有没有TCP包返回回来，不会自动断开链接
返回值
0，TCP失效了
1，等到了TCP包
2，没有等到，超时
*/
short timeout_back_us(WiFiClient *client, unsigned short timeout_us_max)
{
	static unsigned long timenext = micros();
	while (client->available() == 0)
	{
		// 阻塞 timeout_us_max
		if (micros() - timenext > timeout_us_max)
		{
			// Serial.println(">>> Client Timeout !");
			timenext = micros();
			return 2;
		}

		// 链接失效
		if (client->connected() == 0)
		{
			timenext = micros();
			return 0;
		}
	}

	timenext = micros();
	return 1;
}

/*
从TCP连接读取TCP数据，储存在 tcp_data 里，长度为tcp_data_len，每个数据会用“\0”分割
返回本次TCP读取的开始位置，
*/
short get_tcp_data(WiFiClient *client, struct Tcp_cache *tcp_data)
{
	short start_id = tcp_data->len;
	while (client->available() && tcp_data->len < MAX_TCP_DATA - 1)
	{
		tcp_data->data[tcp_data->len++] = static_cast<char>(client->read());
	}
	tcp_data->data[tcp_data->len] = '\0';
	return start_id;
}

/*将打包好的数据，用TCP发送出去*/
short back_send_tcp_of_type(WiFiClient *client, char type, const char *tcp_send_data, int len)
{
	if (len < 0)
	{
		return 1;
	}
	if (client->connected()) // 函数第一次执行loop循环的时候这里可能会出错，因为 client 第一次赋值为局部变量，在setup 中修改他的初始化就可以了
	{
		// 在这里合成需要发送出去的传感器数据？
		unsigned char head[3] = {type, static_cast<unsigned char>(len / 256 % 256), static_cast<unsigned char>(len % 256)};
		client->write(head, 3);
		client->write(tcp_send_data, len);
		client->flush(); // 限制等待时间
		return 1;
	}
	else
	{
		// 结束此次 loop ，到开始位置，重新连接TCP
		client->stop();
		return -1;
	}
}
/*将打包好的数据，用TCP发送出去*/
short back_send_tcp_(WiFiClient *client, char *tcp_send_data, int len)
{
	if (client->connected()) // 函数第一次执行loop循环的时候这里可能会出错，因为 client 第一次赋值为局部变量，在setup 中修改他的初始化就可以了
	{
		// 在这里合成需要发送出去的传感器数据？
		client->write(tcp_send_data, len);
		client->flush(); // 限制等待时间
		return 1;
	}
	else
	{
		// 结束此次 loop ，到开始位置，重新连接TCP
		client->stop();
		return -1;
	}
}

/*将打包好的数据，用TCP发送出去*/
short back_send_tcp(WiFiClient *client, const char *str1)
{
	if (client->connected()) // 函数第一次执行loop循环的时候这里可能会出错，因为 client 第一次赋值为局部变量，在setup 中修改他的初始化就可以了
	{
		// 在这里合成需要发送出去的传感器数据？
		client->write(str1);
		client->flush(); // 限制等待时间
		return 1;
	}
	else
	{
		// 结束此次 loop ，到开始位置，重新连接TCP
		client->stop();
		return -1;
	}
}

uint32_t save_tcp_data_in_file(WiFiClient *client, const char *file_name, uint32_t file_len)
{
	uint32_t len = 0;
	int i = 0;
	int write_ = 0;
	File dataFile = LittleFS.open(file_name, "w");
	Serial.printf(">>> file open file_len %u\r\n", file_len);
	while (client->connected() && len < file_len)
	{
		i = client->read((uint8_t *)my_tcp_cache.data, MAX_TCP_DATA);
		if (i <= 0)
		{
			delay(5);
			continue;
		}
		write_ = dataFile.write((uint8_t *)my_tcp_cache.data, i);
		dataFile.flush();
		if (write_ != i)
		{
			Serial.printf(">>> file write error ! len=%d write_=%d\r\n", len + i, len + write_);
			dataFile.close();

			back_send_tcp_of_type(client, 'u', my_tcp_cache.data, sprintf(my_tcp_cache.data, "%u", len + write_));
			return len + write_;
		}
		len = len + i;
		Serial.printf("i %d  w %d  len%u ", i, write_, len);
		i = 0;
	}
	dataFile.close();
	Serial.printf(">>> file write ok ! len=%d\r\n", len);
	back_send_tcp_of_type(client, 'u', my_tcp_cache.data, sprintf(my_tcp_cache.data, "%u", len));
	return len;
}