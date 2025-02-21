#ifndef _ESPINC_h
#define _ESPINC_h


#ifdef ESP8266
#include <ESP8266WiFi.h> 
#elif defined(ESP32)
#include <WiFi.h>
#endif

#endif