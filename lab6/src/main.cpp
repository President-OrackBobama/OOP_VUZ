#include "bits/stdc++.h"
#include "factory.cpp"
#include "orc.cpp"
#include "bear.cpp"
#include "squirrel.cpp"
#include "observer.cpp"
#include "npc.cpp"

std::ostream &operator<<(std::ostream &out, const set_t &s) {
    for (auto npc : s) {
        out << *npc.get() << std::endl;
    }
    return out;
}

int main() {
    set_t npc_set;
    NPCFactory factory;
    std::shared_ptr<Observer> console_observer, file_observer;
    console_observer = std::make_shared<ConsoleObserver>();
    file_observer = std::make_shared<FileObserver>();

    std::cout << "Generating..." << std::endl
              << std::endl;
    for (size_t i = 0; i < 100; ++i) {
        std::shared_ptr<NPC> cur_npc = factory.createNPC(NPC_type(std::rand() % 3 + 1),
                                                         std::rand() % 500 + 1,
                                                         std::rand() % 500 + 1);

        cur_npc->attach(console_observer);
        cur_npc->attach(file_observer);
        npc_set.insert(cur_npc);
    }

    std::cout << "Saving..." << std::endl
              << std::endl;
    factory.save(npc_set, "npc.txt");

    std::cout << "Loading..." << std::endl
              << std::endl;
    npc_set = factory.load("npc.txt");

    std::cout << "Warriors list:\n"
              << npc_set << std::endl;

    std::cout << "Fighting..." << std::endl
              << std::endl;
    std::cout << "Fight stats ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl
              << std::endl;

    for (int distance = 50; distance <= 500 && !npc_set.empty(); distance += 50) {
        set_t killed_list;
        std::cout << "distance: " << distance << std::endl;
        for (std::shared_ptr<NPC> attacker : npc_set) {
            for (std::shared_ptr<NPC> defender : npc_set) {
                if (attacker != defender && attacker->alive() && defender->alive() && attacker->near(defender, distance)) {
                    if (defender->accept(attacker)) {
                        killed_list.insert(defender);
                    }
                }
            }
        }

        for (auto &npc : killed_list) {
            npc_set.erase(npc);
        }
        std::cout << "-> killed: " << killed_list.size() << std::endl
                  << std::endl;
    }

    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl
              << std::endl;

    std::cout << "Survivors:\n"
              << npc_set << std::endl;
}
