#include <gtest/gtest.h>
#include "../src/factory.cpp"
#include "../src/observer.cpp"
#include "../src/orc.cpp"
#include "../src/bear.cpp"
#include "../src/squirrel.cpp"
#include "../src/npc.cpp"
#include "bits/stdc++.h"

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

    EXPECT_EQ(orc->getType(), "Orc");
    EXPECT_EQ(bear->getType(), "Bear");
    EXPECT_EQ(squirrel->getType(), "Squirrel");

    EXPECT_TRUE(orc->alive());
    EXPECT_TRUE(bear->alive());
    EXPECT_TRUE(squirrel->alive());

    EXPECT_EQ(orc->getX(), 1);
    EXPECT_EQ(bear->getX(), 3);
    EXPECT_EQ(squirrel->getX(), 5);
    EXPECT_EQ(orc->getY(), 2);
    EXPECT_EQ(bear->getY(), 4);
    EXPECT_EQ(squirrel->getY(), 6);
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
    EXPECT_EQ(orc.getX(), 1);
    EXPECT_EQ(orc.getY(), 2);
    EXPECT_TRUE(orc.alive());
    EXPECT_EQ(orc.getType(), "Orc");
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

    EXPECT_TRUE(orc->accept(orc2));
    EXPECT_FALSE(orc->alive());
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TEST(BearTest, ConstructorAndGetters) {
    Bear bear(1, 2);
    EXPECT_EQ(bear.getX(), 1);
    EXPECT_EQ(bear.getY(), 2);
    EXPECT_TRUE(bear.alive());
    EXPECT_EQ(bear.getType(), "Bear");
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

    EXPECT_TRUE(bear->accept(orc));
    EXPECT_FALSE(bear->alive());
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TEST(SquirrelTest, ConstructorAndGetters) {
    Squirrel squirrel(1, 2);
    EXPECT_EQ(squirrel.getX(), 1);
    EXPECT_EQ(squirrel.getY(), 2);
    EXPECT_TRUE(squirrel.alive());
    EXPECT_EQ(squirrel.getType(), "Squirrel");
}

TEST(SquirrelTest, Visitors) {
    NPCFactory factory;
    std::shared_ptr<NPC> orc = factory.createNPC(NPC_type::orc, 1, 2);
    std::shared_ptr<NPC> bear = factory.createNPC(NPC_type::bear, 3, 4);
    std::shared_ptr<NPC> squirrel = factory.createNPC(NPC_type::squirrel, 5, 6);
    std::shared_ptr<NPC> squirrel2 = factory.createNPC(NPC_type::squirrel, -5, 6);

    EXPECT_TRUE(squirrel->alive());
    EXPECT_FALSE(squirrel->accept(orc));
    EXPECT_TRUE(squirrel->alive());

    EXPECT_TRUE(squirrel->alive());
    EXPECT_FALSE(squirrel->accept(squirrel2));
    EXPECT_TRUE(squirrel->alive());

    EXPECT_TRUE(squirrel->alive());
    EXPECT_TRUE(squirrel->accept(bear));
    EXPECT_FALSE(squirrel->alive());

    remove("battle_stats.txt");
    remove("test.txt");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
