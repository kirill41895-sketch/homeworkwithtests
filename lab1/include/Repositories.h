#pragma once
#include "ValueObjects.h"
#include <string>
#include <fstream>

class IJournalRepository {
public:
    virtual ~IJournalRepository() = default;
    virtual void save(const LogEntry& entry) = 0;
};

class FileJournalRepository : public IJournalRepository {
    std::ofstream file;
public:
    FileJournalRepository(const std::string& filename); 
    void save(const LogEntry& entry) override;
};