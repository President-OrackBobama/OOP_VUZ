#include "../include/npc.hpp"

NPC::NPC(NPC_type type, int x, int y, std::string name) : _type(type), _x(x), _y(y), _name(name), _alive(true) {}

const int NPC::getX() const {
    return _x;
}

const int NPC::getY() const {
    return _y;
}

const std::string& NPC::getName() const {
    return _name;
}

const bool NPC::alive() const {
    return _alive;
}

void NPC::notify_killed(const NPC& defender) const {
    for (auto& o : observers) {
        o->report_killed(*this, defender);
    }
}

void NPC::attach(std::shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

bool NPC::near(const std::shared_ptr<NPC>& enemy, int distance) const {
    return std::pow(_x - enemy->_x, 2) + std::pow(_y - enemy->_y, 2) <= std::pow(distance, 2);
}

std::ostream& operator<<(std::ostream& out, const NPC& npc) {
    return out << npc._name << " {x : " << npc._x << ", y : " << npc._y << "}";
}

int NPC::id = 0;
