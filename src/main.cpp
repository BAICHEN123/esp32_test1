#include <Arduino.h>
#include <WiFi.h>
#include <pins_arduino.h>
#include <ESP32Servo.h>
#include <LittleFS.h>

#include "myconstant.h"
#include "DoServerMessage.h"

#define LED_PIN 2

#define DUOJI_PIN 13  // �滻Ϊʵ�ʵĶ������

Servo myServo;

void duoji_setup() {
  myServo.attach(DUOJI_PIN);  // ���Ӷ���ź�����
  myServo.write(0);  // ��ʼλ��Ϊ 0 ��
  delay(1000);  // �ȴ���������ʼλ��
}

void duoji_loop() {
  myServo.write(90);  // ˳ʱ����ת 90 ��
  delay(50);  // ͣ�� 50 ����
  myServo.write(0);  // ��ʱ����ת 90 ��
  delay(50);  // ͣ�� 50 ����
  while(1);
}


void setup() {
  // ��ʼ�� GPIO2 ����Ϊ���ģʽ
  pinMode(LED_PIN, OUTPUT);
  duoji_setup();
}

void loop() {
  // ���� LED
  digitalWrite(LED_PIN, HIGH);
  delay(1000); // �ӳ� 1 ��
  // Ϩ�� LED
  digitalWrite(LED_PIN, LOW);
  delay(1000); // �ӳ� 1 ��

  // duoji_loop();


  // ���� LED
  digitalWrite(LED_PIN, HIGH);
  delay(1000); // �ӳ� 1 ��
  // Ϩ�� LED
  digitalWrite(LED_PIN, LOW);
  delay(1000); // �ӳ� 1 ��
}
