#pragma once
#include "orc.hpp"
#include "bear.hpp"
#include "npc.hpp"

class Squirrel : public NPC {
public:
    Squirrel(int x, int y);
    std::string getType() override;

    bool accept(std::shared_ptr<NPC> visitor) override;
    bool fight(Orc& accepter) override;
    bool fight(Bear& accepter) override;
    bool fight(Squirrel& accepter) override;
};
