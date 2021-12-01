#include <fstream>
#include <iostream>
#include <vector>

int main() {
  std::ifstream input;
  input.open("01/input.txt");
  std::vector<int> sums = {0};
  std::string line;
  int amount = 0;
  while (std::getline(input, line)) {
    int num = std::stoi(line);
    sums.push_back(sums.empty() ? num : num + sums.back());
    const auto& size = sums.size() - 1;
    if (size > 3 &&
        (sums[size] - sums[size - 3]) > (sums[size - 1] - sums[size - 4])) {
      amount++;
    }
  }
  std::cout << "Amount: " << amount << std::endl;
}
