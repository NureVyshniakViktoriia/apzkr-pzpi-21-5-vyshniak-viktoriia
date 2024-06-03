#ifndef BASEARDUINORESPONSE_H
#define BASEARDUINORESPONSE_H

#include <Arduino.h>
#include <ArduinoJson.h>

class BaseArduinoResponse {
public:
    BaseArduinoResponse(bool isSuccess = false, String errorCode = "");

protected:
    bool isSuccess;
    String errorCode;
};

#endif
