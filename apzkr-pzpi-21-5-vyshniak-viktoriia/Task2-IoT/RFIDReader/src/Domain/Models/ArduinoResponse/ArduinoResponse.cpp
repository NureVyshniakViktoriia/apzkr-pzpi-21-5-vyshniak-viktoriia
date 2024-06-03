#include "ArduinoResponse.h"

ArduinoResponse::ArduinoResponse(bool isSuccess, String errorCode, String payload) {
    this->isSuccess = isSuccess;
    this->errorCode = errorCode;
    this->payload = payload;
}

String ArduinoResponse::toJson() {
    JsonDocument doc;
    doc["IsSuccess"] = this->isSuccess;
    doc["ErrorCode"] = this->errorCode;
    doc["Payload"] = this->payload;

    String jsonString;
    serializeJson(doc, jsonString);

    return jsonString;
}
