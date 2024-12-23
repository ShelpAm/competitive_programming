#pragma once

#include "../templates/main.cpp"

class Fenwick_tree {
public:
  // _tree[1..size] is available
  explicit Fenwick_tree(int size) : _tree(size + 1) {}

  // The input array should start from the index 1.
  explicit Fenwick_tree(std::vector<std::int_fast64_t> coll)
      : _tree{std::move(coll)}
  {
    for (int i = 1; i != _tree.size(); ++i) {
      if (auto const parent_index = i + lsb(i); parent_index < _tree.size()) {
        _tree[parent_index] += _tree[i];
      }
    }
  }

  [[nodiscard]] auto sum(int l, int r) const -> std::int_fast64_t
  {
    assert(l > 0);
    assert(l <= r);
    assert(r < _tree.size());
    return prefix_sum(r) - prefix_sum(l - 1);
  }

  [[nodiscard]] auto prefix_sum(int index) const -> std::int_fast64_t
  {
    std::int_fast64_t sum{};
    while (index > 0) {
      sum += _tree[index];
      index -= lsb(index);
    }
    return sum;
  }

  void add_to(int index, std::int_fast64_t delta)
  {
    auto n{static_cast<int>(_tree.size())};
    while (index < n) {
      _tree[index] += delta;
      index += lsb(index);
    }
  }

private:
  std::vector<std::int_fast64_t> _tree;
};
