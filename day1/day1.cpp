//
// Created by kapil on 4.12.2025.
//

#include <cmath>
#include <iostream>
#include <fstream>

void first_puzzle();
void second_puzzle();

int main() {
    // first_puzzle();
    second_puzzle();

    return 0;
}

void second_puzzle() {
    std::ifstream input("../../inputs/day1/input.txt");
    if (!input.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return;
    }

    int curr = 50;
    int result = 0;
    std::string line;
    while (std::getline(input, line)) {
        char dir = line[0];
        int value = std::stoi(line.substr(1));

        // if value >= 100, we may have additional rotations
        // We can fix that by simply adding value/100 to the result
        result += value / 100;

        value %= 100;
        value *= (dir == 'R' ? 1 : -1);

        curr += value;

        // curr - value = prev value, if prev was at 0 we don't want to count that rotation
        result += curr - value != 0 && (curr >= 100 || curr <= 0);

        curr = (curr + 100) % 100; // wrap around 0-99
    }

    std::cout << result << "\n";
}


void first_puzzle() {
    std::ifstream input("../../inputs/day1/input.txt");
    if (!input.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return;
    }

    int curr = 50;
    int result = 0;
    std::string line;
    while (std::getline(input, line)) {
        char dir = line[0];
        int value = std::stoi(line.substr(1));

        value %= 100;
        value *= (dir == 'R' ? 1 : -1);

        curr += value;
        curr = (curr + 100) % 100; // wrap around 0-99

        result += curr == 0;
    }

    std::cout << result << "\n";
}