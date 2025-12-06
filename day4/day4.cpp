//
// Created by kapil on 6.12.2025.
//

#include <cmath>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <unordered_set>

void part_one();
void part_two();
void parse_line(const std::string& line, std::vector<std::vector<int>>& grid,
    std::unordered_set<uint64_t>& valid_rolls, std::unordered_set<uint64_t>& global_roll_set);

int main() {
    part_two();
}

void part_one() {
    std::ifstream input("../../inputs/day4/input.txt");
    if (!input.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return;
    }

    std::string line;
    std::getline(input, line);

    // Create our grid
    std::vector<std::vector<int>> grid;
    grid.reserve(1000); // Overkill

    std::unordered_set<uint64_t> valid_rolls;
    std::unordered_set<uint64_t> global_roll_set; // It's only needed for day 2, but im not making a separate func lol
    valid_rolls.reserve(10000);
    global_roll_set.reserve(10000);

    // Empty line, thanks to which I won't need to do bounds checks on top/bottom + no need to pass line-width as arg
    // IMPORTANT: don't take into account the first and last line of the grid
    grid.emplace_back(line.size());
    grid.emplace_back(line.size()); // First proper line

    do {
        parse_line(line, grid, valid_rolls, global_roll_set);
    } while (std::getline(input, line));

    std::cout << valid_rolls.size() << "\n";
}

// roll = grid_line_idx * line_width + x
// x < line_width
void remove_roll(
    std::vector<std::vector<int>>& grid,
    uint64_t roll,
    std::unordered_set<uint64_t>& global_roll_set)
{
    auto line_width = grid[0].size();

    auto curr_grid_line = roll / line_width;
    auto curr_roll = roll % line_width;

    auto start_idx = curr_roll == 0 ? 1 : 0;
    auto end_idx = curr_roll == line_width - 1 ? 2 : 3;

    // TODO: remove the current roll from the global roll set
    global_roll_set.erase(roll);

    auto grids = std::array{&grid[curr_grid_line-1], &grid[curr_grid_line], &grid[curr_grid_line+1]};
    for (int n = 0; n < grids.size(); n++) {
        auto grid_ref = grids[n];
        for (int j = start_idx; j < end_idx; j++) {
            if (j == 1 && grid_ref == &grid[curr_grid_line]) continue; // Probably fine to omit this line but whatever
            (*grid_ref)[curr_roll+j-1]--; // hacky but whatever

            // This probably would've worked
            // But i had a bug with global_roll_set lol

            // auto curr = (*grid_ref)[curr_roll+j-1];
            // if (curr < 4) {
            //     // TODO: Pass in a set containing all roll positions, so i can simply check if an idx was originally a roll
            //     auto roll_idx = (curr_grid_line - 1 + n) * line_width + curr_roll+j-1;
            //     if (global_roll_set.contains(roll_idx)) {
            //         valid_rolls.insert(roll_idx);
            //     }
            //
            //     // auto idx = (curr_grid_idx-1 + n) * line.size() + i+j-1;
            //
            //     // We don't need to check actually if it's there
            //     // Only for debugging
            //     // if (valid_rolls.contains(idx)) {
            //     //     std::cout << "Removed " << idx - curr_grid_idx << "\n"; // -curr_grid_idx for debugging
            //     // }
            //
            //     // valid_rolls.erase(idx);
            // }
        }
    }
}

void insert_new_valids(std::vector<std::vector<int>>& grid,
    std::unordered_set<uint64_t>& valid_rolls,
    const std::unordered_set<uint64_t>& global_roll_set) {
    // NOTE: I just realized that this is stupid
    // Just iterate over global_roll set bruh
    // too lazy tho

    auto line_width = grid[0].size();
    for (int i = 1; i < grid.size()-1; i++) {
        for (int j = 0; j < line_width; j++) {
            auto glob_idx = i * line_width + j;
            if (!global_roll_set.contains(glob_idx)) continue;
            auto x = grid[i][j];
            if (x < 4) {
                valid_rolls.insert(glob_idx);
            }
        }
    }
}

void part_two() {
    std::ifstream input("../../inputs/day4/input.txt");
    if (!input.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return;
    }

    std::string line;
    std::getline(input, line);

    // Create our grid
    std::vector<std::vector<int>> grid;
    grid.reserve(1000); // Overkill

    std::unordered_set<uint64_t> valid_rolls;
    std::unordered_set<uint64_t> global_roll_set;
    valid_rolls.reserve(10000);
    global_roll_set.reserve(10000);

    // Empty line, thanks to which I won't need to do bounds checks on top/bottom + no need to pass line-width as arg
    // IMPORTANT: don't take into account the first and last line of the grid
    grid.emplace_back(line.size());
    grid.emplace_back(line.size()); // First proper line

    do {
        parse_line(line, grid, valid_rolls, global_roll_set);
    } while (std::getline(input, line));

    uint64_t res = 0;

    std::unordered_set<uint64_t> new_rolls;
    new_rolls.reserve(10000);

    do {
        // std::cout << "Removing: " << valid_rolls.size() << "\n";
        res += valid_rolls.size();

        for (auto roll : valid_rolls) {
            remove_roll(grid, roll, global_roll_set);
        }

        valid_rolls.clear();
        insert_new_valids(grid, valid_rolls, global_roll_set);
    } while (!valid_rolls.empty());

    std::cout << res << "\n";
}

void parse_line(const std::string& line, std::vector<std::vector<int>>& grid,
    std::unordered_set<uint64_t>& valid_rolls, std::unordered_set<uint64_t>& global_roll_set) {
    auto curr_grid_idx = grid.size()-1;

    auto& last_grid_line = grid[curr_grid_idx-1];
    auto& curr_grid_line = grid[curr_grid_idx];
    auto& next_grid_line = grid.emplace_back(line.size());

    for (int i = 0; i < line.size(); i++) {
        char c = line[i];
        if (c != '@') continue;

        global_roll_set.insert(curr_grid_idx * line.size() + i);

        auto start_idx = i == 0 ? 1 : 0;
        auto end_idx = i == line.size() - 1 ? 2 : 3;

        auto grids = std::array{&last_grid_line, &curr_grid_line, &next_grid_line};
        for (int n = 0; n < grids.size(); n++) {
            auto grid_ref = grids[n];
            for (int j = start_idx; j < end_idx; j++) {
                if (j == 1 && grid_ref == &curr_grid_line) continue;
                (*grid_ref)[i+j-1]++; // hacky but whatever

                auto curr = (*grid_ref)[i+j-1];
                if (curr >= 4) {
                    auto idx = (curr_grid_idx-1 + n) * line.size() + i+j-1;

                    // We don't need to check actually if it's there
                    // Only for debugging
                    // if (valid_rolls.contains(idx)) {
                    //     std::cout << "Removed " << idx - curr_grid_idx << "\n"; // -curr_grid_idx for debugging
                    // }

                    valid_rolls.erase(idx);
                }
            }
        }

        if (curr_grid_line[i] < 4) {
            valid_rolls.insert(curr_grid_idx * line.size() + i);
            // std::cout << "Adding: " << (curr_grid_idx-1) * line.size() + i << "\n"; // -curr_grid_idx, see removal
        }
    }
}