#include "bits/stdc++.h"
#include "factory.cpp"
#include "fight.cpp"
#include "npc.cpp"
#include "observer.cpp"
#include "orc.cpp"
#include "squirrel.cpp"
#include "bear.cpp"

std::ostream &operator<<(std::ostream &out, const set_t &s) {
    for (auto npc: s) {
        out << *npc.get() << std::endl;
    }
    return out;
}

int main() {
    const int MAX_X{100}, MAX_Y{100}, npc_num{50};
    set_t npc_set;
    NPCFactory factory;
    std::shared_ptr<Observer> console_observer, file_observer;
    console_observer = std::make_shared<ConsoleObserver>();
    file_observer = std::make_shared<FileObserver>();
    std::srand(std::time(0));

    std::cout << "Generating ..." << std::endl
              << std::endl;

    for (size_t i = 0; i < npc_num; ++i) {
        std::shared_ptr<NPC> cur_npc = factory.createNPC(NPC_type(std::rand() % 3 + 1),
                                                         std::rand() % MAX_X,
                                                         std::rand() % MAX_Y);

        cur_npc->attach(console_observer);
        cur_npc->attach(file_observer);
        npc_set.insert(cur_npc);
    }

    std::cout << "Saving ..." << std::endl
              << std::endl;
    factory.save(npc_set, "npc.txt");

    std::cout << "Loading ..." << std::endl
              << std::endl;
    npc_set = factory.load("npc.txt");

    std::cout << "Warriors list:\n"
              << npc_set << std::endl;

    std::cout << "Fighting ..." << std::endl
              << std::endl;
    std::cout << "Fight stats ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl
              << std::endl;

    std::thread fight_thread(std::ref(FightManager::get()));

    std::thread move_thread([&npc_set, MAX_X, MAX_Y]() {
        while (!stop_flag) {
            for (std::shared_ptr<NPC> npc: npc_set) {
                if (npc->alive()) {
                    npc->move(MAX_X - 1, MAX_Y - 1);
                }
            }
            for (std::shared_ptr<NPC> defender: npc_set) {
                for (std::shared_ptr<NPC> attacker: npc_set) {
                    if (defender != attacker && defender->alive() && attacker->alive() &&
                        defender->near(attacker, attacker->get_damage_range())) {
                        FightManager::get().add_event({defender, attacker});
                    }
                }
            }
            std::this_thread::sleep_for(1s);
        }
    });

    int run_time = 30;
    while (run_time--) {
        size_t grid{20}, survived{0};
        std::vector<std::vector<std::string>> map(grid, std::vector<std::string>(grid, "0"));
        {
            std::lock_guard<std::mutex> lck(print_mutex);

            for (std::shared_ptr<NPC> npc: npc_set) {
                std::string type = npc->get_type();
                int x = npc->get_x() / 5, y = npc->get_y() / 5;
                if (npc->alive()) {
                    if (map[x][y] == "0" || map[x][y] == ".") {
                        if (type == "Orc") {
                            map[x][y] = "O";
                        } else if (type == "Bear") {
                            map[x][y] = "B";
                        } else if (type == "Squirrel") {
                            map[x][y] = "S";
                        }
                    } else if (map[x][y] == "O" || map[x][y] == "B" || map[x][y] == "S") {
                        map[x][y] = "2";
                    } else {
                        map[x][y] = std::to_string(std::stoi(map[x][y]) + 1);
                    }
                    ++survived;
                } else {
                    if (map[x][y] == "0") {
                        map[x][y] = ".";
                    }
                }
            }

            std::cout << "Survived: " << survived << " | Killed: " << npc_num - survived << std::endl;

            std::cout << "   ";
            for (size_t i = 0; i < grid; ++i) {
                if (i < 10) {
                    std::cout << "  " << i << " ";
                } else {
                    std::cout << " " << i << " ";
                }
            }
            std::cout << std::endl;

            for (size_t i = 0; i < grid; ++i) {
                if (i < 10) {
                    std::cout << i << "  ";
                } else {
                    std::cout << i << " ";
                }

                for (size_t j = 0; j < grid; ++j) {
                    std::string str = map[i][j];
                    if (str != "0") {
                        if (str.size() == 1) {
                            std::cout << "[ " << str << "]";
                        } else {
                            std::cout << "[" << str << "]";
                        }
                    } else {
                        std::cout << "[  ]";
                    }
                }
                std::cout << std::endl;
            }
            std::cout << std::endl
                      << "Timer: " << run_time << "s" << std::endl;
        }
        if (run_time == 1) {
            stop_flag = true;
        }
        std::this_thread::sleep_for(1s);
    }

    move_thread.join();
    fight_thread.join();

    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl
              << std::endl;

    std::cout << "Survivors:" << std::endl;

    for (std::shared_ptr<NPC> npc: npc_set) {
        if (npc->alive()) {
            std::cout << *npc.get() << std::endl;
        }
    }

    return 0;
}
