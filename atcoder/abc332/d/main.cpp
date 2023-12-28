#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <string_view>
#include <unordered_map>
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
void debug([[maybe_unused]] std::string_view const& sv, [[maybe_unused]] auto&& t)
{
#ifdef DEBUG
  std::cout << sv << ": " << t << '\n';
#endif
}
void solve_case()
{
  size_t h{};
  size_t w{};
  std::cin >> h >> w;
  vec2uz a(h, w);
  vec2uz b(h, w);
  std::cin >> a >> b;

  std::unordered_map<size_t, std::pair<size_t, size_t>> pos(h * w);
  for (size_t i{}; i != h; ++i) {
    for (size_t j{}; j != w; ++j) {
      pos[b[i][j]] = {i, j};
    }
  }

  auto row_swap{[&](size_t const i) { std::ranges::swap(a[i], a[i + 1]); }};
  auto column_swap{[&](size_t const i) {
    for (size_t j{}; j != h; ++j) {
      std::ranges::swap(a[j][i], a[j][i + 1]);
    }
  }};

  for (size_t i{}; i != h; ++i) {
    for (size_t j{}; j != w; ++j) {
      if (!pos.contains(a[i][j])) {
        std::cout << -1;
        return;
      }
      auto&& p{pos[a[i][j]]};
      long long dx{static_cast<long long>(p.first) - static_cast<long long>(i)};
      if (dx > 0) {
        for (long long k{}; k != dx; ++k) {
          row_swap(i + k);
        }
      }
      else {
        for (long long k{}; k != dx; --k) {
          row_swap(i - 1 + k);
        }
      }
      long long dy{static_cast<long long>(p.second) - static_cast<long long>(j)};
      if (dy > 0) {
        for (long long k{}; k != dy; ++k) {
          column_swap(j + k);
        }
      }
      else {
        for (long long k{}; k != dy; --k) {
          column_swap(j - 1 + k);
        }
      }
    }
  }

  for (size_t i{}; i != h; ++i) {
    for (size_t j{}; j != w; ++j) {
      if (condition) {
      }
    }
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
