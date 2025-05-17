#pragma once

#include <algorithm>
#include <numeric>
#include <vector>

namespace shelpam {

class Disjoint_set_union {
  public:
    explicit Disjoint_set_union(int size) : _parent(size), _size(size, 1)
    {
        std::ranges::iota(_parent, 0);
    }

    // With path compression
    int find(int x)
    {
        return _parent[x] == x ? x : _parent[x] = find(_parent[x]);
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
        if (_size[x] < _size[y]) {
            std::swap(x, y);
        }
        _parent[y] = x;
        _size[x] += _size[y];
        return true;
    }

    [[nodiscard]] bool united(int x, int y)
    {
        return find(x) == find(y);
    }

    [[nodiscard]] auto size(int x)
    {
        return _size[find(x)];
    }

  private:
    std::vector<int> _parent;
    std::vector<int> _size;
};

using Dsu = Disjoint_set_union;

} // namespace shelpam
