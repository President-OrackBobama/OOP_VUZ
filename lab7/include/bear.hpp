#pragma once
#include "orc.hpp"
#include "squirrel.hpp"
#include "npc.hpp"

class Bear : public NPC {
public:
    Bear(int x, int y);
    std::string get_type() override;
    int get_damage_range() const override;

    bool accept(std::shared_ptr<NPC> visitor) override;
    bool fight(std::shared_ptr<Orc> accepter) override;
    bool fight(std::shared_ptr<Bear> accepter) override;
    bool fight(std::shared_ptr<Squirrel> accepter) override;

    void move(int max_x, int max_y) override;
};
