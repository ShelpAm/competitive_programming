#include <array>
#include <cstddef>
#include <iostream>
#include <limits>
#include <ranges>
#include <type_traits>
#include <vector>

using ::std::size_t;

// constexpr bool debug{false};

template<typename T> T read()
{
  T tmp;
  std::cin >> tmp;
  return tmp;
}
template<typename T> class input_value {
public:
  input_value(): value_(read<T>()) {}
  input_value(T const& initial_value): value_(initial_value + read<T>()) {}
  operator T&() { return value_; }
private:
  T value_;
};
template<size_t i, size_t j, typename value_type> using dp2
    = std::array<std::array<value_type, j>, i>;
template<size_t i, size_t j> using dp2uz = dp2<i, j, size_t>;
template<size_t i, size_t j> using dp2ll = dp2<i, j, long long>;
void print(auto&& t)
{
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      print(ele);
    }
    std::cout << '\n';
  }
  else {
    std::cout << t << ' ';
  }
}
auto f(auto&& dp, auto&& i, auto&& j)
{
  auto transform = [dp = dp[0]](auto n) {
    if (n == std::numeric_limits<decltype(n)>::max()) {
      return dp.size() - 1;
    }
    if (n == dp.size()) {
      return 0UZ;
    }
    return n;
  };
  return dp[i - 1][transform(j + 1)] + dp[i - 1][transform(j - 1)];
}
void solve_case()
{
  input_value<size_t> n;
  input_value<size_t> m;
  constexpr auto initial_pos{0};
  std::vector<std::vector<size_t>> dp(m + 1, std::vector<size_t>(n, 0));
  dp[0][initial_pos] = 1;
  for (size_t i{1}; i != dp.size(); ++i) {
    for (size_t j{}; j != dp[0].size(); ++j) {
      dp[i][j] = f(dp, i, j);
    }
  }
  // print(dp);
  std::cout << dp[m][initial_pos];
}
int main()
{
  auto n{1UZ};
  // n = read<size_t>();
  for (size_t i{}; i != n; ++i) {
    solve_case();
  }
  return 0;
}
