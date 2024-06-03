#include "WiFiHelper.h"
#include <Domain/Models/Responses/ArduinoResponse.h>
#include <Domain/Configs/ServerCert.h>
#include <Domain/Configs/ServerKey.h>
#include <BLL/Helpers/JsonHelper/JsonHelper.h>
#include <Domain/Enums/CommandType.h>
#include <BLL/Services/TemperatureMonitorService/TemperatureMonitorService.h>
#include <BLL/Commands/Commands.h>

void connectToWiFi(TrivialCB httpHandler) {
    Serial.println("Connecting to WiFi");

    const char* wifi = ssid.c_str();
    const char* pass = password.c_str();

    Serial.println(wifi);
    Serial.println(pass);
  
    WiFi.begin(wifi, pass);

    int attemptCount = 0;
    while (WiFi.status() != WL_CONNECTED && attemptCount < ATTEMPT_COUNT) {
        delay(1000);
        attemptCount++;
    }

    String jsonResponse;
    if (WiFi.status() != WL_CONNECTED) {
        ArduinoResponse response(false, "INVALID_WIFI_CREDS", "");
        jsonResponse = response.toJson();
    } else {
        ArduinoResponse response(true, "", WiFi.localIP().toString());
        jsonResponse = response.toJson();
    }

    Serial.println(jsonResponse);

    configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");
    server.getServer().setRSACert(new BearSSL::X509List(serverCert), new BearSSL::PrivateKey(serverKey));

    server.on("/data", HTTP_POST, httpHandler);
    server.begin();
    Serial.println("Server listening");
}
