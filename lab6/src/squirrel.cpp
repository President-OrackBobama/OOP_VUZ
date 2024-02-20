#include "../include/squirrel.hpp"

Squirrel::Squirrel(int x, int y) : NPC(NPC_type::squirrel, x, y, "squirrel_" + std::to_string(id++)) {}

std::string Squirrel::getType() {
    return "Squirrel";
}

bool Squirrel::accept(std::shared_ptr<NPC> visitor) {
    if (visitor->fight(*this)) {
        this->_alive = false;
        return true;
    }
    return false;
}

bool Squirrel::fight(Orc& accepter) {
    return false;
}

bool Squirrel::fight(Bear& accepter) {
    return false;
}

bool Squirrel::fight(Squirrel& accepter) {
    return false;
}