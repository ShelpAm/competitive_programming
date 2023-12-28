#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <stack>
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
size_t find_last_greater_than(auto&& f, auto h)
{
  size_t l{0};
  size_t r{f.size() - 1};
  while (l < r) {
    auto m{(l + r) / 2};
    if (f[m] < h) {
      r = m;
    }
    else if (f[m] > h) {
      l = m + 1;
    }
    else {
      return l;
    }
  }
  return l;
}
void solve_case()
{
  std::vector<size_t> h;
  size_t tmp{};
  while (std::cin >> tmp) {
    h.emplace_back(tmp);
  }
  // h.emplace_back(std::numeric_limits<size_t>::max());

  std::vector<size_t> f(h.size() + 1); // f[i] represents the max height of every subsequence whose
  // length is i; otherwise its value would be 0.
  std::vector<size_t> dp(h.size() + 1); // dp[i] represents the max length of subsequence of first
  // i-th elements.
  for (size_t i{}; i != h.size(); ++i) {
    size_t len{find_last_greater_than(f, h[i])};
    dp[i] = len + 1;
    f[len + 1] = h[i];
  }
  std::cout << std::ranges::max(dp) << '\n';
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