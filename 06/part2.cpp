#include <fstream>
#include <iostream>
#include <unordered_map>

#include "absl/strings/str_cat.h"
#include "absl/strings/str_split.h"

uint64_t CountFish(int64_t time_to_respawn, int64_t remaining_days) {
  static std::unordered_map<std::string, uint64_t> memo;
  auto key = absl::StrCat(time_to_respawn, ",", remaining_days);
  if (memo.find(key) != memo.end()) {
    return memo.at(key);
  }
  uint64_t fish = 1;
  if (remaining_days >= 0 && time_to_respawn < remaining_days) {
    fish += CountFish(6, remaining_days - time_to_respawn - 1) - 1;
    fish += CountFish(6, remaining_days - time_to_respawn - 3);
  }
  memo[key] = fish;
  return fish;
}

int main() {
  std::ifstream input;
  input.open("06/input.txt");
  std::string line;
  std::getline(input, line);
  std::vector<std::string> strings = absl::StrSplit(line, ',');
  uint64_t fish = 0;
  for (const auto& str : strings) {
    fish += CountFish(std::stoi(str), 256);
  }
  std::cout << "Fish: " << fish << std::endl;
}
