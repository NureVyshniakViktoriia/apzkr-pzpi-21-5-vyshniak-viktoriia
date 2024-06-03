#ifndef COMMAND_HELPER_H
#define COMMAND_HELPER_H

#include <Arduino.h>
#include <ArduinoJson.h>

void configurePetDevice(JsonDocument& doc);
String getCurrentLocation();

#endif
