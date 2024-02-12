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
constexpr size_t mod{size_t(1e9) + 7};
size_t c_n_2(size_t const n)
{
  return (n % mod * (n - 1) % mod / 2) % mod;
}
void solve_case()
{
  size_t n{};
  std::cin >> n;
  std::vector<size_t> a(n);
  std::cin >> a;

  std::array<size_t, size_t(5e3 + 5)> num_of_len{};
  for (auto const i: a) {
    ++num_of_len[i];
  }

  size_t ans{};
  for (size_t i{1}; i != num_of_len.size(); ++i) {
    if (num_of_len[i] < 2) {
      continue;
    }
    size_t tmp{};
    for (size_t j{1}; 2 * j < i; ++j) {
      tmp += num_of_len[i - j] * num_of_len[j];
      ans %= mod;
    }
    if (i % 2 == 0) {
      tmp += c_n_2(num_of_len[i >> 1]);
    }
    tmp *= c_n_2(num_of_len[i]);
    ans = (ans + tmp) % mod;
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
