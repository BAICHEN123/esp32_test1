#include <Arduino.h>
#include <WiFi.h>
#include <pins_arduino.h>
#include <ESP32Servo.h>
#include <LittleFS.h>

#include "myconstant.h"
#include "DoServerMessage.h"

#define LED_PIN 2

#define DUOJI_PIN 13  // 替换为实际的舵机引脚

Servo myServo;

void duoji_setup() {
  myServo.attach(DUOJI_PIN);  // 连接舵机信号引脚
  myServo.write(0);  // 初始位置为 0 度
  delay(1000);  // 等待舵机到达初始位置
}

void duoji_loop() {
  myServo.write(90);  // 顺时针旋转 90 度
  delay(50);  // 停顿 50 毫秒
  myServo.write(0);  // 逆时针旋转 90 度
  delay(50);  // 停顿 50 毫秒
  while(1);
}


void setup() {
  // 初始化 GPIO2 引脚为输出模式
  pinMode(LED_PIN, OUTPUT);
  duoji_setup();
}

void loop() {
  // 点亮 LED
  digitalWrite(LED_PIN, HIGH);
  delay(1000); // 延迟 1 秒
  // 熄灭 LED
  digitalWrite(LED_PIN, LOW);
  delay(1000); // 延迟 1 秒

  // duoji_loop();


  // 点亮 LED
  digitalWrite(LED_PIN, HIGH);
  delay(1000); // 延迟 1 秒
  // 熄灭 LED
  digitalWrite(LED_PIN, LOW);
  delay(1000); // 延迟 1 秒
}
