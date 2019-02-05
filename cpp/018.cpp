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

size_t find_maximum_sum(const std::shared_ptr<Node> root)
{
  /* The following call is a needless expense. Esp. considering large data structures. */
  // pretty_print(root);

  unsigned largest_sum = 0;
  
  std::vector<std::shared_ptr<Node>> current_path;

  /* We use blocked_nodes to prevent execution from traversing a path that has already been explored.
   * If the current node's left child is referenced in blocked_nodes, execution will continue at the
   * node's right child (provided that the right child isn't included in blocked_nodes, if it is, we
   * unwind current_path to continue execution at the node's parent. */ 
  std::vector<std::shared_ptr<Node>> blocked_nodes;

  auto node = root;
  bool running = true;
  
  while (running) {
    while (node != nullptr) { /* Until node is a leaf in the tree. */
      current_path.push_back(node);
      
      /* Check each node's child in blocked_nodes. */
      if (std::find(blocked_nodes.begin(), blocked_nodes.end(), node->left) == blocked_nodes.end()) {
	node = node->left;
      }
      else if (std::find(blocked_nodes.begin(), blocked_nodes.end(), node->right) == blocked_nodes.end()) {
	node = node->right;
      }
    }

    unsigned current_sum = 0;
    for (const auto& node : current_path) { current_sum += node->val; }

    if (current_sum > largest_sum) { largest_sum = current_sum; }
    
    /* At this stage, node will be a nullptr so we'll set it to the node node in 'current_path'. We also
     * want to pop node from 'current_path' so it ends with node's parent */
    node = current_path.back();
    current_path.pop_back();
    
    /* At this stage we have accumulated an entire paths worth of values */     
    auto parent = current_path.back(); // node->parent not reliable as node can have two parents  
    
    if (parent->left == node) {
      blocked_nodes.push_back(node);
      current_path.pop_back();
      current_sum -= node->val;
      node = parent;
      current_sum -= node->val;
    }
    else {
      while (parent->left != node) { /* Until node is its parent's left child. */
	/* As both children of parent have been explored. We remove the children from 'blocked_nodes' and push the
	 * parent onto 'blocked_nodes'. */
	blocked_nodes.erase(std::remove(blocked_nodes.begin(), blocked_nodes.end(), parent->left), blocked_nodes.end());
	blocked_nodes.erase(std::remove(blocked_nodes.begin(), blocked_nodes.end(), parent->right), blocked_nodes.end());
	blocked_nodes.push_back(parent);
	
	if (blocked_nodes[0] != root) {
	  current_sum -= node->val;
	  node = current_path.back();
	  current_sum -= node->val;
	  current_path.pop_back();
	  parent = current_path.back();
	}
	else {
	  /* The first element of 'blocked_nodes' being 'root' indicates that all paths have been traversed. */
	  running = false;
	  break;
	}
      }
      
      current_path.pop_back();
      node = parent;
    }  
  }
  
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
  std::array<int, 120> triangle_numbers = { 75,
					    95, 64,
					    17, 47, 82,
					    18, 35, 87, 10,
					    20, 04, 82, 47, 65,
					    19, 01, 23, 75, 03, 34,
					    88, 02, 77, 73, 07, 63, 67,
					    99, 65, 04, 28, 06, 16, 70, 92,
					    41, 41, 26, 56, 83, 40, 80, 70, 33,
					    41, 48, 72, 33, 47, 32, 37, 16, 94, 29,
					    53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14,
					    70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57,
					    91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48,
					    63, 66, 04, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31,
					    04, 62, 98, 27, 23,  9, 70, 98, 73, 93, 38, 53, 60, 04, 23 };
  
  auto t1 = std::chrono::system_clock::now();
  
  auto result = find_maximum_sum(construct_tree<triangle_numbers.size()>(triangle_numbers));

  auto t2 = std::chrono::system_clock::now();

  std::chrono::duration<double, std::milli> dur = t2 - t1;
  std::cout << "Largest summation total: " << result << "\n";
  std::cout << "Time taken (milliseconds): " << dur.count() << "\n";
  return 0;
}
