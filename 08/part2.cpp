#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "absl/strings/str_split.h"

using Mapping = std::array<std::set<char>, 10>;

Mapping CreateMapping(const std::vector<std::set<char>>& inputs) {
  Mapping mapping;

  // Calculate 1 and cf from digit 1.
  std::set<char> cf;
  for (auto& input : inputs) {
    if (input.size() == 2) {
      mapping[1] = input;
      cf = input;
      break;
    }
  }

  // Calculate 7 and a from digit 7 - cf.
  std::set<char> a;
  for (auto& input : inputs) {
    if (input.size() == 3) {
      mapping[7] = input;
      std::set_difference(input.begin(), input.end(), cf.begin(), cf.end(),
                          std::inserter(a, a.end()));
      break;
    }
  }

  // Calculate 4 and bd from digit 4 - cf.
  std::set<char> bd;
  for (auto& input : inputs) {
    if (input.size() == 4) {
      mapping[4] = input;
      std::set_difference(input.begin(), input.end(), cf.begin(), cf.end(),
                          std::inserter(bd, bd.end()));
      break;
    }
  }

  // Calculate 8 and eg from digit 8 - cf - a - bd.
  std::set<char> eg;
  for (auto& input : inputs) {
    if (input.size() == 7) {
      mapping[8] = input;
      eg = input;
      for (auto& val : cf) {
        eg.erase(val);
      }
      for (auto& val : a) {
        eg.erase(val);
      }
      for (auto& val : bd) {
        eg.erase(val);
      }
      break;
    }
  }

  std::set<char> b;
  // Calculate the three 6-digit numbers: 0, 9 and 6.
  for (auto& input : inputs) {
    if (input.size() == 6) {
      // Calculate 0 and b from 0 and bd.
      if (!std::includes(input.begin(), input.end(), bd.begin(), bd.end())) {
        mapping[0] = input;
        std::set<char> d;
        std::set_difference(bd.begin(), bd.end(), input.begin(), input.end(),
                            std::inserter(d, d.end()));
        std::set_difference(bd.begin(), bd.end(), d.begin(), d.end(),
                            std::inserter(b, b.end()));
      }
      // Calculate 9 from digit 9 and cf.
      else if (std::includes(input.begin(), input.end(), bd.begin(),
                             bd.end()) &&
               std::includes(input.begin(), input.end(), cf.begin(),
                             cf.end())) {
        mapping[9] = input;
      }
      // Calculate 6 by elimination.
      else if (std::includes(input.begin(), input.end(), bd.begin(),
                             bd.end()) &&
               !std::includes(input.begin(), input.end(), cf.begin(),
                              cf.end())) {
        mapping[6] = input;
      }
    }
  }

  // Calculate the three 5-digit numbers: 2, 3 and 5.
  for (auto& input : inputs) {
    if (input.size() == 5) {
      if (std::includes(input.begin(), input.end(), b.begin(), b.end())) {
        mapping[5] = input;
      } else if (std::includes(input.begin(), input.end(), eg.begin(),
                               eg.end())) {
        mapping[2] = input;
      } else {
        mapping[3] = input;
      }
    }
  }

  return mapping;
}

int ApplyMapping(const Mapping& mapping,
                 const std::vector<std::set<char>>& output_set) {
  int sum = 0;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 10; ++j) {
      if (output_set[i] == mapping[j]) {
        sum += std::pow(10, 3 - i) * j;
      }
    }
  }
  return sum;
}

int main() {
  std::ifstream input;
  input.open("08/input.txt");
  std::string line;
  int sum = 0;
  while (std::getline(input, line)) {
    std::pair<std::string, std::string> pair = absl::StrSplit(line, "|");
    std::vector<std::string> inputs = absl::StrSplit(pair.first, " ");
    std::vector<std::set<char>> input_set;
    for (const auto& str : inputs) {
      input_set.emplace_back(str.begin(), str.end());
    }
    Mapping mapping = CreateMapping(input_set);
    std::vector<std::string> outputs =
        absl::StrSplit(pair.second, " ", absl::SkipEmpty());
    std::vector<std::set<char>> output_set;
    for (const auto& str : outputs) {
      output_set.emplace_back(str.begin(), str.end());
    }
    sum += ApplyMapping(mapping, output_set);
  }
  std::cout << "Sum: " << sum << std::endl;
}
