#ifndef MEMORY_HELPER_H
#define MEMORY_HELPER_H

#include <Arduino.h>
#include <EEPROM.h>

inline const int eepromSize = 512;

String readFromMemory(int start, int end);
void writeInMemory(int start, String data);

void loadSavedConfig(String& ssid, String& password);
void loadSavedConfig(String& ssid, String& password, String& callbackUrl, int& userId);

#endif
