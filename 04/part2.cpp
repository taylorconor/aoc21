#include <fstream>
#include <iostream>

#include "absl/strings/str_split.h"

struct Board {
  explicit Board(const std::string &str) {
    int row = 0;
    for (auto &line : absl::StrSplit(str, '\n')) {
      int col = 0;
      for (auto &num : absl::StrSplit(line, ' ')) {
        if (num.empty()) {
          continue;
        }
        board[row][col] = std::make_pair(std::stoi(num.data()), false);
        col++;
      }
      if (!line.empty()) {
        row++;
      }
    }
  }

  void ApplyNumber(int num) {
    for (int row = 0; row < 5; ++row) {
      for (int col = 0; col < 5; ++col) {
        if (board[row][col].first == num) {
          board[row][col].second = true;
        }
      }
    }
  }

  bool IsWinning() {
    int col_sum[5] = {};
    for (int row = 0; row < 5; ++row) {
      int row_sum = 0;
      for (int col = 0; col < 5; ++col) {
        row_sum += board[row][col].second;
        col_sum[col] += board[row][col].second;
        if (col_sum[col] == 5) {
          return true;
        }
      }
      if (row_sum == 5) {
        return true;
      }
    }
    return false;
  }

  int SumUnmarked() {
    int sum = 0;
    for (int row = 0; row < 5; ++row) {
      for (int col = 0; col < 5; ++col) {
        if (!board[row][col].second) {
          sum += board[row][col].first;
        }
      }
    }
    return sum;
  }

  std::array<std::array<std::pair<int, bool>, 5>, 5> board;
};

int main() {
  std::ifstream input;
  input.open("04/input.txt");
  std::string line;
  std::getline(input, line);
  std::vector<int> numbers;
  for (auto &num : absl::StrSplit(line, ",")) {
    numbers.push_back(std::stoi(num.data()));
  }
  std::vector<Board> boards;
  std::string board_content;
  while (std::getline(input, line)) {
    if (line.empty() && !board_content.empty()) {
      boards.emplace_back(board_content);
      board_content = "";
    } else {
      board_content += '\n' + line;
    }
  }
  for (auto num : numbers) {
    auto board = boards.begin();
    while (board != boards.end()) {
      board->ApplyNumber(num);
      if (board->IsWinning()) {
        if (boards.size() == 1) {
          std::cout << "Score: " << num * board->SumUnmarked() << std::endl;
          return 0;
        }
        board = boards.erase(board);
      } else {
        board++;
      }
    }
  }
}
