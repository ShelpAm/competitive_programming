#pragma once

#include <numeric>
#include <vector>

namespace disjoint_set_union {
class Disjoint_set_union {
public:
  explicit Disjoint_set_union(int const size) : _parent(size), _size(size, 1)
  {
    std::iota(_parent.begin(), _parent.end(), 0);
  }
  // with path compression
  auto find(int const x) -> int
  {
    return _parent[x] == x ? x : _parent[x] = find(_parent[x]);
  }
  /// @return:
  /// false if there has been pair x,y in the set.
  /// true successfully united
  auto unite(int x, int y) -> bool
  {
    x = find(x), y = find(y);
    if (x == y) {
      return false;
    }
    if (_size[x] < _size[y]) {
      std::swap(x, y);
    }
    _parent[y] = x;
    _size[x] += _size[y];
    return true;
  }
  [[nodiscard]] auto united(int const x, int const y) -> bool
  {
    return find(x) == find(y);
  }
  [[nodiscard]] auto size(int const x) -> int
  {
    return _size[find(x)];
  }

private:
  std::vector<int> _parent;
  std::vector<int> _size;
};
using Dsu = Disjoint_set_union;
} // namespace disjoint_set_union
