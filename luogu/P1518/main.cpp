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
  arr2<10, 10, char> map;
  input(map);

  size_t farmer_x{};
  size_t farmer_y{};
  size_t cow_x{};
  size_t cow_y{};

  for (size_t i{}; i != 10; ++i) {
    for (size_t j{}; j != 10; ++j) {
      if (map[i][j] == 'F') {
        farmer_x = i;
        farmer_y = j;
      }
      else if (map[i][j] == 'C') {
        cow_x = i;
        cow_y = j;
      }
    }
  }

  constexpr long long dir[4][2]{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
  size_t cow_dir{};
  size_t farmer_dir{};

  size_t num_steps{};
  while (cow_x != farmer_x || cow_y != farmer_y) {
    auto move{[&](size_t& d, size_t& x, size_t& y) {
      auto obj_x{x + dir[d % 4][0]};
      auto obj_y{y + dir[d % 4][1]};
      if (obj_x < 0 || obj_x >= 10 || obj_y < 0 || obj_y >= 10
          || map[obj_x][obj_y] == '*') {
        ++d;
      }
      else {
        x = obj_x;
        y = obj_y;
      }
    }};

    move(cow_dir, cow_x, cow_y);
    move(farmer_dir, farmer_x, farmer_y);
    ++num_steps;
    if (cow_x == farmer_x && cow_y == farmer_y) {
      std::cout << num_steps;
      return;
    }
    if (num_steps >= 100000) {
      std::cout << 0;
      return;
    }
  }
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
