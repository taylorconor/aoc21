#include <fstream>
#include <iostream>
#include <vector>

#include "absl/strings/str_split.h"

int get_fuel(int i, const std::vector<int>& nums) {
  int fuel = 0;
  for (int num : nums) {
    int n = std::abs(num - i);
    fuel += (n * (n + 1)) / 2;
  }
  return fuel;
}

int main() {
  std::ifstream input;
  input.open("07/input.txt");
  std::string line;
  std::getline(input, line);
  std::vector<std::string> number_strs = absl::StrSplit(line, ",");
  std::vector<int> numbers;
  for (const auto& str : number_strs) {
    int num = std::stoi(str);
    numbers.push_back(num);
  }
  std::sort(numbers.begin(), numbers.end());
  int min = INT_MAX;
  for (int i = numbers[0]; i < numbers.back(); i++) {
    int fuel = get_fuel(i, numbers);
    if (fuel < min) {
      min = fuel;
    }
  }
  std::cout << "Fuel: " << min << std::endl;
}
