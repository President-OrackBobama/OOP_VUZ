#include <bits/stdc++.h>
#include "nmBitString.cpp"

int main() {
    BitString bitString = {'0', '0', '1', '0', '0', '1'};
    std::cout << "bitString: " << bitString << std::endl;

    BitString bitString1(bitString);
    bitString1 = bitString;
    BitString bitString2("110001010101");

    bitString1.setBit(2, '1');
    bitString1.setBit(3, '1');
    bitString2.setBit(3, '1');

    std::cout << "bitString1:  " << bitString1 << std::endl;

    std::cout << "bitString2: " << bitString2 << std::endl;

    std::cout << "bitString1 + bitString2: " << (bitString1 + bitString2) << std::endl;

    std::cout << "bitString2 - bitString1: " << (bitString2 - bitString1) << std::endl;

    std::cout << "bitString1 & bitString2: " << (bitString1 & bitString2) << std::endl;

    std::cout << "bitString1 | bitString2: " << (bitString1 | bitString2) << std::endl;

    std::cout << "bitString1 ^ bitString2: " << (bitString1 ^ bitString2) << std::endl;

    std::cout << "~bitString1: " << ~bitString1 << std::endl;

    std::cout << "~bitString2: " << ~bitString2 << std::endl;

    if (bitString1 == bitString2) {
        std::cout << "bitString1 is equal bitString2" << std::endl;
    } else {
        std::cout << "bitString1 is not euqal bitString2" << std::endl;
    }

    std::cout << "The value of bitString1[2]: " << bitString1.getBit(1) << std::endl;
}