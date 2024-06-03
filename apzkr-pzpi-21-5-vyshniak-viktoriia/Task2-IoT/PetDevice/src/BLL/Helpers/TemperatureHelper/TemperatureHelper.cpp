#include "TemperatureHelper.h"

double celsiusToFahrenheit(double celsius) {
    const double CELSIUS_TO_FAHRENHEIT_SCALE = 9.0 / 5.0;
    const double FAHRENHEIT_FREEZING_POINT = 32.0;

    double tempInFahrenheit = (celsius * CELSIUS_TO_FAHRENHEIT_SCALE) + FAHRENHEIT_FREEZING_POINT;
    return round(tempInFahrenheit * 100) / 100.0;
}
