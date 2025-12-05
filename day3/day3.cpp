//
// Created by kapil on 5.12.2025.
//

#include <cmath>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <array>

uint64_t fastpow(uint64_t a, uint64_t b) {
    uint64_t res = 1;

    while (b > 0) {
        if (b & 1) res *= a;
        a *= a;
        b >>= 1;
    }

    return res;
}

void part_two() {
    std::ifstream input("../../inputs/day3/input.txt");
    if (!input.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return;
    }

    std::string line;
    uint64_t res = 0;

    std::array<int, 12> maxes{};

    while (std::getline(input, line)) {
        maxes = {};
        for (int i = 0; i < line.size(); i++) {
            int num = line[i] - '0';
            int remaining_digits = line.size() - i - 1;

            for (int j = 0; j < 12; j++) {
                if (num > maxes[j] && remaining_digits >= 12-j-1) {
                    maxes[j] = num;
                    // Fill the rest of the maxes with zeros, forces to refill them
                    for (int k = j + 1; k < 12; k++) {
                        maxes[k] = 0;
                    }

                    break;
                }
            }
        }

        uint64_t temp = 0;
        for (int i = 0; i < 12; i++) {
            temp += maxes[i] * fastpow(10, 12-i-1);
        }

        res += temp;
    }

    std::cout << res << "\n";
}

int main() {
    part_two();
    // std::ifstream input("../../inputs/day3/input.txt");
    // if (!input.is_open()) {
    //     std::cerr << "Failed to open input.txt" << std::endl;
    //     return 1;
    // }
    //
    // std::string line;
    // uint64_t res = 0;
    // while (std::getline(input, line)) {
    //     int curr_max = 0;
    //     int sub_max = 0;
    //     for (int i = 0; i < line.size(); i++) {
    //         int num = line[i] - '0';
    //
    //         if (num > curr_max && i != line.size() - 1) {
    //             curr_max = num;
    //             sub_max = line[i + 1] - '0';
    //         } else if (num > sub_max) {
    //             sub_max = num;
    //         }
    //     }
    //
    //     res += curr_max * 10 + sub_max;
    // }
    //
    // std::cout << res << "\n";

    return 0;
}