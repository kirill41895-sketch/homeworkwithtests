#include "Repositories.h"
#include <stdexcept>

FileJournalRepository::FileJournalRepository(const std::string& filename) {
    file.open(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open journal file: " + filename);
    }
    file << "Time,Temperature,HeaterPower,CoolerPower\n";
}

void FileJournalRepository::save(const LogEntry& entry) {
    if (file.is_open()) {
        file << entry.time << "," << entry.temp << "," 
             << entry.heaterPower << "," << entry.coolerPower << "\n";
    }
}