#pragma once
#include "generics.h"

class fenwick_tree {
public:
  fenwick_tree(u64 const size) : tree_(size) {}
  // The input array should start from the index 1.
  fenwick_tree(vi coll) : tree_{std::move(coll)}
  {
    for (size_t i = 1; i != tree_.size(); ++i) {
      auto parent_index = i + lsb(static_cast<i64>(i));
      if (parent_index < tree_.size()) {
        tree_[parent_index] += tree_[i];
      }
    }
  }
  [[nodiscard]] i64 prefix_sum(u64 index) const
  {
    i64 sum{};
    while (index > 0) {
      sum += tree_[index];
      index -= lsb(static_cast<i64>(index));
    }
    return sum;
  }
  void add_to(u64 index, i64 const value)
  {
    while (index < tree_.size()) {
      tree_[index] += value;
      index += lsb(static_cast<i64>(index));
    }
  }

private:
  vi tree_;
};
