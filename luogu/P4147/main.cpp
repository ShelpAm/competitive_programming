#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <stack>
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
  size_t m{};
  std::cin >> n >> m;
  vec2<char> v(n, m);
  std::cin >> v;

  // All data in dp are defaulted to 0.
  vec2uz dp(n + 1, m);
  for (size_t i{1}; i != n + 1; ++i) {
    for (size_t j{}; j != m; ++j) {
      if (v[i - 1][j] == 'F') {
        dp[i][j] = dp[i - 1][j] + 1;
      }
    }
    dp[i].emplace_back(0);
  }

  size_t ans{};
  for (auto const& row: dp | std::ranges::views::drop(1)) {
    std::stack<size_t> h;
    std::stack<size_t> w;
    for (auto const height: row) {
      if (!h.empty() && height < h.top()) {
        size_t width{};
        while (!h.empty() && h.top() > height) {
          width += w.top();
          ans = std::ranges::max(ans, width * h.top());
          h.pop();
          w.pop();
        }
        w.push(width + 1);
      }
      else {
        w.push(1);
      }
      h.push(height);
    }
  }
  std::cout << ans * 3;
}
int main()
{
  // std::freopen("/home/shelpam/in", "r", stdin);
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
