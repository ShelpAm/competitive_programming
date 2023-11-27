#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
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
  vec2(size_t const i, size_t const j, size_t k)
      : vec2_impl<value_t>(i, std::vector<value_t>(j, k))
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
void solve_case()
{
  size_t n{};
  size_t m{};
  std::cin >> n >> m;
  vec2ll d(n + 2, n + 2, 0);
  for (size_t i{}; i != m; ++i) {
    size_t x1{};
    size_t y1{};
    size_t x2{};
    size_t y2{};
    std::cin >> x1 >> y1 >> x2 >> y2;
    ++d[x1][y1];
    --d[x1][y2 + 1];
    --d[x2 + 1][y1];
    ++d[x2 + 1][y2 + 1];
  }
  vec2uz v(n + 2, n + 2, 0);
  std::ranges::copy(d[0], v[0].begin());
  for (size_t i{1}; i != n; ++i) {
    v[0][i] = d[0][i];
  }
  for (size_t i{1}; i != n + 1; ++i) {
    for (size_t j{1}; j != n + 1; ++j) {
      v[i][j] = v[i - 1][j] + v[i][j - 1] + d[i][j] - v[i - 1][j - 1];
    }
  }
  for (size_t i{1}; i != n + 1; ++i) {
    for (size_t j{1}; j != n + 1; ++j) {
      std::cout << v[i][j] << ' ';
    }
    std::cout << '\n';
  }
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
