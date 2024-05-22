#pragma once
#include "generics.h"

class disjoint_set_union {
public:
  explicit disjoint_set_union(int size) : parent_(size), size_(size, 1)
  {
    std::iota(parent_.begin(), parent_.end(), 0);
  }
  // with path compression
  int find(int const x)
  {
    return parent_[x] == x ? x : parent_[x] = find(parent_[x]);
  }
  /// @return:
  /// false if there has been pair x,y in the set.
  /// true successfully united
  bool unite(int x, int y)
  {
    x = find(x), y = find(y);
    if (x == y) {
      return false;
    }
    if (size_[x] < size_[y]) {
      std::swap(x, y);
    }
    parent_[y] = x;
    size_[x] += size_[y];
    return true;
  }
  [[nodiscard]] bool united(int const x, int const y)
  {
    return find(x) == find(y);
  }
  [[nodiscard]] std::size_t size(int x) { return size_[find(x)]; }

private:
  std::vector<int> parent_;
  std::vector<int> size_;
};
using dsu = disjoint_set_union;
