#include "../include/factory.hpp"

std::shared_ptr<NPC> NPCFactory::createNPC(NPC_type type, int x, int y) {
    std::shared_ptr<NPC> res;
    switch (type) {
        case orc:
            res = std::make_shared<Orc>(x, y);
            break;
        case bear:
            res = std::make_shared<Bear>(x, y);
            break;
        case squirrel:
            res = std::make_shared<Squirrel>(x, y);
            break;

        default:
            break;
    }

    return res;
}

void NPCFactory::save(const set_t &s, const std::string &file_name) {
    std::ofstream out(file_name);
    out << s.size() << std::endl;
    for (auto &npc: s) {
        out << npc->getType() << std::endl
            << npc->getX() << std::endl
            << npc->getY() << std::endl;
    }

    out.flush();
    out.close();
}

set_t NPCFactory::load(const std::string &file_name) {
    set_t res;
    std::ifstream in(file_name);
    std::shared_ptr<Observer> console_observer, file_observer;
    console_observer = std::make_shared<ConsoleObserver>();
    file_observer = std::make_shared<FileObserver>();

    if (in.good() && in.is_open()) {
        int count;
        in >> count;
        while (count--) {
            std::shared_ptr<NPC> npc;
            int x, y;
            std::string type;
            in >> type;
            if (type == "Orc") {
                in >> x >> y;
                npc = std::make_shared<Orc>(x, y);
                res.insert(npc);
            } else if (type == "Bear") {
                in >> x >> y;
                npc = std::make_shared<Bear>(x, y);
                res.insert(npc);
            } else if (type == "Squirrel") {
                in >> x >> y;
                npc = std::make_shared<Squirrel>(x, y);
                res.insert(npc);
            }
            npc->attach(console_observer);
            npc->attach(file_observer);
        }
    }

    return res;
}