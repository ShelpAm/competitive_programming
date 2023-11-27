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
void move_to_left(auto&& v, size_t const right, size_t count)
{
  // Optimization
  // v[right] = '0';
  v[right - count] = '1';
}
size_t count_connected_blocks(auto&& v, size_t right)
{
  size_t count{};
  while (right != -1 && v[right--] == '1') {
    ++count;
  }
  return count;
}
void solve_case()
{
  size_t n{};
  std::cin >> n;
  std::vector<char> v(n);
  input(v);
  auto num_of_bit_1{std::ranges::count(v, '1')};
  size_t num_of_operations{};
  size_t num_of_connected_blocks{};
  for (size_t i{n - 1}; i != -1; --i) {
    if (num_of_bit_1 > i) {
      std::cout << -1 << ' ';
      continue;
    }
    num_of_connected_blocks
        += count_connected_blocks(v, i - num_of_connected_blocks);
    move_to_left(v, i, num_of_connected_blocks);
    num_of_operations += num_of_connected_blocks;
    std::cout << num_of_operations << ' ';
  }
  std::cout << '\n';
}
int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // std::cout.tie(nullptr);

  size_t n{1};
  n = read<size_t>();
  for (size_t i{}; i != n; ++i) {
    solve_case();
  }
  return 0;
}
