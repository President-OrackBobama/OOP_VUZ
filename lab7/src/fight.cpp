#include "../include/fight.hpp"

std::atomic<bool> stop_flag(false);

FightManager &FightManager::get() {
    static FightManager instance;
    return instance;
}

void FightManager::add_event(FightEvent &&event) {
    std::lock_guard<std::shared_mutex> lock(mtx);
    events.push(event);
}

void FightManager::operator()() {
    while (!stop_flag) {
        {
            std::optional<FightEvent> event;

            {
                std::lock_guard<std::shared_mutex> lock(mtx);
                if (!events.empty()) {
                    event = events.front();
                    events.pop();
                }
            }

            if (event) {
                std::shared_lock<std::shared_mutex> lock(mtx);
                if (event->attacker->alive() && event->defender->alive()) {
                    event->defender->accept(event->attacker);
                }
            } else {
                std::this_thread::sleep_for(100ms);
            }
        }
    }
}
