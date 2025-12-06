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

size_t find_range(const std::vector<std::pair<uint64_t, uint64_t>>& sorted_ranges, uint64_t x) {
    size_t L = 0, R = sorted_ranges.size();

    while (L < R) {
        const auto M = L + (R - L) / 2;
        auto [a, b] = sorted_ranges[M];

        if (x < a) {
            R = M;
        } else if (x > b) {
            L = M+1;
        } else {
            return M;
        }
    }

    return -1;
}

void part_one() {
    std::ifstream input("../../inputs/day5/input.txt");
    if (!input.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return;
    }

    std::vector<std::pair<uint64_t, uint64_t>> ranges;

    std::string line;
    while (std::getline(input, line)) {
        if (line.empty()) break;

        auto break_idx = line.find_first_of('-');
        assert(break_idx != std::string::npos);

        uint64_t a = std::stoull(line.substr(0, break_idx));
        uint64_t b = std::stoull(line.substr(break_idx + 1));

        ranges.emplace_back(a, b);
    }

    std::ranges::sort(ranges.begin(), ranges.end(), [](auto a, auto b) {
        // Sort by first val
        return a.first < b.first;
    });

    // Merge
    std::vector<std::pair<uint64_t, uint64_t>> sorted_ranges;
    for (auto [a, b] : ranges) {
        if (sorted_ranges.empty() || a > sorted_ranges.back().second) {
            sorted_ranges.emplace_back(a, b);
        } else {
            sorted_ranges.back().second = std::max(sorted_ranges.back().second, b);
        }
    }

    uint64_t result = 0;

    while (std::getline(input, line)) {
        const auto x = std::stoull(line);
        result += find_range(sorted_ranges, x) != -1;
    }

    std::cout << result << "\n";
}

void part_two() {
    std::ifstream input("../../inputs/day5/input.txt");
    if (!input.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return;
    }

    std::vector<std::pair<uint64_t, uint64_t>> ranges;

    std::string line;
    while (std::getline(input, line)) {
        if (line.empty()) break;

        auto break_idx = line.find_first_of('-');
        assert(break_idx != std::string::npos);

        uint64_t a = std::stoull(line.substr(0, break_idx));
        uint64_t b = std::stoull(line.substr(break_idx + 1));

        ranges.emplace_back(a, b);
    }

    std::ranges::sort(ranges.begin(), ranges.end(), [](auto a, auto b) {
        // Sort by first val
        return a.first < b.first;
    });

    // Merge
    std::vector<std::pair<uint64_t, uint64_t>> sorted_ranges;
    for (auto [a, b] : ranges) {
        if (sorted_ranges.empty() || a > sorted_ranges.back().second) {
            sorted_ranges.emplace_back(a, b);
        } else {
            sorted_ranges.back().second = std::max(sorted_ranges.back().second, b);
        }
    }

    uint64_t result = 0;
    for (auto [a, b] : sorted_ranges) {
        result += b-a+1; // 5-10
    }

    std::cout << result << "\n";
}