#include <gtest/gtest.h>
#include "../src/factory.cpp"
#include "../src/fight.cpp"
#include "../src/npc.cpp"
#include "../src/bear.cpp"
#include "../src/orc.cpp"
#include "../src/squirrel.cpp"
#include "bits/stdc++.h"
#include "../src/observer.cpp"


TEST(NPCFactoryTest, CreateNPC) {
    NPCFactory factory;
    bool test = true;
    try {
        std::shared_ptr<NPC> orc = factory.createNPC(NPC_type::orc, 1, 2);
        std::shared_ptr<NPC> bear = factory.createNPC(NPC_type::bear, 3, 4);
        std::shared_ptr<NPC> squirrel = factory.createNPC(NPC_type::squirrel, 5, 6);
    } catch (...) {
        test = false;
    }
    EXPECT_TRUE(test);
}

TEST(NPCFactoryTest, Save) {
    NPCFactory factory;
    set_t s;
    bool test = true;
    try {
        s.insert(factory.createNPC(NPC_type::orc, 1, 2));
        s.insert(factory.createNPC(NPC_type::bear, 3, 4));
        s.insert(factory.createNPC(NPC_type::squirrel, 5, 6));
        factory.save(s, "test.txt");
    } catch (...) {
        test = false;
    }
    EXPECT_TRUE(test);
}

TEST(NPCFactoryTest, Load) {
    NPCFactory factory;
    set_t s;
    bool test = true;
    try {
        s = factory.load("test.txt");
    } catch (...) {
        test = false;
    }
    EXPECT_TRUE(test);
}

TEST(NPCTest, OutputOperator) {
    std::shared_ptr<NPC> npc = std::make_shared<Orc>(1, 2);
    std::stringstream expected_output;
    expected_output << "orc_9 {x : 1, y : 2}";

    std::stringstream actual_output;
    actual_output << *npc;

    EXPECT_EQ(expected_output.str(), actual_output.str());
}

TEST(NPCTest, Getters) {
    NPCFactory factory;
    std::shared_ptr<NPC> orc = factory.createNPC(NPC_type::orc, 1, 2);
    std::shared_ptr<NPC> bear = factory.createNPC(NPC_type::bear, 3, 4);
    std::shared_ptr<NPC> squirrel = factory.createNPC(NPC_type::squirrel, 5, 6);

    EXPECT_EQ(orc->get_type(), "Orc");
    EXPECT_EQ(bear->get_type(), "Bear");
    EXPECT_EQ(squirrel->get_type(), "Squirrel");

    EXPECT_TRUE(orc->alive());
    EXPECT_TRUE(bear->alive());
    EXPECT_TRUE(squirrel->alive());

    EXPECT_EQ(orc->get_x(), 1);
    EXPECT_EQ(bear->get_x(), 3);
    EXPECT_EQ(squirrel->get_x(), 5);
    EXPECT_EQ(orc->get_y(), 2);
    EXPECT_EQ(bear->get_y(), 4);
    EXPECT_EQ(squirrel->get_y(), 6);
}


TEST(NPCTest, Near) {
    NPCFactory factory;
    std::shared_ptr<NPC> orc = factory.createNPC(NPC_type::orc, 1, 2);
    std::shared_ptr<NPC> bear = factory.createNPC(NPC_type::bear, 50, 1);
    std::shared_ptr<NPC> squirrel = factory.createNPC(NPC_type::squirrel, 100, 1);

    EXPECT_FALSE(orc->near(bear, 10));
    EXPECT_TRUE(orc->near(bear, 60));
    EXPECT_FALSE(orc->near(squirrel, 90));
    EXPECT_TRUE(orc->near(squirrel, 110));
}


