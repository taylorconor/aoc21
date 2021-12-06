#include <fstream>
#include <iostream>

#include "absl/strings/str_cat.h"

int main() {
  std::ifstream input;
  input.open("06/input.txt");
  std::string line;
  std::getline(input, line);
  std::vector<std::string> strings = absl::StrSplit(line, ',');
  std::vector<int> fish;
  for (auto& str : strings) {
    fish.push_back(std::stoi(str));
  }
  for (int i = 0; i < 80; ++i) {
    int to_add = 0;
    for (int& f : fish) {
      if (f == 0) {
        f = 6;
        to_add++;
      } else {
        f--;
      }
    }
    fish.insert(fish.end(), to_add, 8);
  }
  std::cout << "Fish: " << fish.size() << std::endl;
}
