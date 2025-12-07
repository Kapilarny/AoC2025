//
// Created by kapil on 6.12.2025.
//

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <array>
#include <cassert>
#include <vector>
#include <unordered_set>

void part_one();
void part_two();

int main() {
    // part_one();
    part_two();

    return 0;
}

enum class Operation {
    PLUS = 0,
    MUL = 1
};

void part_one() {
    std::ifstream input("../../inputs/day6/input.txt");
    if (!input.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return;
    }

    std::vector<uint64_t> data;
    std::vector<Operation> operations;

    {
        std::string temp;
        while (input >> temp) {
            // std::cout << temp << "\n";

            if (temp == "*" || temp == "+") {
                operations.push_back(temp == "+" ? Operation::PLUS : Operation::MUL);
            } else {
                data.push_back(std::stoll(temp));
            }
        }
    }

    uint64_t result = 0;
    for (int i = 0; i < operations.size(); i++) {
        uint64_t temp = data[i];
        for (int j = 1; j < data.size()/operations.size(); j++) {
            auto retr = data[j*operations.size() + i];
            if (operations[i] == Operation::MUL) {
                temp *= retr;
            } else {
                temp += retr;
            }
        }

        result += temp;
    }

    std::cout << result << "\n";
}

void part_two() {
    std::ifstream input("../../inputs/day6/test.txt");
    if (!input.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return;
    }

    std::vector<uint64_t> data;
    std::vector<Operation> operations;

    {
        std::string temp;
        while (input >> temp) {
            // std::cout << temp << "\n";

            if (temp == "*" || temp == "+") {
                operations.push_back(temp == "+" ? Operation::PLUS : Operation::MUL);
            } else {
                data.push_back(std::stoll(temp));
            }
        }
    }

    uint64_t result = 0;
    for (int i = 0; i < operations.size(); i++) {
        std::vector<std::vector<uint64_t>> digs;

        // I'm lazy
        auto max_digs = 0;
        for (int j = 0; j < data.size()/operations.size(); j++) {
            auto retr = data[j*operations.size() + i];

            auto dig_idx = 0;
            while (retr != 0) {
                // if (dig_idx == digs.size()) digs.resize(dig_idx + 1);
                // digs[dig_idx].push_back(retr % 10);
                retr /= 10;
                dig_idx++;
            }

            if (dig_idx > max_digs) max_digs = dig_idx;
        }

        digs.resize(max_digs);

        for (int j = 0; j < data.size()/operations.size(); j++) {
            auto retr = data[j*operations.size() + i];
            auto dig_len = 0;
            while (retr != 0) {
                retr /= 10;
                dig_len++;
            }

            retr = data[j*operations.size() + i];
            for (int k = 0; k < dig_len; k++) {
                digs[digs.size()-1-k].push_back(retr % 10);
                retr /= 10;
            }
        }

        std::vector<uint64_t> actual_data;
        for (auto operand : digs) {
            uint64_t result = 0;
            uint64_t ten_pow = 1;
            for (int k = operand.size()-1; k >= 0; k--) {
                result += operand[k] * ten_pow;
                ten_pow *= 10;
            }

            actual_data.push_back(result);
        }

        uint64_t temp = actual_data[0];
        for (int j = 1; j < actual_data.size(); j++) {
            auto retr = actual_data[j];
            if (operations[i] == Operation::MUL) {
                temp *= retr;
            } else {
                temp += retr;
            }
        }

        for (int j = 0; j < actual_data.size(); j++) {
            std::cout << actual_data[j] << " ";
        }

        std::cout << (operations[i] == Operation::MUL ? " * " : " + ") << "\n";

        result += temp;
    }

    std::cout << result << "\n";
}