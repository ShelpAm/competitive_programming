#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <string_view>
#include <vector>

// configs
using ::std::size_t;

struct dsu {
  dsu(size_t size_): pa(size_), size(size_, 1) { std::iota(pa.begin(), pa.end(), 0); }
  size_t find(size_t const x) { return pa[x] == x ? x : pa[x] = find(pa[x]); }
  void unite(size_t x, size_t y)
  {
    x = find(x);
    y = find(y);
    if (x == y) {
      return;
    }
    if (size[x] < size[y]) {
      std::swap(size[x], size[y]);
    }
    pa[y] = x;
    size[x] += size[y];
  }
  size_t get_size(size_t const i) { return size[find(i)]; }
  bool is_together(size_t const x, size_t const y) { return find(x) == find(y); }
  std::vector<size_t> pa;
  std::vector<size_t> size;
};
void solve_case()
{
  size_t n{};
  std::cin >> n;
  std::vector<size_t> a(n);
  for (auto&& e: a) {
    std::cin >> e;
  }

  // Expectation is as follow.
  size_t randomized{(n + 1) * n / 2};
  dsu d(n);
  for (size_t i{}; i != n; ++i) {
    d.unite(i, a[i] - 1);
  }
  double playmaker{};
  for (size_t i{}; i != n; ++i) {
    playmaker += static_cast<double>(d.get_size(i)) / static_cast<double>(n);
  }
  if (playmaker <= randomized) {
    std::cout << playmaker;
  }
  else {
    std::cout << "lose";
  }
}
int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // std::cout.tie(nullptr);

  size_t t{1};
  // std::cin >> t;
  for (size_t i{}; i != t; ++i) {
    solve_case();
  }
  return 0;
}
