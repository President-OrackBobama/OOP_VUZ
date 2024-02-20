#pragma once

#include <fstream>
#include <memory>
#include <shared_mutex>

#include "orc.hpp"
#include "bear.hpp"
#include "squirrel.hpp"

extern std::mutex print_mutex, file_mutex;

class ConsoleObserver : public Observer {
public:
    ConsoleObserver() = default;

    void report_killed(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender) override;
};

class FileObserver : public Observer {
    std::ofstream os;

public:
    FileObserver() : os(std::ofstream("fight_stats.txt")) {}

    void report_killed(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender) override;
};
