#include "Notification.h"

Notification::Notification(int userId, String petRfid) {
    this->userId = userId;
    this->petRfid = petRfid;
}

String Notification::toJson() {
    JsonDocument doc;
    doc["UserId"] = this->userId;
    doc["PetRFID"] = this->petRfid;

    String jsonString;
    serializeJson(doc, jsonString);

    return jsonString;
}
