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

extern void graph_render(const std::vector<std::shared_ptr<Node>>& current_path,
			 const std::vector<std::shared_ptr<Node>>& blocked_nodes);

extern void graph_init();

#endif
