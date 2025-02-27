#include <Arduino.h>
#include <WiFi.h>
#include <pins_arduino.h>
#include <ESP32Servo.h>
#include <LittleFS.h>

#include "myconstant.h"
#include "DoServerMessage.h"

#define LED_PIN 2

#define DUOJI_PIN 13 // 替换为实际的舵机引脚

Servo myServo;

void duoji_setup()
{
  myServo.attach(DUOJI_PIN); // 连接舵机信号引脚
  myServo.write(90);          // 初始位置为 0 度
  delay(1000);               // 等待舵机到达初始位置
}

void duoji_loop(int len1)
{
  // int len1 = 10;
  const int timeout = 20;
  for (int i = len1; i > 0; i = i - 1)
  {
    myServo.write(0); // 顺时针旋转 90 度
    delay(timeout);
    if (i % 2 == 0)
    {
      digitalWrite(LED_PIN, LOW);
    }
    else
    {
      digitalWrite(LED_PIN, HIGH);
    }
  }
  delay(1300);
  for (int i = len1; i > 0; i = i - 1)
  {
    myServo.write(90); // 逆时针旋转 90 度
    delay(timeout);
    if (i % 2 == 0)
    {
      digitalWrite(LED_PIN, LOW);
    }
    else
    {
      digitalWrite(LED_PIN, HIGH);
    }
  }
}

void setup()
{
  // 初始化 GPIO2 引脚为输出模式
  pinMode(LED_PIN, OUTPUT);
  duoji_setup();
}

void loop()
{
  const int timeout_led = 200;
  // 点亮 LED

  // 点亮 LED
  digitalWrite(LED_PIN, HIGH);
  delay(timeout_led); // 延迟 1 秒
  // 熄灭 LED
  digitalWrite(LED_PIN, LOW);
  delay(timeout_led); // 延迟 1 秒


  duoji_loop(1);
  
  // for(int i = 0; i < 5; i++){
  //   // 熄灭 LED
  //   digitalWrite(LED_PIN, LOW);
  //   delay(timeout_led); // 延迟 1 秒
  //   duoji_loop(i);
  //   digitalWrite(LED_PIN, HIGH);
  //   delay(timeout_led); // 延迟 1 秒
  // }

  // 点亮 LED
  digitalWrite(LED_PIN, HIGH);
  delay(timeout_led); // 延迟 1 秒
  // 熄灭 LED
  digitalWrite(LED_PIN, LOW);
  delay(timeout_led); // 延迟 1 秒
  while (1)
    ;
}
