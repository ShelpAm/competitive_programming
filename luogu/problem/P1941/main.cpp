#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <cstddef>
#include <deque>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// configs
template<typename value_type> using vec1 = ::std::vector<value_type>;
using ::std::array;
using ::std::cin;
using ::std::cout;
using ::std::size_t;
using ::std::string;
using ::std::string_view;
using ::std::ranges::max;
using ::std::ranges::min;
using ::std::ranges::sort;
using ::std::operator""sv;
using ::std::ranges::views::drop;
using ::std::ranges::views::reverse;
using ::std::ranges::views::take;

[[maybe_unused]] char constexpr endl{'\n'};

namespace impl {
  template<typename value_type> using vec2 = std::vector<std::vector<value_type>>;
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
template<size_t i, size_t j, typename value_type> using arr2
    = std::array<std::array<value_type, j>, i>;
template<size_t i, size_t j> using arr2uz = arr2<i, j, size_t>;
template<size_t i, size_t j> using arr2ll = arr2<i, j, long long>;
template<typename value_type> class vec2 : public impl::vec2<value_type> {
public:
  vec2(size_t const i, size_t const j, value_type const& value = {})
      : impl::vec2<value_type>(i, std::vector<value_type>(j, value))
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
    std::cout << endl;
  }
  else if constexpr (impl::is_pair<decltype(t)>) {
    std::cout << t.first << ": " << t.second << ", ";
  }
  else {
    std::cout << std::setw(2) << t << ' ';
  }
}
void debug(std::string_view const sv, auto&& t)
{
#ifdef DEBUG
  std::cout << sv << ": ";
  print(t);
  std::cout << endl;
#endif
}
constexpr size_t big{0x3f3f3f3f};
auto solve_case()
{
  size_t n, m, k;
  cin >> n >> m >> k;
  vec1<std::pair<size_t, size_t>> v(n);
  cin >> v;
  vec1<std::pair<size_t, size_t>> limits(n + 1, {1, m});
  vec1<bool> has_trap(n + 1);
  for (size_t i{}; i != k; ++i) {
    size_t p, l, h;
    cin >> p >> l >> h;
    limits[p] = {l + 1, h - 1};
    has_trap[p] = true;
  }

  vec2uz dp(n + 1, m + 1, big);
  std::ranges::fill(dp[0], 0);
  size_t went_through{};
  for (size_t i{1}; i <= n; ++i) {
    auto const& [x, y]{v[i - 1]};
    // Go up
    for (size_t j{x}; j <= m; ++j) {
      dp[i][j] = min({dp[i][j], dp[i - 1][j - x] + 1, dp[i][j - x] + 1});
    }
    // Go ceil, j 表示来源
    for (size_t j{m - x}; j <= m; ++j) {
      dp[i][m] = min({dp[i][m], dp[i - 1][j] + 1, dp[i][j] + 1});
    }
    // Go down
    for (size_t j{m - y}; j != -1UZ; --j) {
      dp[i][j] = min(dp[i][j], dp[i - 1][j + y]);
    }
    // Do some clean-up.
    for (size_t k{}; k <= limits[i].first - 1; ++k) {
      dp[i][k] = big;
    }
    for (size_t k{limits[i].second + 1}; k <= m; ++k) {
      dp[i][k] = big;
    }
    // cout << "X: " << i << '|';
    // print(dp[i]);
    // cout << "limits: " << limits[i].first << ' ' << limits[i].second << ", x,y: " << x << ' ' <<
    // y
    //      << endl;
    if (std::ranges::all_of(dp[i], [&](size_t const t) { return t == big; })) {
      cout << 0 << endl << went_through;
      return;
    }
    if (has_trap[i]) {
      ++went_through;
    }
  }
  size_t ans{big};
  for (auto const i: dp[n]) {
    ans = min(ans, i);
  }
  cout << 1 << endl << ans;
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
