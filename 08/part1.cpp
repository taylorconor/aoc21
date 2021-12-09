#include <fstream>
#include <iostream>
#include <vector>

#include "absl/strings/str_split.h"

int main() {
  std::ifstream input;
  input.open("08/input.txt");
  std::string line;
  int count = 0;
  while (std::getline(input, line)) {
    std::pair<std::string, std::string> pair = absl::StrSplit(line, "|");
    std::vector<std::string> outputs = absl::StrSplit(pair.second, " ");
    for (const auto& output : outputs) {
      int sz = output.size();
      if (sz == 2 || sz == 3 || sz == 4 || sz == 7) {
        count++;
      }
    }
  }
  std::cout << "Count: " << count << std::endl;
}
