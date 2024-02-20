#include "../include/observer.hpp"

void ConsoleObserver::report_killed(const NPC& attacker, const NPC& defender) {
    std::cout << defender << "\t| killed by |\t" << attacker << std::endl;
}

void FileObserver::report_killed(const NPC& attacker, const NPC& defender) {
    os << defender << "\t| killed by |\t" << attacker << std::endl;
}
