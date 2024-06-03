#include "BaseArduinoResponse.h"

BaseArduinoResponse::BaseArduinoResponse(bool isSuccess, String errorCode) {
    this->isSuccess = isSuccess;
    this->errorCode = errorCode;
}
