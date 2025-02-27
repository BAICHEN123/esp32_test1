#include <Arduino.h>
#include <WiFi.h>
#include <pins_arduino.h>
#include <ESP32Servo.h>
#include <LittleFS.h>

#include "myconstant.h"
#include "DoServerMessage.h"

#define LED_PIN 2

#define DUOJI_PIN 13 // �滻Ϊʵ�ʵĶ������

Servo myServo;

void duoji_setup()
{
  myServo.attach(DUOJI_PIN); // ���Ӷ���ź�����
  myServo.write(90);          // ��ʼλ��Ϊ 0 ��
  delay(1000);               // �ȴ���������ʼλ��
}

void duoji_loop(int len1)
{
  // int len1 = 10;
  const int timeout = 20;
  for (int i = len1; i > 0; i = i - 1)
  {
    myServo.write(0); // ˳ʱ����ת 90 ��
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
    myServo.write(90); // ��ʱ����ת 90 ��
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
  // ��ʼ�� GPIO2 ����Ϊ���ģʽ
  pinMode(LED_PIN, OUTPUT);
  duoji_setup();
}

void loop()
{
  const int timeout_led = 200;
  // ���� LED

  // ���� LED
  digitalWrite(LED_PIN, HIGH);
  delay(timeout_led); // �ӳ� 1 ��
  // Ϩ�� LED
  digitalWrite(LED_PIN, LOW);
  delay(timeout_led); // �ӳ� 1 ��


  duoji_loop(1);
  
  // for(int i = 0; i < 5; i++){
  //   // Ϩ�� LED
  //   digitalWrite(LED_PIN, LOW);
  //   delay(timeout_led); // �ӳ� 1 ��
  //   duoji_loop(i);
  //   digitalWrite(LED_PIN, HIGH);
  //   delay(timeout_led); // �ӳ� 1 ��
  // }

  // ���� LED
  digitalWrite(LED_PIN, HIGH);
  delay(timeout_led); // �ӳ� 1 ��
  // Ϩ�� LED
  digitalWrite(LED_PIN, LOW);
  delay(timeout_led); // �ӳ� 1 ��
  while (1)
    ;
}
