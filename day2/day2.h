//
// Created by kapil on 5.12.2025.
//

#ifndef AOC2025_DAY2_H
#define AOC2025_DAY2_H

#include <cmath>
#include <cstdint>
#include <iostream>
#include <fstream>

void first_puzzle();
void second_puzzle();

inline uint64_t fastpow(uint64_t a, uint64_t b) {
    uint64_t res = 1;

    while (b > 0) {
        if (b & 1) res *= a;
        a *= a;
        b >>= 1;
    }

    return res;
}

#endif //AOC2025_DAY2_H