#include "Room.h"
#include "Services.h"
#include "Repositories.h"
#include <iostream>
#include <memory>

int main() {
    unsigned int seed = 42;
    double dt = 1.0;
    int total_steps = 300;

    try {
        std::unique_ptr<IJournalRepository> journal = std::make_unique<FileJournalRepository>("simulation_log.csv");
        
        Room room(15.0, 500.0, 5.0, 100.0, 100.0, seed);
        Thermostat thermostat(Temperature(22.0), 0.5);

        for (int step = 0; step < total_steps; ++step) {
            double currentTime = step * dt;
            Temperature currentTemp = room.getSensorReading();
            auto [heaterPower, coolerPower] = thermostat.calculateControl(currentTemp);
            
            room.getHeater().setPower(heaterPower);
            room.getCooler().setPower(coolerPower);

            LogEntry entry{currentTime, currentTemp.celsius, heaterPower.value, coolerPower.value};
            journal->save(entry);

            room.updatePhysics(dt, Temperature(5.0));
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}