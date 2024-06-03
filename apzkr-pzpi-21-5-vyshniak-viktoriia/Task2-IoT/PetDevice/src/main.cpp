#include <Arduino.h>
#include <ArduinoJson.h>
#include <BLL/Helpers/Memory/MemoryHelper.h>
#include <BLL/Helpers/WiFiHelper/WiFiHelper.h>
#include <BLL/Services/TemperatureMonitorService/TemperatureMonitorService.h>
#include "BLL/Helpers/JsonHelper/JsonHelper.h"
#include "Domain/Enums/CommandType.h"
#include "Domain/Models/Responses/ArduinoResponse.h"
#include "BLL/Commands/Commands.h"
#include <ESP8266mDNS.h>

NTC_TEMP_CLASS ntc(0);
TemperatureMonitorService tempService;

void handleHttp() {
    String jsonStr = server.arg("plain");
    Serial.println(jsonStr);
    JsonDocument doc;
    parseJsonData(doc, jsonStr);

    String commandStr = doc["CommandType"];
    CommandType command = (CommandType)commandStr.toInt();
    String locale = doc["Locale"];
    String jsonResponse;
    switch(command) {
        case CommandType::GetCurrentTemperature:
            jsonResponse = tempService.getCurrentTemperature(locale, ntc);
            break;
        case CommandType::GetAverageTemperature:
            jsonResponse = tempService.getAverageTemperature(locale, ntc);
            break;
        case CommandType::GetCurrentLocation:
            jsonResponse = getCurrentLocation();
            break;
        default:
            ArduinoResponse response(false, "UNKNOWN_COMMAND", "");
            jsonResponse = response.toJson();
            break;
    }

    Serial.println(jsonResponse);

    server.send(200, "application/json", jsonResponse);
}

void setup() {
    Serial.begin(9600);
    loadSavedConfig(ssid, password);
    connectToWiFi(handleHttp);
    Serial.println("Ended setup...");
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
    server.handleClient();
    MDNS.update();
  }

  while (Serial.available()) {
    String jsonString = Serial.readStringUntil('\n');
    JsonDocument doc;
    parseJsonData(doc, jsonString);

    String commandStr = doc["CommandType"];
    CommandType command = (CommandType)commandStr.toInt();
    switch(command) {
      case CommandType::Configure:
        configurePetDevice(doc);
        break;
      default:
        ArduinoResponse response(false, "UNKOWN_COMMAND", "");
        String jsonResponse = response.toJson();
        Serial.println(jsonResponse);
        break;
    }

    jsonString = "";
  }
}
