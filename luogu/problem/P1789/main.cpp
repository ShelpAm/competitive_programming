#include <array>
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
void solve_case()
{
  size_t n{};
  size_t m{};
  size_t k{};
  std::cin >> n >> m >> k;
  std::vector<bool> v(n * n, true);
  for (size_t i{}; i != m; ++i) {
    size_t x_{};
    size_t y_{};
    std::cin >> x_ >> y_;
    x_ -= 1;
    y_ -= 1;
    std::array offset_x{-2, -1, 0, 1, 2, -1, -1, 1, 1, 0, 0, 0, 0};
    std::array offset_y{0, 0, 0, 0, 0, -1, 1, -1, 1, -2, -1, 1, 2};
    for (size_t p{}; p != offset_x.size(); ++p) {
      size_t x{x_};
      size_t y{y_};
      x += offset_x[p];
      y += offset_y[p];
      if (x >= 0 && x < n && y >= 0 && y < n) {
        v[x * n + y] = false;
      }
    }
  }
  for (size_t i{}; i != k; ++i) {
    size_t x_{};
    size_t y_{};
    std::cin >> x_ >> y_;
    x_ -= 1;
    y_ -= 1;
    for (long long p{-2}; p != 3; ++p) {
      for (long long q{-2}; q != 3; ++q) {
        size_t x{x_};
        size_t y{y_};
        x += p;
        y += q;
        if (x >= 0 && x < n && y >= 0 && y < n) {
          v[x * n + y] = false;
        }
      }
    }
  }
  std::cout << std::accumulate(v.begin(), v.end(), 0);
  // for (size_t i{}; i != n; ++i) {
  //   for (size_t j{}; j != n; ++j) {
  //     std::cout << v[i * n + j] << ' ';
  //   }
  //   std::cout << '\n';
  // }
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
