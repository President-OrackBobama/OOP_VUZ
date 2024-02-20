#include "../include/orc.hpp"

Orc::Orc(int x, int y) : NPC(NPC_type::orc, x, y, "orc_" + std::to_string(id++)) {}

std::string Orc::getType() {
    return "Orc";
}

bool Orc::accept(std::shared_ptr<NPC> visitor) {
    if (visitor->fight(*this)) {
        this->_alive = false;
        return true;
    }
    return false;
}

bool Orc::fight(Orc& accepter) {
    notify_killed(accepter);
    return true;
}

bool Orc::fight(Bear& accepter) {
    notify_killed(accepter);
    return true;
}

bool Orc::fight(Squirrel& accepter) {
    return false;
}