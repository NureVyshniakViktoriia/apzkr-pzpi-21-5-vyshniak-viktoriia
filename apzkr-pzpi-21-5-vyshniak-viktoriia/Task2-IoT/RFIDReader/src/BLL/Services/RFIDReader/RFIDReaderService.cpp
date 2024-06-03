#include "RfidReaderService.h"
#include <ESP8266HTTPClient.h>

RFIDReaderService::RFIDReaderService(MFRC522 &rfid, String callbackUrl, String userId)
  : rfid(rfid), callbackUrl(callbackUrl), userId(userId) {}

String RFIDReaderService::getDomainFromCallbackUrl() {
    Serial.print("Hello from refidreader: ");
    Serial.println(callbackUrl);
    String ipAddress = "";
    int colonIndex = callbackUrl.indexOf(':');
    
    if (colonIndex != -1) {
        ipAddress = callbackUrl.substring(colonIndex + 3, callbackUrl.indexOf(':', colonIndex + 3));
        Serial.print("IP address: ");
        Serial.println(ipAddress);
    } else {
        Serial.println("Invalid URL format");
    }

    return ipAddress;
}

String RFIDReaderService::readRFID() {
    if (!rfid.PICC_IsNewCardPresent()) {
        return "";
    }

    if (!rfid.PICC_ReadCardSerial()) {
        return "";
    }

    String tag = "";
    for (int i = 0; i < rfid.uid.size; i++) {
        tag += rfid.uid.uidByte[i];
    }

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();

    return tag;
}

void RFIDReaderService::processTag() {
    String tag = readRFID();
    if (tag == "") {
        return;
    }

    WiFiClientSecure client;
    String serverDomain = getDomainFromCallbackUrl();
    client.setInsecure();

    if (client.connect(serverDomain, 7114)){
        Serial.println("Connected to server");
    } else {
        Serial.println("ERROR connection to server");
    }

    HTTPClient https;

    https.begin(client, callbackUrl);
    https.addHeader("Content-Type", "application/json");

    Notification notification(userId.toInt(), tag);
    String data = notification.toJson();

    int httpsResponseCode = https.POST(data);
    Serial.print("HTTP status code = ");
    Serial.println(httpsResponseCode);   

    https.end();
}

void RFIDReaderService::setCallbackUrl(String newCallbackUrl) {
    this->callbackUrl = newCallbackUrl;
}

void RFIDReaderService::setUserId(int newUserId) {
    this->userId = String(newUserId);
}