#include <fstream>
#include <iostream>

int main() {
  std::ifstream input;
  input.open("03/input.txt");
  std::string line;
  int ones[12] = {};
  int total_nums = 0;
  while (std::getline(input, line)) {
    int num = std::stoi(line, 0, 2);
    total_nums++;
    for (int i = 0; i < 12; ++i) {
      ones[i] += (bool)(num & (1 << i));
    }
  }
  uint16_t gamma = 0;
  for (int i = 0; i < 12; ++i) {
    if (ones[i] * 2 > total_nums) {
      gamma += 1 << i;
    }
  }
  std::cout << "Power: " << gamma * (~gamma & 0xFFF) << std::endl;
}
