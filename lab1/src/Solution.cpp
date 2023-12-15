#pragma once
#include <iostream>
#include <string>


long eliminate_unset_bits(const std::string& number) {
    size_t count = 0;

    for (char ch : number) {
        if (ch == '1') {
            count = count * 2 + 1;
        }
    }

    return count;
}