#include <gtest/gtest.h>
#include <iostream>
#include "../include/allocator.hpp"
#include "../include/list.hpp"

#define BLOCKS 1024

using namespace new_Allocator;

TEST(ListAllocator, test1) {

    List<int, Allocator<int> > lst;
    lst.emplace_back(10);
    ASSERT_TRUE(*lst.begin() == 10);
    lst.clear();
}

TEST(ListAllocator, test2) {

    List<double, Allocator<double> > lst;
    EXPECT_ANY_THROW(lst.erase(lst.begin()));
}

TEST(ListAllocator, test3) {

    List<double, Allocator<double>> lst;

    lst.emplace_front(0);

    ASSERT_TRUE(lst.rbegin() == lst.begin());

    lst.clear();
}

TEST(ListIterator, test1) {
    List<int, Allocator<int>> lst;

    lst.emplace_back(10);
    lst.emplace_back(10);
    lst.emplace_back(10);
    lst.emplace_back(10);
    lst.emplace(++lst.begin(), 77);
    lst.emplace_front(15);

    List<int, Allocator<int>>::Iterator tmp1, tmp2;

    for(List<int, Allocator<int>>::Iterator it = lst.begin(); it != lst.end(); ++it){
        if(*it == 77) tmp1 = it;
        if(*it == 10) tmp2 = it;
    }

    ASSERT_TRUE(*lst.begin() == 15);
    ASSERT_TRUE(*tmp1 == 77);
    ASSERT_TRUE(*tmp2 == 10);
    ASSERT_TRUE(lst.size() == 6);

    lst.clear();
}

TEST(ListIterator, test2) {

    List<std::string, Allocator<std::string>> lst;

    lst.emplace_front("Hey!\n");
    lst.emplace_back("Nice to meet you!\n");
    lst.emplace(lst.rbegin(), "My name is [...]\n");

    std::string res = "";
    for(auto elem : lst){
        res+=elem;
    }

    ASSERT_TRUE(res=="Hey!\nMy name is [...]\nNice to meet you!\n");

    lst.clear();
}

int main(int argc, char** argv) {

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
