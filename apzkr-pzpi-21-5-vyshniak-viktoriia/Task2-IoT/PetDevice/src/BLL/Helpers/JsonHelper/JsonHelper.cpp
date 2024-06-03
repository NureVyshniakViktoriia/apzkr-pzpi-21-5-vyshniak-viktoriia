#include "JsonHelper.h"

void parseJsonData(JsonDocument& doc, String& jsonString) {
    DeserializationError error = deserializeJson(doc, jsonString);

    if (error) {
        Serial.print("JSON parsing failed: ");
        Serial.println(error.c_str());
        return;
    }
}
