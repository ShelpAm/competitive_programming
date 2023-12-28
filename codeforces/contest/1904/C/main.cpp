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
void debug([[maybe_unused]] std::string_view const& sv, [[maybe_unused]] auto&& t)
{
#ifdef DEBUG
  std::cout << sv << ": " << t << '\n';
#endif
}
void solve_case()
{
  size_t n{};
  size_t k{};
  std::cin >> n >> k;
  std::vector<size_t> a(n);
  std::cin >> a;

  if (k >= 3) {
    std::cout << 0 << '\n';
    return;
  }

  std::ranges::sort(a);
  size_t d{std::ranges::min(a)};
  for (size_t i{}; i + 1 != n; ++i) {
    d = std::ranges::min(d, a[i + 1] - a[i]);
  }
  if (k == 1) {
    std::cout << d << '\n';
    return;
  }
  for (size_t i{}; i != n; ++i) {
    for (size_t j{}; j != i; ++j) {
      size_t v{a[i] - a[j]};
      auto p{std::ranges::lower_bound(a, v) - a.begin()};
      if (p < n) {
        d = std::ranges::min(d, a[p] - v);
      }
      if (p >= 1) {
        d = std::ranges::min(d, v - a[p - 1]);
      }
    }
  }
  std::cout << d << '\n';
}
int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // std::cout.tie(nullptr);

  size_t t{1};
  std::cin >> t;
  for (size_t i{}; i != t; ++i) {
    solve_case();
  }
  return 0;
}
