//
// Created by kapil on 5.12.2025.
//

#include "day2.h"

// Probably a way to calculate this in O(1)
// using mirrors get first possible value and last valid value and simply
// add in whatevers in the middle

// e.g.
// 998-1220
// 998 -> 1000
// 10|00 -> first value 1010
// 12|20 -> last value is 1212
// Between them should be as well 1111

// Couldn't be bothered though, since this works lol
uint64_t calc(uint64_t x, uint64_t y, int x_len, int y_len) {
    uint64_t res = 0;

    // Impossible to create two halves
    if (x_len == y_len && x_len % 2 != 0) return 0;

    auto cut_point = x_len/2 + x_len % 2;
    auto base = x / fastpow(10, cut_point);

    auto base_digit_len = x_len / 2;

    while (true) {
        if (base >= fastpow(10, base_digit_len)) base_digit_len++;

        uint64_t curr = 0;
        for (int i = 0; i < 2; i++) {
            curr += base * fastpow(10, i * base_digit_len);
        }

        base++;
        if (curr < x) continue;

        if (curr <= y) {
            res += curr;
        } else break;
    }

    return res;
}

void first_puzzle() {
    std::ifstream input("../../inputs/day2/input.txt");
    if (!input.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return;
    }

    std::string data;
    input >> data;

    std::string temp;
    temp.reserve(data.size());

    uint64_t result = 0;
    uint64_t first = 0;
    int L = 0;
    int x_len = 0;
    for (int i = 0; i < data.size(); ++i) {
        char c = data[i];
        if (c == '-') {
            uint64_t x = std::stoll(data.substr(L, i));
            first = x;
            x_len = i - L;
            L = i + 1;
            continue;
        }

        if (c == ',' || i == data.size() - 1) {
            uint64_t x = std::stoll(data.substr(L, i));

            // calculate
            result += calc(first, x, x_len, i - L);

            L = i + 1;
        }
    }

    std::cout << result << "\n";
}