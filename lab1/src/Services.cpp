#include "Services.h"

Thermostat::Thermostat(Temperature target, double hyst) 
    : targetTemp(target), hysteresis(hyst) {}

std::pair<Power, Power> Thermostat::calculateControl(Temperature currentTemp) {
    double current = currentTemp.celsius;
    double target = targetTemp.celsius;

    if (current < target - hysteresis) {
        return {Power(1.0), Power(0.0)};
    } 
    if (current > target + hysteresis) {
        return {Power(0.0), Power(1.0)};
    }
    return {Power(0.0), Power(0.0)};
}