#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <ranges>
#include <string_view>
#include <vector>

using ::std::size_t;

// constexpr bool debug{false};

template<typename T> T read()
{
  T tmp;
  std::cin >> tmp;
  return tmp;
}
template<typename value_t> class input_value {
public:
  input_value(): value_(read<value_t>()) {}
  input_value(const input_value&) = delete;
  input_value(input_value&&) = delete;
  input_value& operator=(const input_value&) = delete;
  input_value& operator=(input_value&&) = delete;
  ~input_value() = default;
  operator value_t&() { return value(); }
  value_t& value() { return value_; }
private:
  value_t value_;
};
template<size_t i, size_t j, typename value_type> using arr2
    = std::array<std::array<value_type, j>, i>;
template<size_t i, size_t j> using arr2uz = arr2<i, j, size_t>;
template<size_t i, size_t j> using arr2ll = arr2<i, j, long long>;
template<typename value_type> using vec2_impl
    = std::vector<std::vector<value_type>>;
template<typename value_t> class vec2 : public vec2_impl<value_t> {
public:
  vec2(size_t const i, size_t const j)
      : vec2_impl<value_t>(i, std::vector<value_t>(j, {}))
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
void input(auto&& t)
{
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      input(ele);
    }
  }
  else if constexpr (is_pair<decltype(t)>) {
    std::cin >> t.first >> t.second;
  }
  else {
    std::cin >> t;
  }
}
std::pair<bool, size_t> check(auto&& v, size_t const d)
{
  for (size_t i{1}; i != v.size(); ++i) {
    if (auto delta{v[i] - v[i - 1]}; delta % d != 0) {
      return {false, delta};
    }
  }
  return {true, -1UZ};
}
void solve_case()
{
  size_t n{};
  std::cin >> n;
  std::vector<size_t> v(n);
  input(v);

  if (v[0] == v[1]) {
    std::cout << n;
    return;
  }

  std::ranges::sort(v);
  size_t d{-1UZ};
  for (size_t i{1}; i != n; ++i) {
    d = std::ranges::min(d, v[i] - v[i - 1]);
  }

  while (true) {
    auto info{check(v, d)};
    if (info.first) {
      break;
    }
    d = std::gcd(d, info.second);
  }

  std::cout << (v.back() - v.front()) / d + 1;
}
int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // std::cout.tie(nullptr);

  size_t n{1};
  // n = read<size_t>();
  for (size_t i{}; i != n; ++i) {
    solve_case();
  }
  return 0;
}
