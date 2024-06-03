#include "TemperatureMonitorService.h"
#include <BLL/Helpers/TemperatureHelper/TemperatureHelper.h>
#include <Domain/Models/Responses/ArduinoResponse.h>

TemperatureMonitorService::TemperatureMonitorService() {
    this->day = getTodaysDay();
}

void TemperatureMonitorService::addTemperature(double temp) {
    temperatures.push_back(temp);
}

void TemperatureMonitorService::updateDay(int newDay) {
    day = newDay;
    temperatures.clear();
}

int TemperatureMonitorService::getDay() const {
    return day;
}

vector<double>& TemperatureMonitorService::getTemperatures() {
    return temperatures;
}

String TemperatureMonitorService::getCurrentTemperature(String locale, NTC_TEMP_CLASS ntc) {
    double currentTemperature = ntc.GetTemp();
    if (locale == "en-US") {
        currentTemperature = celsiusToFahrenheit(currentTemperature);
    }

    ArduinoResponse response(
        true,
        "",
        String(currentTemperature)
    );

    return response.toJson();
}

String TemperatureMonitorService::getAverageTemperature(String locale, NTC_TEMP_CLASS ntc) {
    checkDate(ntc);
    
    double sum = 0;
    for (double temperature : temperatures) {
        sum += temperature;
    }

    double average = sum / temperatures.size();
    if (locale == "en-US") {
        average = celsiusToFahrenheit(average);
    }

    average = round(average * 100) / 100.0;

    ArduinoResponse response(
        true,
        "",
        String(average)
    );

    return response.toJson();
}

int TemperatureMonitorService::getTodaysDay() {
    auto now = chrono::system_clock::now();

    time_t now_time = chrono::system_clock::to_time_t(now);
    tm* now_tm = localtime(&now_time);

    int day = now_tm->tm_mday;

    return day;
}

void TemperatureMonitorService::checkDate(NTC_TEMP_CLASS ntc) {
    int todaysDay = getTodaysDay();

    if (day != todaysDay) {
        previousMillis = 0;
        day = todaysDay;
        addTemperature(ntc.GetTemp());
    }
}
