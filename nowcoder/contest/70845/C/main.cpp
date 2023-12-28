#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
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
template<typename value_type> using vec2_impl = std::vector<std::vector<value_type>>;
template<typename value_t> class vec2 : public vec2_impl<value_t> {
public:
  vec2(size_t const i, size_t const j): vec2_impl<value_t>(i, std::vector<value_t>(j)) {}
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
enum {
  t,
  tx,
  o
};
std::array<size_t, 20001> f{};
void solve_case()
{
  constexpr size_t num_letters{26};
  constexpr size_t mod{998244353};
  size_t n{};
  std::cin >> n;

  if (n < 3) {
    std::cout << "0\n";
    return;
  }

  f[0] = 1;
  for (size_t i{1}; i != f.size(); ++i) {
    f[i] = f[i - 1] * num_letters;
    f[i] %= mod;
  }

  size_t sum{f[n]};
  std::vector<size_t> dp(n + 1);
  std::vector<char> c(n + 1);

  size_t m{1};
  for (size_t i{2}; i != n + 1; ++i) {
    if (c[i - 1] == tx) {
      m *= 25;
      c[i] = o;
    }
    else if (c[i - 1] == t) {
    }
  }

  sum -= dp[n];
  sum %= mod;
  std::cout << sum << std::endl;
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
