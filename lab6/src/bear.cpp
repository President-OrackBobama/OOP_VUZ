#include "../include/bear.hpp"

Bear::Bear(int x, int y) : NPC(NPC_type::bear, x, y, "bear_" + std::to_string(id++)) {}

std::string Bear::getType() {
    return "Bear";
}

bool Bear::accept(std::shared_ptr<NPC> visitor) {
    if (visitor->fight(*this)) {
        this->_alive = false;
        return true;
    }
    return false;
}

bool Bear::fight(Orc& accepter) {
    return false;
}

bool Bear::fight(Bear& accepter) {
    return false;
}

bool Bear::fight(Squirrel& accepter) {
    notify_killed(accepter);
    return true;
}