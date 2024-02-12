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
size_t search(auto&& height_map, size_t const i, size_t const j,
              size_t const last_height)
{
  static arr2uz<102, 102> note{};
  if (i < 0 || j < 0 || i >= height_map.size() || j >= height_map[0].size()) {
    return 0;
  }
  // std::cout << "Searching for new way..." << '\n';
  if (last_height <= height_map[i][j]) {
    return 0;
  }
  if (note[i][j] != 0) {
    // std::cout << "Using old data..." << '\n';
    return note[i][j];
  }
  // print(note);
  // for (size_t i{}; i != 5; ++i) {
  //   for (size_t j{}; j != 5; ++j) {
  //     std::cout << note[i][j] << ' ';
  //   }
  //   std::cout << '\n';
  // }
  // std::cout << "Current circulated pos: " << i << ' ' << j << '\n';
  // std::cout << '\n';
  return note[i][j]
         = std::ranges::max({search(height_map, i + 1, j, height_map[i][j]),
                             search(height_map, i - 1, j, height_map[i][j]),
                             search(height_map, i, j + 1, height_map[i][j]),
                             search(height_map, i, j - 1, height_map[i][j])})
           + 1;
}
void solve_case()
{
  size_t x{};
  size_t y{};
  std::cin >> x >> y;
  vec2uz height_map(x, y);
  input(height_map);

  size_t max_length{};
  for (size_t i{}; i != x; ++i) {
    for (size_t j{}; j != y; ++j) {
      max_length = std::ranges::max(max_length, search(height_map, i, j, -1UZ));
    }
  }
  std::cout << max_length;
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
