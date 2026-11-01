#pragma once
#include "ValueObjects.h"
#include <utility>

class Thermostat {
    Temperature targetTemp;
    double hysteresis;
public:
    Thermostat(Temperature target, double hyst);
    std::pair<Power, Power> calculateControl(Temperature currentTemp);
};