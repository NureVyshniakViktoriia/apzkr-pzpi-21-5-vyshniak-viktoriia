#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <Arduino.h>
#include <ArduinoJson.h>

class Notification {
public:
    Notification(int userId = 0, String petRfid = "");

    String toJson();

private:
    int userId;
    String petRfid;
};

#endif
