#include <gtest/gtest.h>
#include "Solution.cpp"

int main() {
    std::string number{"11010011110000001000001111111"}; //->32767
    std::cout << eliminate_unset_bits(number) << std::endl;

    return 0;
}
