//
// Created by kapil on 5.12.2025.
//

#include "day2.h"

uint64_t compose_num(uint64_t base, int base_len, int rep_count) {
    uint64_t res = 0;

    for (int i = 0; i < rep_count; i++) {
        res += base * fastpow(10, i * base_len);
    }

    return res;
}



// TODO: write ts
// Same thing as part_one but perform additional passes on 1/n, where n is a prime
// stop when len/n < 2
uint64_t calc_d2(uint64_t x, uint64_t y, int x_len, int y_len) {
    uint64_t result = 0;

    // 1 - len/2
    for (int i = 1; i <= x_len/2; i++) {

    }

    return result;
}

void second_puzzle() {
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
            result += calc_d2(first, x, x_len, i - L);

            L = i + 1;
        }
    }

    std::cout << result << "\n";
}