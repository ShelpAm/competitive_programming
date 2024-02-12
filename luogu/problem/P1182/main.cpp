#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <numeric>
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
  vec2(size_t const i, size_t const j): vec2<value_t>(i, std::vector<value_t>(j)) {}
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
void solve_case()
{
  size_t n{};
  size_t m{};
  std::cin >> n >> m;
  std::vector<size_t> a(n);
  std::cin >> a;

  auto check{[&](size_t const sum_limit) {
    size_t sum{};
    size_t num_segment{1};
    for (size_t i{}; i != n; ++i) {
      if (a[i] > sum_limit) {
        return false;
      }
      if (sum + a[i] > sum_limit) {
        sum = a[i];
        if (++num_segment > m) {
          return false;
        }
      }
      else {
        sum += a[i];
      }
    }
    return true;
  }};

  size_t r{std::accumulate(a.begin(), a.end(), 0UZ)};
  size_t l{r / m};
  while (l < r) {
    size_t m{(l + r) / 2};
    if (check(m)) {
      r = m;
    }
    else {
      l = m + 1;
    }
  }
  std::cout << l;
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
