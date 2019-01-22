#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <memory>
#include <stack>
#include <vector>

struct Node
{
  std::shared_ptr<Node> parent = nullptr, left = nullptr, right = nullptr;
  int val;
  Node(int v) : val(v) {}
};

void pretty_print(const std::shared_ptr<Node> root) {
  std::vector<std::shared_ptr<Node>> nodes;

  nodes.push_back(root);

  unsigned row = 0, counter = 0;
  
  while (!nodes.empty()) {
    auto node = nodes.front();
    std::cout << node->val << " ";

    // Only add nodes if they don't currently exist in queue
    if (node->left  != nullptr && std::find(nodes.begin(), nodes.end(), node->left) == nodes.end()) {
      nodes.push_back(node->left);
    }
    if (node->right != nullptr && std::find(nodes.begin(), nodes.end(), node->right) == nodes.end()) {
      nodes.push_back(node->right);
    }

    nodes.erase(nodes.begin());

    if (row == counter) {
      ++row;
      counter = 0;
      std::cout << "\n";    
    }
    else {
      ++counter;
    }
  }  
}

std::shared_ptr<Node> get_final_node(std::shared_ptr<Node> root)
{
  auto node = root;
  while (node->right != nullptr) { node = node->right; }
  return node;
}

size_t find_maximum_sum(const std::shared_ptr<Node> root)
{
  /* The following call is a needless expense. Esp. considering large data structures. */
  // pretty_print(root);

  unsigned largest_sum = 0, current_sum = 0;
  
  std::stack<std::shared_ptr<Node>> current_path;
  std::vector<std::shared_ptr<Node>> blocked_nodes;

  auto node = root;
  
  do {
    while (node != nullptr) {
      std::cout << node->val << " ";

      current_path.push(node);
      
      if (std::find(blocked_nodes.begin(), blocked_nodes.end(), node->left) == blocked_nodes.end()) {
	node = node->left;
      }
      else if (std::find(blocked_nodes.begin(), blocked_nodes.end(), node->right) == blocked_nodes.end()) {
	node = node->right;
      }    
    }
   
    std::cout << "\n";

    node = current_path.top();
    current_path.pop();

    auto parent = current_path.top(); // node->parent not reliable as node can have two parents  

    if (parent->left == node) {
      blocked_nodes.push_back(node);
      current_path.pop();
      node = parent;
    }
    else {
      while (parent->left != node) {
	blocked_nodes.erase(std::remove(blocked_nodes.begin(), blocked_nodes.end(), parent->left), blocked_nodes.end());
	blocked_nodes.erase(std::remove(blocked_nodes.begin(), blocked_nodes.end(), parent->right), blocked_nodes.end());
	blocked_nodes.push_back(parent);

	if (blocked_nodes[0] != root) {
	  node = current_path.top();
	  current_path.pop();
	  parent = current_path.top();
	} else {
	  break; // Used to resolve the last path
	}
      }

      if (blocked_nodes[0] != root) {
	current_path.pop();
	node = parent;
      }
    }  
  } while (blocked_nodes[0] != root);
  
  return largest_sum;
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
  //std::array<int, 10> triangle_numbers = { 3, 7, 4, 2, 4, 6, 8, 5, 9, 3 };

  std::array<int, 10> triangle_numbers = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  
  auto t1 = std::chrono::system_clock::now();
  
  auto result = find_maximum_sum(construct_tree<triangle_numbers.size()>(triangle_numbers));

  auto t2 = std::chrono::system_clock::now();

  std::chrono::duration<double, std::milli> dur = t2 - t1;
  std::cout << "Largest summation total: " << result << "\n";
  std::cout << "Time taken (milliseconds): " << dur.count() << "\n";
  return 0;
}
