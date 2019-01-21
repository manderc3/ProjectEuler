#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <memory>
#include <queue>
#include <stack>
#include <vector>

struct Node
{
  std::shared_ptr<Node> parent = nullptr, left = nullptr, right = nullptr;
  int val;
  Node(int v) : val(v) {}
};

size_t find_maximum_sum(const std::shared_ptr<Node> node)
{
  return 0;
}

template<int size>
std::shared_ptr<Node> construct_tree(const std::array<int, size>& vals)
{
  std::array<std::shared_ptr<Node>, size> nodes;

  // New up nodes and assign values on first run
  for (unsigned i = 0; i < size; i++) {
    nodes[i] = std::make_shared<Node>(vals[i]);
  }

  unsigned row = 0, counter = 0;

  // On second run, establish edges between nodes
  for (unsigned i = 0; i < size; i++) {
    auto node = nodes[i];
    auto left_index = i + row + 1;
    auto right_index = i + row + 2;
    
    if (right_index < size) {
      node->left = nodes[left_index];
      node->right = nodes[right_index];

      if (node != nodes.front()) {
	node->left->parent  = node;
	node->right->parent = node;
      }
      
      if (counter == row) {
	++row;
	counter = 0;
      }
      else {
	++counter;
      }
    }
  }
  
  return nodes.front();
}

int main()
{
  std::array<int, 10> triangle_numbers = { 3, 7, 4, 2, 4, 6, 8, 5, 9, 3 };

  auto t1 = std::chrono::system_clock::now();
  
  auto result = find_maximum_sum(construct_tree<triangle_numbers.size()>(triangle_numbers));

  auto t2 = std::chrono::system_clock::now();

  std::chrono::duration<double, std::milli> dur = t2 - t1;
  std::cout << "Time taken (milliseconds): " << dur.count() << "\n";
  return 0;
}
