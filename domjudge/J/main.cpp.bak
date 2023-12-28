#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <map>
#include <ranges>
#include <string_view>
#include <vector>

using ::std::size_t;

// constexpr bool debug{false};

template<size_t i, size_t j, typename value_type> using arr2
    = std::array<std::array<value_type, j>, i>;
template<size_t i, size_t j> using arr2uz = arr2<i, j, size_t>;
template<size_t i, size_t j> using arr2ll = arr2<i, j, long long>;
template<typename value_type> using vec2_impl
    = std::vector<std::vector<value_type>>;
template<typename value_t> class vec2 : public vec2_impl<value_t> {
public:
  vec2(size_t const i, size_t const j)
      : vec2_impl<value_t>(i, std::vector<value_t>(j))
  {}
};
using vec2uz = vec2<size_t>;
using vec2ll = vec2<long long>;
template<typename T> concept is_pair = requires(T t) {
  t.first;
  t.second;
};
void print(auto&& t)
{
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      print(ele);
    }
    std::cout << '\n';
  }
  else if constexpr (is_pair<decltype(t)>) {
    std::cout << t.first << ": " << t.second << ", ";
  }
  else {
    std::cout << t << ' ';
  }
}
void debug(std::string_view const& sv, auto&& t)
{
  std::cout << sv << ": ";
  print(t);
}
auto&& operator>>(auto&& is, auto&& t)
{
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      is >> ele;
    }
  }
  else if constexpr (is_pair<decltype(t)>) {
    is >> t.first >> t.second;
  }
  else {
    is >> t;
  }
  return is;
}
void solve_case()
{
  size_t n{};
  std::cin >> n;
  std::vector<long long> v(n);
  std::cin >> v;
  size_t q{};
  std::cin >> q;
  std::map<long long, size_t> mp;
  for (auto const i: v) {
    ++mp[i];
  }

  for (size_t i{}; i != q; ++i) {
    long long a{};
    long long b{};
    std::cin >> a >> b;

    auto delta{a * a - 4 * b};
    if (delta < 0) {
      std::cout << "0 ";
    }
    else if (delta == 0) {
      if (a % 2 == 0) {
        std::cout << mp[a / 2] * (mp[a / 2] - 1) / 2 << ' ';
      }
      else {
        std::cout << "0 ";
      }
    }
    else {
      // delta > 0
      long long s{static_cast<long long>(std::sqrt(delta))};
      if (s * s == delta) {
        size_t l{};
        size_t r{};
        if ((a + s) % 2 == 0) {
          r = mp[(a + s) / 2];
        }
        if ((a - s) % 2 == 0) {
          l = mp[(a - s) / 2];
        }
        std::cout << r * l << ' ';
      }
      else {
        std::cout << "0 ";
      }
    }
  }
  std::cout << '\n';
}
int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // std::cout.tie(nullptr);

  size_t n{1};
  std::cin >> n;
  for (size_t i{}; i != n; ++i) {
    solve_case();
  }
  return 0;
}
