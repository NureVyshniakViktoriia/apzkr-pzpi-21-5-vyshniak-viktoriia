#ifndef ARDUINORESPONSE_H
#define ARDUINORESPONSE_H

#include <Arduino.h>
#include <ArduinoJson.h>

class ArduinoResponse {
public:
    ArduinoResponse(
    bool isSuccess = false, 
    String errorCode = "", 
    String payload = "");

    String toJson();

private:
    bool isSuccess;
    String errorCode;
    String payload;
};

#endif
