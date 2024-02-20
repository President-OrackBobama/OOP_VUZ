#pragma once
#include "squirrel.hpp"
#include "bear.hpp"
#include "npc.hpp"

class Orc : public NPC {
public:
    Orc(int x, int y);
    std::string get_type() override;
    int get_damage_range() const override;

    bool accept(std::shared_ptr<NPC> visitor) override;
    bool fight(std::shared_ptr<Orc> accepter) override;
    bool fight(std::shared_ptr<Bear> accepter) override;
    bool fight(std::shared_ptr<Squirrel> accepter) override;

    void move(int max_x, int max_y) override;
};
