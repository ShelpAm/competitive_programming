#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <list>
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
using ::std::array;
using ::std::cin;
using ::std::cout;
using ::std::size_t;
template<typename value_type> using vec1 = ::std::vector<value_type>;
using ::std::string;
using ::std::string_view;
using ::std::ranges::max;
using ::std::ranges::min;
using ::std::ranges::sort;
using namespace ::std::string_view_literals;

namespace impl {
  template<typename value_t> using vec2 = std::vector<std::vector<value_t>>;
  template<typename T> concept is_pair = requires(T t) {
    t.first;
    t.second;
  };
  class io_accelerator {
  public:
    io_accelerator()
    {
      std::ios::sync_with_stdio(false);
      std::cin.tie(nullptr);
      // The following line needn't to be executed because the above line actually had done this.
      // std::cout.tie(nullptr);
    }
    io_accelerator(const io_accelerator&) = delete;
    io_accelerator(io_accelerator&&) = delete;
    io_accelerator& operator=(const io_accelerator&) = delete;
    io_accelerator& operator=(io_accelerator&&) = delete;
    ~io_accelerator()
    {
      std::ios::sync_with_stdio(true);
      std::cin.tie(&std::cout);
    }
  };
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
    std::cout << '\n';
  }
  else if constexpr (impl::is_pair<decltype(t)>) {
    std::cout << t.first << ": " << t.second << ',';
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
auto solve_case()
{
  size_t f, v;
  cin >> f >> v;
  vec2ll beauty(f + 1, v + 1);
  for (size_t i{1}; i <= f; ++i) {
    for (size_t j{1}; j <= v; ++j) {
      cin >> beauty[i][j];
    }
  }

  vec2ll dp(f + 1, v + 1, -0x3f3f3f3f);
  vec2uz prev(f + 1, v + 1);
  std::ranges::fill(dp[0].begin(), dp[0].end(), 0);
  for (size_t i{1}; i <= f; ++i) {
    for (size_t j{i}; j <= v; ++j) {
      for (size_t k{0}; k < j; ++k) {
        if (dp[i][j] < dp[i - 1][k] + beauty[i][j]) {
          dp[i][j] = dp[i - 1][k] + beauty[i][j];
          prev[i][j] = k;
        }
      }
    }
  }
  auto p{std::ranges::max_element(dp[f]) - dp[f].begin()};
  cout << dp[f][p] << '\n';
  vec1<size_t> ans;
  ans.reserve(f);
  for (size_t i{f}; i != 0; --i) {
    ans.emplace_back(p);
    p = prev[i][p];
  }
  print(ans | std::ranges::views::reverse);
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
  impl::io_accelerator accelerator;
  solve_all_cases(solve_case);
  return 0;
}
