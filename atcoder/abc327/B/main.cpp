#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <map>
#include <numeric>
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
constexpr size_t mod{static_cast<size_t>(1e18 + 7)};
size_t quick_pow(size_t a, size_t n)
{
  a %= mod;
  size_t res{1};
  while (n != 0) {
    if ((n & 1) == 1) {
      res = res * a % mod;
    }
    a = a * a % mod;
    n /= 2;
  }
  return res;
}
auto solve_case()
{
  size_t b{};
  std::cin >> b;
  size_t l{};
  size_t r{15};
  while (l < r) {
    auto mid{(l + r + 1) >> 1};
    if (quick_pow(mid, mid) <= b % mod) {
      l = mid;
    }
    else {
      r = mid - 1;
    }
  }
  if (quick_pow(l, l) == b % mod) {
    return static_cast<int>(l);
  }
  return -1;
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
      print(solve_case_f());
    }
  }
}
int main()
{
  impl::do_optimization();
  solve_all_cases(solve_case);
  return 0;
}
