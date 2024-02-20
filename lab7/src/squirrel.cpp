#include "../include/squirrel.hpp"

Squirrel::Squirrel(int x, int y) : NPC(NPC_type::squirrel, x, y, "squirrel_" + std::to_string(id++)) {}

std::string Squirrel::get_type() {
    return "Squirrel";
}

int Squirrel::get_damage_range() const {
    return 5;
}

bool Squirrel::accept(std::shared_ptr<NPC> visitor) {
    if (visitor->fight(std::shared_ptr<Squirrel>(this, [](Squirrel *) {}))) {
        return true;
    }
    return false;
}

bool Squirrel::fight(std::shared_ptr<Orc> accepter) {
    return false;
}

bool Squirrel::fight(std::shared_ptr<Bear> accepter) {
    return false;
}

bool Squirrel::fight(std::shared_ptr<Squirrel> accepter) {
    return false;
}

void Squirrel::move(int max_x, int max_y) {
    std::lock_guard<std::shared_mutex> lck(_mutex);
    double angle = static_cast<double>(std::rand() % 100) / 100 * 2 * M_PI,
           dist = static_cast<double>(std::rand() % 100) / 100 * 5;

    int shift_x = static_cast<int>(dist * std::cos(angle)),
        shift_y = static_cast<int>(dist * std::sin(angle));

    if ((_x + shift_x >= 0) && (_x + shift_x <= max_x))
        _x += shift_x;
    if ((_y + shift_y >= 0) && (_y + shift_y <= max_y))
        _y += shift_y;
}
