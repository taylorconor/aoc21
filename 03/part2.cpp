#include <fstream>
#include <iostream>

// Trie structure.
struct Node {
  std::unique_ptr<Node> zero = nullptr;
  std::unique_ptr<Node> one = nullptr;
  Node *parent = nullptr;

  explicit Node(Node *parent) : parent(parent) {}

  int GetNodeCount() {
    int children = 0;
    if (zero) {
      children += zero->GetNodeCount();
    }
    if (one) {
      children += one->GetNodeCount();
    }
    // Include this node in the node count if it's a leaf.
    return children ? children : 1;
  }

  std::string GetValue() {
    if (!parent) {
      return "";
    }
    return parent->GetValue() + (parent->zero.get() == this ? "0" : "1");
  }
};

void AddToRoot(Node *root, const std::string &str) {
  Node *node = root;
  for (char c : str) {
    auto &sub_ptr = (c == '0') ? node->zero : node->one;
    if (!sub_ptr) {
      sub_ptr = std::make_unique<Node>(node);
    }
    node = sub_ptr.get();
  }
}

int main() {
  std::ifstream input;
  input.open("03/input.txt");
  std::string line;
  Node root(nullptr);
  while (std::getline(input, line)) {
    AddToRoot(&root, line);
  }
  Node *oxygen = &root, *co2 = &root;
  for (int i = 0; i < line.length(); ++i) {
    // Progress oxygen pointer.
    if (oxygen->zero && oxygen->one) {
      if (oxygen->one->GetNodeCount() >= oxygen->zero->GetNodeCount()) {
        oxygen = oxygen->one.get();
      } else {
        oxygen = oxygen->zero.get();
      }
    } else {
      oxygen = oxygen->zero ? oxygen->zero.get() : oxygen->one.get();
    }
    // Progress co2 pointer.
    if (co2->zero && co2->one) {
      if (co2->zero->GetNodeCount() <= co2->one->GetNodeCount()) {
        co2 = co2->zero.get();
      } else {
        co2 = co2->one.get();
      }
    } else {
      co2 = co2->zero ? co2->zero.get() : co2->one.get();
    }
  }
  int oxygen_val = std::stoi(oxygen->GetValue(), 0, 2);
  int co2_val = std::stoi(co2->GetValue(), 0, 2);
  std::cout << "Rating: " << oxygen_val * co2_val << std::endl;
}