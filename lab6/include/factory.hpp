#pragma once
#include <fstream>

#include "npc.hpp"
#include "orc.hpp"
#include "bear.hpp"
#include "squirrel.hpp"
#include "observer.hpp"

class NPCFactory {
public:
    NPCFactory() = default;
    ~NPCFactory() = default;
    std::shared_ptr<NPC> createNPC(NPC_type type, int x, int y);
    void save(const set_t& s, const std::string& file_name);
    set_t load(const std::string& file_name);
};
