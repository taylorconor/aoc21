#include <fstream>
#include <iostream>

int main() {
  std::ifstream input;
  input.open("01/input.txt");
  int prev_num = -1;
  int amount = 0;
  std::string line;
  while (std::getline(input, line)) {
    int num = std::stoi(line);
    if (num > prev_num && prev_num >= 0) {
      amount++;
    }
    prev_num = num;
  }
  std::cout << "Amount: " << amount << std::endl;
}
