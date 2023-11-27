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
long long w(long long const a, long long const b, long long const c)
{
  static std::array<arr2ll<25, 25>, 25> note{};
  if (a <= 0 || b <= 0 || c <= 0) {
    return 1;
  }
  if (note[a][b][c] != 0) {
    // std::cout << "Using old data...\n";
    return note[a][b][c];
  }
  // std::cout << "Searching for old data...\n";
  if (a > 20 || b > 20 || c > 20) {
    return note[a][b][c] = w(20, 20, 20);
  }
  if (a < b && b < c) {
    return note[a][b][c] = w(a, b, c - 1) + w(a, b - 1, c - 1) - w(a, b - 1, c);
  }
  return note[a][b][c] = w(a - 1, b, c) + w(a - 1, b - 1, c)
                         + w(a - 1, b, c - 1) - w(a - 1, b - 1, c - 1);
}
void solve_case()
{
  while (true) {
    std::array<long long, 3> arr{};
    input(arr);
    std::array<long long, 3> copy{arr};
    if (arr[0] == -1 && arr[1] == -1 && arr[2] == -1) {
      return;
    }
    for (size_t i{}; i != 3; ++i) {
      if (arr[i] > 21) {
        arr[i] = 21;
      }
    }
    std::cout << "w(" << copy[0] << ", " << copy[1] << ", " << copy[2]
              << ") = " << w(arr[0], arr[1], arr[2]) << '\n';
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
