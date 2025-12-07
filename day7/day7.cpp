//
// Created by kapil on 7.12.2025.
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
}

void part_two() {
    std::ifstream input("../../inputs/day7/input.txt");
    if (!input.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return;
    }

    std::string line;
    int line_idx = 0;
    std::getline(input, line); // Skip 0-th line

    auto start_idx = line.size() / 2;
    assert(line[start_idx] == 'S');

    uint64_t split_count = 0;
    std::vector<std::vector<int>> splitters;

    while (std::getline(input, line)) {
        line_idx++;
        if (line_idx % 2 == 1) continue; // Skip every odd line (irrelevant)

        auto curr_splits = std::vector<int>();

        for (auto i = 0; i < 1+(line_idx/2)*2; i++) {
            if (line[start_idx + i] == '^') curr_splits.push_back(i+1);
        }

        splitters.emplace_back(curr_splits);

        start_idx--;
    }

    std::vector<uint64_t> data(1+splitters.size()*2, 1);

    for (int i = splitters.size() - 1; i >= 0; i--) {
        auto splitter_base = (splitters.size()-1 - i);
        for (auto idx : splitters[i]) {
            auto converted_idx = idx + splitter_base;
            data[converted_idx] = data[converted_idx-1] + data[converted_idx+1];
        }
    }

    std::cout << data[line.size()/2-1] + data[line.size()/2+1] << "\n";
}


void part_one() {
    std::ifstream input("../../inputs/day7/input.txt");
    if (!input.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return;
    }

    std::string line;
    int line_idx = 0;
    std::getline(input, line); // Skip 0-th line

    std::vector<bool> last_lights;
    last_lights.push_back(true);

    auto start_idx = line.size() / 2;
    assert(line[start_idx] == 'S');

    uint64_t split_count = 0;

    while (std::getline(input, line)) {
        line_idx++;
        if (line_idx % 2 == 1) continue; // Skip every odd line (irrelevant)
        std::vector<bool> curr_lights(last_lights.size()+2);

        // bool left_lit = false; tbf useless
        for (auto i = 0; i < last_lights.size(); i++) {
            if (!last_lights[i]) continue;

            if (line[start_idx + i] == '^') {
                curr_lights[i] = true;
                curr_lights[(i+1)+1] = true;
                split_count++;
            } else {
                curr_lights[(i+1)] = true;
            }
        }

        last_lights = std::move(curr_lights);
        start_idx--;
    }

    std::cout << split_count << "\n";
}