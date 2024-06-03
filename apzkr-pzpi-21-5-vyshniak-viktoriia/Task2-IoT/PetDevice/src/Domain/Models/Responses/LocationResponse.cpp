#include "LocationResponse.h"

LocationResponse::LocationResponse(bool isSuccess, String errorCode, double latitude, double longtitude)
    : BaseArduinoResponse(isSuccess, errorCode) {
    this->latitude = latitude;
    this->longtitude = longtitude;
}

String LocationResponse::toJson() {
    JsonDocument doc;
    doc["IsSuccess"] = this->isSuccess;
    doc["ErrorCode"] = this->errorCode;
    doc["Latitude"] = this->latitude;
    doc["Longtitude"] = this->longtitude;

    String jsonString;
    serializeJson(doc, jsonString);

    return jsonString;
}
