#pragma once
#include <iostream>
#include <memory>
#include <optional>
#include <queue>
#include <shared_mutex>
#include <thread>

#include "npc.hpp"

using namespace std::chrono_literals;
extern std::atomic<bool> stop_flag;

struct FightEvent {
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<NPC> defender;
};

class FightManager {
private:
    std::queue<FightEvent> events;
    std::shared_mutex mtx;

    FightManager() {}

public:
    static FightManager &get();

    void add_event(FightEvent &&event);

    void operator()();
};
