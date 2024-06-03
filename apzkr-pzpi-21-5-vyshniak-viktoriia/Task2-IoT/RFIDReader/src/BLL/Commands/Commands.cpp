#include "Commands.h"
#include <BLL/Helpers/Memory/MemoryHelper.h>

void configureRFIDReader(ArduinoJson::JsonDocument& doc) {
    String newSsid = doc["WifiSettings"]["Ssid"];
    String newPassword = doc["WifiSettings"]["Password"];
    String newCallbackUrl = doc["WifiSettings"]["CallbackUrl"];
    String newUserId = doc["UserId"];

    EEPROM.begin(eepromSize);
    for (int i = 0; i < 160; i++) {
    EEPROM.write(i, 0);
    }

    Serial.println("writing eeprom ssid:");
    writeInMemory(0, newSsid);

    Serial.println("writing eeprom pass:");
    writeInMemory(32, newPassword);

    Serial.println("writing eeprom callback url:");
    writeInMemory(64, newCallbackUrl);

    Serial.println("writing eeprom user id:");
    writeInMemory(128, newUserId);

    EEPROM.commit();
    EEPROM.end();

    ESP.restart();
}
