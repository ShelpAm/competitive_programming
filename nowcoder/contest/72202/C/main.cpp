#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iomanip>
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
auto my_pow(auto a, std::size_t n) -> decltype(a)
{
  if (n == 0) {
    return 1;
  }
  if (a == 0) {
    return 0;
  }
  decltype(a) extra = 1.0;
  while (n != 1) {
    if ((n & 1) == 1) {
      extra *= a;
      n -= 1;
    }
    else {
      a *= a;
      n /= 2;
    }
  }
  return (a * extra);
}
void solve_case()
{
  size_t n{};
  std::cin >> n;
  std::unordered_map<size_t, size_t> a;
  for (;;) {
    long long i{};
    long long j{};
    std::cin >> i;
    if (i == -1) {
      break;
    }
    std::cin >> j;
    a[i] = j;
  }

  constexpr double p{1.0 / 3};
  double sum{};
  for (auto const [floor, num]: a) {
    sum += 50 * my_pow(p, floor) * num;
  }
  std::cout << std::round(sum / static_cast<double>(3 * n + 2));
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
