#ifndef WIFI_HELPER_H
#define WIFI_HELPER_H

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266WebServerSecure.h>

inline String ssid; //= "TP-Link_701B";
inline String password; //= "35068839";
inline const int ATTEMPT_COUNT = 5;
inline BearSSL::ESP8266WebServerSecure server(443);

void connectToWiFi(TrivialCB httpHandler);

#endif