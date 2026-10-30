#pragma once
#include "ValueObjects.h"
#include "Entities.h"
#include <memory>
#include <random>

class Room {
    double actualTemperature;
    const double thermalMass;
    const double heatLossCoefficient;
    const double maxHeaterPower;
    const double maxCoolerPower;
    
    std::unique_ptr<Heater> heater;
    std::unique_ptr<Cooler> cooler;
    std::mt19937 rng;
    std::normal_distribution<double> noiseDist;

public:
    Room(double startTemp, double mass, double heatLoss, double maxHeat, double maxCool, unsigned int seed);
    void updatePhysics(double dt, Temperature outsideTemp);
    IActuator& getHeater() { return *heater; }
    IActuator& getCooler() { return *cooler; }
    Temperature getSensorReading();
    double getTrueTemperature() const { return actualTemperature; }
};