#include <Arduino.h>
#include "BLL/Helpers/Memory/MemoryHelper.h"
#include "BLL/Helpers/WiFiHelper/WiFiHelper.h"
#include <SPI.h>
#include <MFRC522.h>
#include "BLL/Services/RFIDReader/RFIDReaderService.h"
#include "BLL/Helpers/JsonHelper/JsonHelper.h"
#include "Domain/Enums/CommandType.h"
#include "BLL/Commands/Commands.h"

#define RST_PIN D3
#define SS_PIN D4

MFRC522 rfid(SS_PIN, RST_PIN);
RFIDReaderService rfidReaderService(rfid);

void setup() {
    Serial.begin(9600);
    Serial.println("Setup started.");

    loadSavedConfig(ssid, password, callbackUrl, userId);
    rfidReaderService.setCallbackUrl(callbackUrl);
    rfidReaderService.setUserId(userId);
    
    connectToWiFi();
    
    SPI.begin();
    rfid.PCD_Init();
    
    Serial.println("Setup finished.");
}

void loop() {
    if (Serial.available()) {
        String jsonString = Serial.readStringUntil('\n');
        JsonDocument doc;
        parseJsonData(doc, jsonString);

        String commandStr = doc["CommandType"];
        CommandType command = (CommandType)(commandStr.toInt());

        switch(command) {
            case CommandType::ConfigureRFIDReader:
                configureRFIDReader(doc);
                break;
            default:
                break;
        }
    }
    if (WiFi.status() == WL_CONNECTED) {
        MDNS.update();
        rfidReaderService.processTag();
    }
}