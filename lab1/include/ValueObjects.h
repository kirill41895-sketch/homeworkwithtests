#pragma once

struct Temperature {
    double celsius;
    Temperature(double c) : celsius(c) {}
};

struct Power {
    double value;
    Power(double v) : value(v < 0.0 ? 0.0 : (v > 1.0 ? 1.0 : v)) {}
};

struct LogEntry {
    double time;
    double temp;
    double heaterPower;
    double coolerPower;
};