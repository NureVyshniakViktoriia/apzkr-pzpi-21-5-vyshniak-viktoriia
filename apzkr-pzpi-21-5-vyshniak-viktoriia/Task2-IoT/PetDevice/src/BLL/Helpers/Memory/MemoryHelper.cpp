#include "MemoryHelper.h"

String readFromMemory(int start, int end) {
    String data = "";
    for (int i = start; i < end; ++i) {
        char readChar = char(EEPROM.read(i));
        if (readChar == 0) {
            break;
        }

        data += readChar;
    }

    return data;
}

void writeInMemory(int start, String data) {
    Serial.println("writing eeprom:");
    for (unsigned int i = 0; i < data.length(); i++)
    {
        EEPROM.write(start + i, data[i]);
        Serial.print("Wrote: ");
        Serial.println(data[i]);
    }
}

void loadSavedConfig(String& ssid, String& password) {
    EEPROM.begin(eepromSize);

    ssid = readFromMemory(0, 32);
    Serial.println("Stored SSID: " + ssid);

    password = readFromMemory(32, 64);
    Serial.println("Stored password: " + password);

    EEPROM.end();
}

void loadSavedConfig(String& ssid, String& password, String& callbackUrl, int& userId) {
    EEPROM.begin(eepromSize);

    ssid = readFromMemory(0, 32);
    Serial.println("Stored SSID: " + ssid);

    password = readFromMemory(32, 64);
    Serial.println("Stored password: " + password);

    callbackUrl = readFromMemory(64, 128);
    Serial.println("Stored callback url: " + callbackUrl);

    String eUserId = readFromMemory(128, 160);
    Serial.println("Stored user id: " + eUserId);
    userId = eUserId.toInt();

    EEPROM.end();
}
