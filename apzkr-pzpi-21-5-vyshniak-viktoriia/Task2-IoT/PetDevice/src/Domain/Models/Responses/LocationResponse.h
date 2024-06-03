#ifndef LOCATIONRESPONSE_H
#define LOCATIONRESPONSE_H

#include "BaseArduinoResponse.h"
#include <Arduino.h>
#include <ArduinoJson.h>

class LocationResponse : public BaseArduinoResponse {
public:
    LocationResponse(bool isSuccess = false, String errorCode = "", double latitude = 0, double longtitude = 0);
    String toJson();

private:
    double latitude;
    double longtitude;
};

#endif
