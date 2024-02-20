#include "../include/observer.hpp"

std::mutex print_mutex, file_mutex;

void ConsoleObserver::report_killed(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender) {
    std::lock_guard<std::mutex> lck(print_mutex);
    std::cout << *defender << " | killed by | " << *attacker << std::endl;
}

void FileObserver::report_killed(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender) {
    std::lock_guard<std::mutex> lck(file_mutex);
    os << *defender << " | killed by | " << *attacker << std::endl;
}
