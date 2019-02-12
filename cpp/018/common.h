#ifndef COMMON_H
#define COMMON_H

#include <memory>
#include <stack>
#include <vector>

struct Node
{
  std::shared_ptr<Node> parent = nullptr, left = nullptr, right = nullptr;
  int val;
  Node(int v) : val(v) {}
};

extern std::shared_ptr<Node> root;

extern std::stack<std::shared_ptr<Node>> current_path;

/* We use blocked_nodes to prevent execution from traversing a path that has already been explored.
 * If the current node's left child is referenced in blocked_nodes, execution will continue at the
 * node's right child (provided that the right child isn't included in blocked_nodes, if it is, we
 * unwind current_path to continue execution at the node's parent. */ 

extern std::vector<std::shared_ptr<Node>> blocked_nodes;
  
extern void graph_init();

#endif
