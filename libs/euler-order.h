#pragma once

#include "graph.h"

namespace shelpam {

using graph::Node_type;

// There may be more than 2 occurences of some node in `seq`.
class Euler_order {
public:
  Euler_order(graph::Graph const &g, int root) : dfn_(g.size())
  {
    std::function<void(int u, int p)> dfs{[this, &g, &dfs](int u, int p) {
      dfn_[u].push_back(seq_.size());
      seq_.push_back(u);
      for (auto const &[_, v] : g.edges_of(u)) {
        if (v != p) {
          dfs(v, u);
          seq_.push_back(u);
        }
      }
    }};

    dfs(root, root);
  }

  [[nodiscard]] auto sequence() const -> std::vector<Node_type> const &
  {
    return seq_;
  }

  [[nodiscard]] auto dfn(Node_type u) const -> std::vector<std::size_t> const &
  {
    return dfn_[u];
  }

private:
  std::vector<std::vector<std::size_t>> dfn_; // first time to be visited
  std::vector<Node_type> seq_;
};

} // namespace shelpam
