#include "Commands.h"
#include <BLL/Helpers/Memory/MemoryHelper.h>
#include <Domain/Models/Responses/LocationResponse.h>

void configurePetDevice(JsonDocument & doc) {
    String newSsid = doc["WifiSettings"]["Ssid"];
    String newPassword = doc["WifiSettings"]["Password"];
    Serial.print("New ssid: ");
    Serial.println(newSsid);
    Serial.print("New pass: ");
    Serial.println(newPassword);

    EEPROM.begin(eepromSize);
    for (int i = 0; i < 64; i++) {
        EEPROM.write(i, 0);
    }

    Serial.println("writing eeprom ssid:");
    writeInMemory(0, newSsid);

    Serial.println("writing eeprom pass:");
    writeInMemory(32, newPassword);

    EEPROM.commit();
    EEPROM.end();

    ESP.restart();
}

String getCurrentLocation() {
    LocationResponse response(
        true,
        "",
        30.31,
        50.27
    );

    return response.toJson();
}
