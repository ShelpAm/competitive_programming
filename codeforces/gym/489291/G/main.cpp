#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
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
    std::cout << std::fixed << std::setprecision(4) << t << ' ';
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
  long long n{};
  size_t k{};
  std::cin >> n >> k;
  std::vector<double> p(n);
  std::cin >> p;

  std::ranges::sort(p, std::ranges::greater());
  p.insert(p.begin(), 0);

  auto tr{[n](long long const i) { return i + n; }};

  vec2<double> dp(n + 1, 2 * n + 1);
  dp[0][tr(0)] = 1;
  for (long long i{1}; i <= n; ++i) {
    for (long long j{-n}; j <= n; ++j) {
      dp[i][tr(j)]
          = p[i] * dp[i - 1][tr(j - 1)] + (1 - p[i]) * dp[i - 1][tr(j + 1)];
    }
  }
  // print(dp);
  double ans{};
  for (size_t i{1}; i <= n; ++i) {
    double tmp{};
    for (size_t j{k}; j <= n; ++j) {
      tmp += dp[i][tr(j)];
    }
    ans = std::ranges::max(ans, tmp);
  }
  std::cout << ans;
}
int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // std::cout.tie(nullptr);

  size_t n{1};
  // std::cin >> n;
  for (size_t i{}; i != n; ++i) {
    solve_case();
  }
  return 0;
}
