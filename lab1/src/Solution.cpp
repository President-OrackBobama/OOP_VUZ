#pragma once
#include <iostream>
#include <string>


long eliminate_unset_bits(std::string number){
    std::string out;
    for (char ch : number) {
        if (ch == '1') {
            out += ch;
        }
    }

    int count = 0;
    if (out.length() == 0) {
        return 0;
    }
    else {
        for(int i = 0; i < out.length(); ++i){
            count = 1 + count*2;
        }
    }
    return count;
}