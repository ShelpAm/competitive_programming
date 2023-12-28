#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// configs
using ::std::size_t;

namespace impl {
  template<typename value_t> using vec2 = std::vector<std::vector<value_t>>;
  template<typename T> concept is_pair = requires(T t) {
    t.first;
    t.second;
  };
  void do_optimization()
  {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    // std::cout.tie(nullptr);
  }
} // namespace impl
template<size_t i, size_t j, typename value_t> using arr2 = std::array<std::array<value_t, j>, i>;
template<size_t i, size_t j> using arr2uz = arr2<i, j, size_t>;
template<size_t i, size_t j> using arr2ll = arr2<i, j, long long>;
template<typename value_t> class vec2 : public impl::vec2<value_t> {
public:
  vec2(size_t const i, size_t const j, value_t const& value = {})
      : impl::vec2<value_t>(i, std::vector<value_t>(j, value))
  {}
};
using vec2uz = vec2<size_t>;
using vec2ll = vec2<long long>;
auto&& operator>>(auto&& is, auto&& t)
{
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      is >> ele;
    }
  }
  else if constexpr (impl::is_pair<decltype(t)>) {
    is >> t.first >> t.second;
  }
  else {
    is >> t;
  }
  return is;
}
void print(auto const& t)
{
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      print(ele);
    }
  }
  else if constexpr (impl::is_pair<decltype(t)>) {
    std::cout << t.first << t.second;
  }
  else {
    std::cout << t << ' ';
  }
}
void debug([[maybe_unused]] std::string_view const& sv, [[maybe_unused]] auto&& t)
{
#ifdef DEBUG
  std::cout << sv << ": ";
  print(t);
  std::cout << '\n';
#endif
}
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
      std::ranges::swap(x, y);
    }
    pa[y] = x;
    size[x] += size[y];
  }
  bool united(size_t const x, size_t const y) { return find(x) == find(y); }
  std::vector<size_t> pa;
  std::vector<size_t> size;
};
auto solve_case()
{
  size_t n{};
  size_t m{};
  std::cin >> n >> m;
  std::vector<size_t> a(m);
  std::vector<size_t> b(m);
  for (auto&& e: a) {
    std::cin >> e;
    --e;
  }
  for (auto&& e: b) {
    std::cin >> e;
    --e;
  }
  dsu d(2 * n);
  for (size_t i{}; i != m; ++i) {
    if (d.united(a[i], b[i])) {
      return false;
    }
    d.unite(a[i], b[i] + n);
    d.unite(b[i], a[i] + n);
  }
  return true;
}
void solve_all_cases(auto&& solve_case_f)
{
  size_t t{1};
  // std::cin >> t;
  for (size_t i{}; i != t; ++i) {
    if constexpr (std::is_same_v<decltype(solve_case_f()), void>) {
      solve_case_f();
    }
    else {
      print(solve_case_f() ? "Yes" : "No");
    }
  }
}
int main()
{
  impl::do_optimization();
  solve_all_cases(solve_case);
  return 0;
}
