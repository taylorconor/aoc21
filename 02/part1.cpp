#include <fstream>
#include <iostream>

#include "absl/strings/match.h"
#include "absl/strings/str_split.h"

int main() {
  std::ifstream input;
  input.open("02/input.txt");
  std::string line;
  int horizontal = 0, depth = 0;
  while (std::getline(input, line)) {
    std::vector<std::string> split = absl::StrSplit(line, ' ');
    int num = std::stoi(split[1]);
    if (split[0] == "forward") {
      horizontal += num;
    } else if (split[0] == "down") {
      depth += num;
    } else if (split[0] == "up") {
      depth -= num;
    }
  }
  std::cout << "Position: " << horizontal * depth << std::endl;
}
