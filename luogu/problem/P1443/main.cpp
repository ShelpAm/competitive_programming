#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <queue>
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
  vec2(size_t const i, size_t const j): impl::vec2<value_t>(i, std::vector<value_t>(j, -1)) {}
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
struct pos_t {
  auto operator<=>(pos_t const&) const = default;
  auto operator+(pos_t const& rhs) const { return pos_t{x + rhs.x, y + rhs.y, depth + 1}; }
  long long x;
  long long y;
  long long depth;
};
void solve_case()
{
  size_t n{};
  size_t m{};
  size_t x{};
  size_t y{};
  std::cin >> n >> m >> x >> y;
  --x;
  --y;
  vec2ll v(n, m);

  auto is_valid{
      [&](pos_t const& pos) { return pos.x >= 0 && pos.x < n && pos.y >= 0 && pos.y < m; }};
  constexpr std::array<pos_t, 8> dirs{pos_t{2, 1}, {2, -1},  {1, 2},  {1, -2},
                                      {-1, 2},     {-1, -2}, {-2, 1}, {-2, -1}};

  std::queue<pos_t> q;
  q.push(pos_t{static_cast<long long>(x), static_cast<long long>(y), 0});
  while (!q.empty()) {
    if (is_valid(q.front()) && v[q.front().x][q.front().y] == -1) {
      v[q.front().x][q.front().y] = q.front().depth;
      for (auto const& dir: dirs) {
        q.push(q.front() + dir);
      }
    }
    q.pop();
  }

  for (size_t i{}; i != n; ++i) {
    for (size_t j{}; j != m; ++j) {
      printf("%-5lld", v[i][j]);
    }
    printf("\n");
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
