#include "Room.h"

Room::Room(double startTemp, double mass, double heatLoss, double maxHeat, double maxCool, unsigned int seed)
    : actualTemperature(startTemp), thermalMass(mass), heatLossCoefficient(heatLoss),
      maxHeaterPower(maxHeat), maxCoolerPower(maxCool), 
      heater(std::make_unique<Heater>()), cooler(std::make_unique<Cooler>()),
      rng(seed), noiseDist(0.0, 0.1) {}

void Room::updatePhysics(double dt, Temperature outsideTemp) {
    double heaterEffect = heater->getPower().value * maxHeaterPower;
    double coolerEffect = cooler->getPower().value * maxCoolerPower;
    
    double heatLoss = heatLossCoefficient * (actualTemperature - outsideTemp.celsius);
    double netPower = heaterEffect - coolerEffect - heatLoss;
    
    actualTemperature += (netPower / thermalMass) * dt;
}

Temperature Room::getSensorReading() {
    return Temperature(actualTemperature + noiseDist(rng)); // это погрешность типа
}