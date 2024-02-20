#pragma once
#include <cmath>
#include <iostream>
#include <memory>
#include <set>
#include <vector>

class NPC;
class Orc;
class Bear;
class Squirrel;

using set_t = std::set<std::shared_ptr<NPC>>;

enum NPC_type {
    unknown = 0,
    orc = 1,
    bear = 2,
    squirrel = 3
};

/*enum NPC_type { unknown = 0,
                knight = 1,
                merchant = 2,
                squirrel = 3 };*/

class Observer {
public:
    Observer() = default;
    virtual void report_killed(const NPC& attacker, const NPC& defender) = 0;
};

class NPC {
protected:
    NPC_type _type;
    int _x = 0, _y = 0;
    std::string _name;
    bool _alive;
    std::vector<std::shared_ptr<Observer>> observers;
    static int id;

    NPC(NPC_type type, int x, int y, std::string name);
    virtual ~NPC() = default;

public:
    virtual std::string getType() = 0;
    const int getX() const;
    const int getY() const;
    const std::string& getName() const;
    const bool alive() const;

    virtual bool accept(std::shared_ptr<NPC> visitor) = 0;
    virtual bool fight(Orc& accepter) = 0;
    virtual bool fight(Bear& accepter) = 0;
    virtual bool fight(Squirrel& accepter) = 0;

    void attach(std::shared_ptr<Observer> observer);
    void notify_killed(const NPC& defender) const;

    bool near(const std::shared_ptr<NPC>& enemy, int distance) const;

    friend std::ostream& operator<<(std::ostream& out, const NPC& npc);
};
