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
void solve_case()
{
  constexpr size_t mod{10007};

  size_t n{};
  size_t m{};
  std::cin >> n >> m;
  std::vector<size_t> number(n + 1);
  std::cin >> (number | std::ranges::views::drop(1));
  std::vector<size_t> color(n + 1);
  std::cin >> (color | std::ranges::views::drop(1));

  std::vector<std::array<std::vector<size_t>, 2>> indices_of_color(m + 1);
  for (size_t i{1}; i != n + 1; ++i) {
    indices_of_color[color[i]][i % 2].emplace_back(i);
  }

  auto calc{[&number](auto&& indices) {
    size_t sum_number{};
    for (auto const idx: indices) {
      sum_number += number[idx];
    }
    // std::cout << "Now is calculating ";
    // print(indices);
    // std::cout << "Precalculated sum_number is " << sum_number << ' ';
    size_t sum{};
    for (auto const idx: indices) {
      sum += idx * ((indices.size() - 2) * number[idx] + sum_number);
    }
    // std::cout << " and total corresponding sum is " << sum << '\n';
    return sum;
  }};

  size_t ans{};
  for (auto&& by_color: indices_of_color) {
    for (auto&& by_odd_even: by_color) {
      ans += calc(by_odd_even);
      ans %= mod;
    }
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
