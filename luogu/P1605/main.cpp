#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <string_view>
#include <vector>

// configs
using ::std::size_t;

namespace impl {
  template<typename value_t> using vec2 = std::vector<std::vector<value_t>>;
  template<typename T> concept is_pair = requires(T t) {
    t.first;
    t.second;
  };
} // namespace impl
template<size_t i, size_t j, typename value_t> using arr2 = std::array<std::array<value_t, j>, i>;
template<size_t i, size_t j> using arr2uz = arr2<i, j, size_t>;
template<size_t i, size_t j> using arr2ll = arr2<i, j, long long>;
template<typename value_t> class vec2 : public impl::vec2<value_t> {
public:
  vec2(size_t const i, size_t const j): impl::vec2<value_t>(i, std::vector<value_t>(j)) {}
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
auto&& operator<<(auto&& os, auto&& t)
{
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      os << ele << ' ';
    }
    os << '\n';
  }
  else if constexpr (impl::is_pair<decltype(t)>) {
    os << t.first << ": " << t.second << ", ";
  }
  else {
    os << t << ' ';
  }
  return os;
}
void debug(std::string_view const& sv, auto&& t)
{
#ifdef DEBUG
  std::cout << sv << ": " << t << '\n';
#endif
}
size_t n{};
size_t m{};
size_t search(size_t const sx, size_t const sy, size_t const fx, size_t const fy, auto&& visited)
{
  if (sx == -1 || sx == n || sy == -1 || sy == m || visited[sx][sy]) {
    return 0;
  }
  if (sx == fx && sy == fy) {
    return 1;
  }

  visited[sx][sy] = true;
  size_t sum{};
  sum += search(sx - 1, sy, fx, fy, visited);
  sum += search(sx + 1, sy, fx, fy, visited);
  sum += search(sx, sy - 1, fx, fy, visited);
  sum += search(sx, sy + 1, fx, fy, visited);
  visited[sx][sy] = false;

  return sum;
}
void solve_case()
{
  size_t t{};
  std::cin >> n >> m >> t;
  size_t sx, sy, fx, fy;
  std::cin >> sx >> sy >> fx >> fy;
  vec2<bool> visited(n, m);
  for (size_t i{}; i != t; ++i) {
    size_t x, y;
    std::cin >> x >> y;
    visited[x - 1][y - 1] = true;
  }
  std::cout << search(sx - 1, sy - 1, fx - 1, fy - 1, visited);
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