TEST(NPCTest, Attach) {
    NPCFactory factory;
    std::shared_ptr<NPC> orc = factory.createNPC(NPC_type::orc, 1, 1);
    std::shared_ptr<Observer> console_observer, file_observer;
    console_observer = std::make_shared<ConsoleObserver>();
    file_observer = std::make_shared<FileObserver>();
    bool test = true;
    try {
        orc->attach(console_observer);
        orc->attach(file_observer);
    } catch (...) {
        test = false;
    }
    EXPECT_TRUE(test);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TEST(OrcTest, ConstructorAndGetters) {
    Orc orc(1, 2);
    EXPECT_EQ(orc.get_x(), 1);
    EXPECT_EQ(orc.get_y(), 2);
    EXPECT_TRUE(orc.alive());
    EXPECT_EQ(orc.get_type(), "Orc");
}

TEST(OrcTest, Visitors) {
    NPCFactory factory;
    std::shared_ptr<NPC> orc = factory.createNPC(NPC_type::orc, 1, 2);
    std::shared_ptr<NPC> orc2 = factory.createNPC(NPC_type::orc, -1, 2);
    std::shared_ptr<NPC> bear = factory.createNPC(NPC_type::bear, 3, 4);
    std::shared_ptr<NPC> squirrel = factory.createNPC(NPC_type::squirrel, 5, 6);

    EXPECT_TRUE(orc->alive());
    EXPECT_FALSE(orc->accept(bear));
    EXPECT_TRUE(orc->alive());

    EXPECT_FALSE(orc->accept(squirrel));
    EXPECT_TRUE(orc->alive());
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TEST(BearTest, ConstructorAndGetters) {
    Bear bear(1, 2);
    EXPECT_EQ(bear.get_x(), 1);
    EXPECT_EQ(bear.get_y(), 2);
    EXPECT_TRUE(bear.alive());
    EXPECT_EQ(bear.get_type(), "Bear");
}

TEST(BearTest, Visitors) {
    NPCFactory factory;
    std::shared_ptr<NPC> orc = factory.createNPC(NPC_type::orc, 1, 2);
    std::shared_ptr<NPC> bear = factory.createNPC(NPC_type::bear, 3, 4);
    std::shared_ptr<NPC> bear2 = factory.createNPC(NPC_type::bear, -3, 4);
    std::shared_ptr<NPC> squirrel = factory.createNPC(NPC_type::squirrel, 5, 6);

    EXPECT_TRUE(bear->alive());
    EXPECT_FALSE(bear->accept(squirrel));
    EXPECT_TRUE(bear->alive());

    EXPECT_FALSE(bear->accept(bear2));
    EXPECT_TRUE(bear->alive());


}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TEST(SquirrelTest, ConstructorAndGetters) {
    Squirrel squirrel(1, 2);
    EXPECT_EQ(squirrel.get_x(), 1);
    EXPECT_EQ(squirrel.get_y(), 2);
    EXPECT_TRUE(squirrel.alive());
    EXPECT_EQ(squirrel.get_type(), "Squirrel");
}

TEST(SquirrelTest, Visitors) {
    NPCFactory factory;
    std::shared_ptr<NPC> orc = factory.createNPC(NPC_type::orc, 1, 2);
    std::shared_ptr<NPC> bear = factory.createNPC(NPC_type::bear, 3, 4);
    std::shared_ptr<NPC> squirrel = factory.createNPC(NPC_type::squirrel, 5, 5);
    std::shared_ptr<NPC> squirrel2 = factory.createNPC(NPC_type::squirrel, -5, 6);

    EXPECT_TRUE(squirrel->alive());
    EXPECT_FALSE(squirrel->accept(orc));
    EXPECT_TRUE(squirrel->alive());

    EXPECT_TRUE(squirrel->alive());
    EXPECT_FALSE(squirrel->accept(squirrel2));
    EXPECT_TRUE(squirrel2->alive());

    remove("fight_stats.txt");
    remove("test.txt");
}

//_________________________________________________________________________________________________________________________
TEST(FightManagerTest, GetReturnsSingletonInstance) {
    FightManager& instance1 = FightManager::get();
    FightManager& instance2 = FightManager::get();

    EXPECT_EQ(&instance1, &instance2);
}

TEST(FightManagerTest, AddEventAddsEventToQueue) {
    FightManager& manager = FightManager::get();
    FightEvent event;

    bool test = true;
    try {
        manager.add_event(std::move(event));
    } catch (...) {
        test = false;
    }
    EXPECT_TRUE(test);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
