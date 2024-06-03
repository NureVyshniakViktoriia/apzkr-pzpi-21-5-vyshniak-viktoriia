#ifndef TEMPERATUREMONITORSERVICE_H
#define TEMPERATUREMONITORSERVICE_H

#include <vector>
#include <NTC_TEMP_MODULE.h>
#include <chrono>

using namespace std;

inline unsigned long previousMillis = 0;
inline const unsigned long interval = 3600000;

class TemperatureMonitorService {
private:
    int day;
    vector<double> temperatures;
    
public:
    TemperatureMonitorService();
    void addTemperature(double temp);
    void updateDay(int newDay);
    int getDay() const;
    vector<double>& getTemperatures();
    String getCurrentTemperature(String locale, NTC_TEMP_CLASS ntc);
    String getAverageTemperature(String locale, NTC_TEMP_CLASS ntc);
    int getTodaysDay();
    void checkDate(NTC_TEMP_CLASS ntc);
};

#endif