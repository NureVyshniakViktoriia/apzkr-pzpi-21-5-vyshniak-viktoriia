#ifndef ARDUINORESPONSE_H
#define ARDUINORESPONSE_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "BaseArduinoResponse.h"

class ArduinoResponse : public BaseArduinoResponse {
public:
    ArduinoResponse(bool isSuccess = false, String errorCode = "", String payload = "");
    String toJson();

private:
    String payload;
};

#endif
