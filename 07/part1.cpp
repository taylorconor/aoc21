#include <fstream>
#include <iostream>
#include <vector>

#include "absl/strings/str_split.h"

int main() {
  std::ifstream input;
  input.open("07/input.txt");
  std::string line;
  std::getline(input, line);
  std::vector<std::string> number_strs = absl::StrSplit(line, ",");
  std::vector<int> numbers;
  for (const auto& str : number_strs) {
    numbers.push_back(std::stoi(str));
  }
  std::nth_element(numbers.begin(), numbers.begin() + (numbers.size() / 2),
                   numbers.end());
  int fuel = 0;
  for (auto number : numbers) {
    fuel += std::abs(number - numbers[numbers.size() / 2]);
  }
  std::cout << "Fuel: " << fuel << std::endl;
}
