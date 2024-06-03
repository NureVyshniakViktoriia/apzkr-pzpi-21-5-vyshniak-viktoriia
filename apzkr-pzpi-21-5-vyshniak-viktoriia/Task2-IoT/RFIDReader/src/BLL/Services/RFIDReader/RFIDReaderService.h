#ifndef RFID_SERVICE_H
#define RFID_SERVICE_H

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <Domain/Models/Notification/Notification.h>
#include <MFRC522.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <SPI.h>

class RFIDReaderService {
  public:
    RFIDReaderService(MFRC522 &rfid, String callbackUrl = "", String userId = "");
    String getDomainFromCallbackUrl();
    String readRFID();
    void processTag();
    void setCallbackUrl(String newCallbackUrl);
    void setUserId(int newUserId);

  private:
    MFRC522 &rfid;
    String callbackUrl;
    String userId;
};

#endif
