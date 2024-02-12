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
struct pos_t {
  auto operator<=>(pos_t const&) const = default;
  auto operator+(pos_t const& rhs) const { return pos_t{x + rhs.x, y + rhs.y}; }
  auto operator*(long long const scale) const { return pos_t{x * scale, y * scale}; }
  long long x;
  long long y;
};
void solve_case()
{
  size_t n{};
  std::cin >> n;
  vec2<char> v(n, n);
  std::cin >> v;

  constexpr std::array<pos_t, 8> dirs{pos_t{0, 1}, {0, -1}, {-1, -1}, {1, -1},
                                      {1, 1},      {1, 0},  {-1, 1},  {-1, 0}};
  std::string_view target{"yizhong"};
  vec2<char> res(n, n);
  for (auto&& row: res) {
    std::ranges::fill(row, '*');
  }
  for (size_t i{}; i != n; ++i) {
    for (size_t j{}; j != n; ++j) {
      pos_t pos{static_cast<long long>(i), static_cast<long long>(j)};
      for (auto const dir: dirs) {
        auto is_ok{[&]() {
          for (size_t len{}; len != target.size(); ++len) {
            auto t{pos + dir * len};
            if (t.x < 0 || t.x >= n || t.y < 0 || t.y >= n) {
              return false;
            }
            if (v[t.x][t.y] != target[len]) {
              return false;
            }
          }
          return true;
        }()};
        if (is_ok) {
          for (size_t len{}; len != target.size(); ++len) {
            auto t{pos + dir * len};
            res[t.x][t.y] = target[len];
          }
        }
      }
    }
  }
  for (auto const& row: res) {
    for (char const c: row) {
      std::cout << c;
    }
    std::cout << '\n';
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
