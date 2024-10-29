#pragma once

#include "../templates/main.cpp"
#include "graph.h"

namespace shelpam {

using graph::Node_type;

class Least_common_ancestor {
public:
  Least_common_ancestor(graph::Graph const &g, int root)
      : dfn_(g.size()),
        depth_(g.size(),
               -1) // -1 to make `depth[parent-of-root] + 1` equal to 0.
  {
    std::function<void(int u, int p)> dfs{[this, &g, &dfs](int u, int p) {
      depth_[u] = depth_[p] + 1;
      dfn_[u] = seq_.size();
      seq_.push_back(u);
      for (auto const &[_, v] : g.edges_of(u)) {
        if (v != p) {
          dfs(v, u);
          seq_.push_back(u);
        }
      }
    }};

    dfs(root, root);

    f_.assign(1 + msb(seq_.size()), std::vector<int>(seq_.size(), inf<int>));
    for (std::size_t i{}; i != seq_.size(); ++i) {
      f_[0][i] = depth_[seq_[i]];
    }
    h_.assign(1 + msb(seq_.size()), std::vector<int>(seq_.size()));
    h_[0] = seq_;

    for (std::size_t i{1}; i != f_.size(); ++i) {
      for (std::size_t j{}; j + (1 << i) - 1 != f_[i].size(); ++j) {
        if (chmin(f_[i][j], f_[i - 1][j])) {
          h_[i][j] = h_[i - 1][j];
        }
        if (chmin(f_[i][j], f_[i - 1][j + (1 << (i - 1))])) {
          h_[i][j] = h_[i - 1][j + (1 << (i - 1))];
        }
      }
    }
  }

  [[nodiscard]] auto query(Node_type u, Node_type v) const -> Node_type
  {
    auto const [l, r]{std::minmax(dfn_[u], dfn_[v])};
    auto const k{msb(r - l + 1)};
    Node_type result;
    int depth{inf<int>};
    if (chmin(depth, f_[k][l])) {
      result = h_[k][l];
    }
    if (chmin(depth, f_[k][r - (1 << k) + 1])) {
      result = h_[k][r - (1 << k) + 1];
    }
    return result;
  }

private:
  // Of node
  std::vector<std::size_t> dfn_; // first time to be visited
  std::vector<Node_type> seq_;
  std::vector<int> depth_;

  std::vector<std::vector<int>> f_;       // Min sparse table for depth
  std::vector<std::vector<Node_type>> h_; // Sparse table for min depth node
};

using LCA = Least_common_ancestor;

} // namespace shelpam
