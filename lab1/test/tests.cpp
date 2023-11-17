#pragma once
#include "gtest/gtest.h"
#include "../src/Solution.cpp"  



TEST(EliminateUnsetBitsTest, EmptyString) {
    EXPECT_EQ(eliminate_unset_bits(""), 0);
}


TEST(EliminateUnsetBitsTest, AllBitsSet) {
    EXPECT_EQ(eliminate_unset_bits("1111"), 15);
}


TEST(EliminateUnsetBitsTest, NoBitsSet) {
    EXPECT_EQ(eliminate_unset_bits("0000"), 0);
}


TEST(EliminateUnsetBitsTest, OneBitSet) {
    EXPECT_EQ(eliminate_unset_bits("0010"), 1);
}


TEST(EliminateUnsetBitsTest, MixedBitsSet) {
    EXPECT_EQ(eliminate_unset_bits("101010"), 7);
}

TEST(EliminateUnsetBitsTest, LongNumber) {
    EXPECT_EQ(eliminate_unset_bits("101011001010011111110101001"), 65535);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}