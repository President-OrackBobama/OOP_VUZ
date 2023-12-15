#include "gtest/gtest.h"
#include "../src/nmBitString.cpp"

TEST(BitStringTest, DefaultConstructor) {
    BitString b;
    EXPECT_EQ(b.getSize(), 1);
}

TEST(BitStringTest, SizeConstructor) {
    BitString b(5, '1');
    EXPECT_EQ(b.getSize(), 5);
    EXPECT_EQ(b.getBit(0), '1');
}

TEST(BitStringTest, StringConstructor) {
    BitString b("1010");
    EXPECT_EQ(b.getSize(), 4);
    EXPECT_EQ(b.getBit(2), '1');
}

TEST(BitStringTest, CopyConstructor) {
    BitString original(3, '1');
    BitString copy(original);
    EXPECT_EQ(copy.getSize(), 3);
    EXPECT_EQ(copy.getBit(1), '1');
}

TEST(BitStringTest, MoveConstructor) {
    BitString original(5, '1');
    BitString moved(std::move(original));

    EXPECT_EQ(moved.getSize(), 5);
    EXPECT_EQ(moved.getBit(3), '1');
    EXPECT_EQ(original.getSize(), 0);
}

TEST(BitStringTest, CopyAssignmentOperator) {
    BitString original(3, '1');
    BitString copy;
    copy = original;

    EXPECT_EQ(copy.getSize(), 3);
    EXPECT_EQ(copy.getBit(1), '1');
}

TEST(BitStringTest, MoveAssignmentOperator) {
    BitString original(4, '1');
    BitString moved;
    moved = std::move(original);

    EXPECT_EQ(moved.getSize(), 4);
    EXPECT_EQ(moved.getBit(2), '1');
    EXPECT_EQ(original.getSize(), 0);
}

TEST(BitStringTest, InitializerListConstructor) {
    BitString b = {'1', '0', '1', '1'};
    EXPECT_EQ(b.getSize(), 4);
    EXPECT_EQ(b.getBit(2), '1');
}

TEST(BitStringTest, SumAssignOperator) {
    BitString b1 = {'1', '0', '1'};
    BitString b2 = {'1', '1'};
    b1 += b2;

    EXPECT_EQ(b1.getSize(), 4);
    EXPECT_EQ(b1.getBit(0), '1');
    EXPECT_EQ(b1.getBit(1), '0');
    EXPECT_EQ(b1.getBit(2), '0');
    EXPECT_EQ(b1.getBit(3), '0');
}

TEST(BitStringTest, SumOperator) {
    BitString b1 = {'1', '0', '1'};
    BitString b2 = {'1', '1'};
    BitString result = b1 + b2;

    EXPECT_EQ(result.getSize(), 4);
    EXPECT_EQ(result.getBit(0), '1');
    EXPECT_EQ(result.getBit(1), '0');
    EXPECT_EQ(result.getBit(2), '0');
    EXPECT_EQ(result.getBit(3), '0');
}

TEST(BitStringTest, SubtractionAssignmentOperator) {
    BitString b1 = {'1', '0', '1', '1'};
    BitString b2 = {'0', '1'};
    b1 -= b2;

    EXPECT_EQ(b1.getSize(), 4);
    EXPECT_EQ(b1.getBit(0), '1');
    EXPECT_EQ(b1.getBit(1), '0');
    EXPECT_EQ(b1.getBit(2), '1');
    EXPECT_EQ(b1.getBit(3), '0');
}

TEST(BitStringTest, SubtractionOperator) {
    BitString b1 = {'1', '0', '1', '1'};
    BitString b2 = {'0', '1'};
    BitString result = b1 - b2;

    EXPECT_EQ(result.getSize(), 4);
    EXPECT_EQ(result.getBit(0), '1');
    EXPECT_EQ(result.getBit(1), '0');
    EXPECT_EQ(result.getBit(2), '1');
    EXPECT_EQ(result.getBit(3), '0');
}

TEST(BitStringTest, BitwiseANDOperator) {
    BitString b1 = {'1', '0', '1'};
    BitString b2 = {'1', '1'};
    BitString result = b1 & b2;

    EXPECT_EQ(result.getSize(), 1);
    EXPECT_EQ(result.getBit(0), '1');
}

TEST(BitStringTest, BitwiseOROperator) {
    BitString b1 = {'1', '0', '1'};
    BitString b2 = {'1', '1'};
    BitString result = b1 | b2;

    EXPECT_EQ(result.getSize(), 3);
    EXPECT_EQ(result.getBit(0), '1');
    EXPECT_EQ(result.getBit(1), '1');
    EXPECT_EQ(result.getBit(2), '1');
}

TEST(BitStringTest, BitwiseXOROperator) {
    BitString b1 = {'1', '0', '1'};
    BitString b2 = {'1', '1'};
    BitString result = b1 ^ b2;

    EXPECT_EQ(result.getSize(), 3);
    EXPECT_EQ(result.getBit(0), '1');
    EXPECT_EQ(result.getBit(1), '1');
    EXPECT_EQ(result.getBit(2), '0');
}

TEST(BitStringTest, BitwiseNOTOperator) {
    BitString b = {'1', '0', '1'};
    BitString result = ~b;

    EXPECT_EQ(result.getSize(), 2);
    EXPECT_EQ(result.getBit(0), '1');
    EXPECT_EQ(result.getBit(1), '0');
}

TEST(BitStringTest, LessThanOperator) {
    BitString b1 = {'1', '0', '1'};
    BitString b2 = {'1', '1'};
    EXPECT_FALSE(b1 < b2);
}

TEST(BitStringTest, GreaterThanOperator) {
    BitString b1 = {'1', '1'};
    BitString b2 = {'1', '0', '1'};
    EXPECT_FALSE(b1 > b2);
}

TEST(BitStringTest, EqualityOperator) {
    BitString b1 = {'1', '0', '1'};
    BitString b2 = {'1', '0', '1'};
    EXPECT_TRUE(b1 == b2);
}

TEST(BitStringTest, InequalityOperator) {
    BitString b1 = {'1', '0', '1'};
    BitString b2 = {'1', '1'};
    EXPECT_TRUE(b1 != b2);
}

TEST(BitStringTest, GetSize) {
    BitString b1;
    EXPECT_EQ(b1.getSize(), 1);

    BitString b2(5, '1');
    EXPECT_EQ(b2.getSize(), 5);

    BitString b3("010");
    EXPECT_EQ(b3.getSize(), 2);
}

TEST(BitStringTest, GetBit) {
    BitString b = {'1', '0', '1', '1'};
    
    EXPECT_EQ(b.getBit(0), '1');
    EXPECT_EQ(b.getBit(1), '0');
    EXPECT_EQ(b.getBit(2), '1');
    EXPECT_EQ(b.getBit(3), '1');
    
    EXPECT_THROW(b.getBit(5), std::out_of_range);
}

TEST(BitStringTest, SetBit) {
    BitString b = {'1', '0', '1', '1'};

    b.setBit(0, '0');
    EXPECT_EQ(b.getBit(0), '1');
    EXPECT_EQ(b.getBit(1), '1');

    EXPECT_THROW(b.setBit(5, '1'), std::out_of_range);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}