#ifndef WIFI_HELPER_H
#define WIFI_HELPER_H

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266WebServerSecure.h>

inline String ssid; //= "TP-Link_701B";
inline String password; //= "35068839";
inline String callbackUrl;
inline int userId = 0;
inline const int ATTEMPT_COUNT = 10;

void connectToWiFi();

#endif