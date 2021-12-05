#include <fstream>
#include <iostream>

#include "absl/strings/str_split.h"

struct Coord {
  explicit Coord(const std::string &str) {
    std::vector<std::string> pieces = absl::StrSplit(str, ',');
    x = std::stoi(pieces[0]);
    y = std::stoi(pieces[1]);
  }

  int x = 0;
  int y = 0;
};

int main() {
  std::ifstream input;
  input.open("05/input.txt");
  std::string line;
  std::array<std::array<int, 1000>, 1000> counts = {};
  while (std::getline(input, line)) {
    std::vector<std::string> points = absl::StrSplit(line, " -> ");
    Coord start(points[0]);
    Coord end(points[1]);
    if (start.x == end.x) {
      for (int i = std::min(start.y, end.y); i <= std::max(start.y, end.y);
           ++i) {
        counts[start.x][i]++;
      }
    } else if (start.y == end.y) {
      for (int i = std::min(start.x, end.x); i <= std::max(start.x, end.x);
           ++i) {
        counts[i][start.y]++;
      }
    }
  }
  int total = 0;
  for (int x = 0; x < 1000; x++) {
    for (int y = 0; y < 1000; y++) {
      if (counts[x][y] > 1) {
        total++;
      }
    }
  }
  std::cout << "Overlap: " << total << std::endl;
}
