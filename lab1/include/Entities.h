#pragma once
#include "ValueObjects.h"

class IActuator {
public:
    virtual ~IActuator() = default;
    virtual void setPower(Power p) = 0;
    virtual Power getPower() const = 0;
};

class Heater : public IActuator {
    Power currentPower{0.0};
public:
    void setPower(Power p) override { currentPower = p; }
    Power getPower() const override { return currentPower; }
};

class Cooler : public IActuator {
    Power currentPower{0.0};
public:
    void setPower(Power p) override { currentPower = p; }
    Power getPower() const override { return currentPower; }
};