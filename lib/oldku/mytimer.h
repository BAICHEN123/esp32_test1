#ifndef _MYTIMER_H
#define _MYTIMER_H
//#include <ESP8266WiFi.h>
#include <Arduino.h>


#ifndef timercallback
typedef void (*timercallback)();
#endif

#ifndef uint8_t
#define uint8_t unsigned char
#endif
#ifndef uint16_t
#define uint16_t unsigned short
#endif

struct MyTime{
	uint8_t run_fig;//计算闰年的
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t week;
	uint8_t hour;
	uint8_t minute;//分
	uint8_t sec;//秒
};
extern struct MyTime Now;

//服务器每隔 1min 就会发来时间
void next_sec(struct MyTime * now);

//将服务器发来的时间，转换
void str_get_time(struct MyTime * now,char * data_str);

#ifdef ESP8266
void set_timer1_s(timercallback userFunc, double time_s);
void set_timer1_ms(timercallback userFunc, uint32_t time_ms);
/*微秒定时器 定时中断函数里禁止调用 delay 进行延时操作，调用必暴毙
userFunc 需要定时调用执行的函数名*/
void set_timer1_us(timercallback userFunc, uint32_t time_us);

#endif
#endif