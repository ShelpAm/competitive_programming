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
constexpr size_t big{0x3f3f3f3f};
auto solve_case()
{
  size_t n;
  std::cin >> n;
  std::vector<std::tuple<size_t, size_t, size_t>> v(n);
  for (auto&& [rmb, rp, time]: v) {
    std::cin >> rmb >> rp >> time;
  }
  size_t m, r;
  std::cin >> m >> r;

  vec2uz dp(m + 1, r + 1);
  for (auto&& [rmb, rp, time]: v) {
    for (size_t i{m}; i >= rmb; --i) {
      for (size_t j{r}; j >= rp; --j) {
        dp[i][j] = std::ranges::max(dp[i][j], dp[i - rmb][j - rp] + big - time);
      }
    }
  }
  std::cout << (big - dp[m][r] % big);
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
