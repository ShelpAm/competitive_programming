#include <array>
#include <cstddef>
#include <iostream>
#include <ranges>
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
  // return;
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
size_t row{};
size_t col{};
void dfs(vec2<char>& map, size_t const i, size_t const j)
{
  if (i < 0 || i >= row || j < 0 || j >= col) {
    return;
  }
  if (map[i][j] == '0') {
    return;
  }
  map[i][j] = '0';
  dfs(map, i + 1, j);
  dfs(map, i - 1, j);
  dfs(map, i, j + 1);
  dfs(map, i, j - 1);
}
void search(vec2<char>& map, size_t const i, size_t const j, char const type)
{
  if (i < 0 || i >= row || j < 0 || j >= col) {
    return;
  }
  if (map[i][j] != type) {
    return;
  }
  map[i][j] = '0';
  search(map, i + 1, j, type);
  search(map, i - 1, j, type);
  search(map, i, j + 1, type);
  search(map, i, j - 1, type);
}
void solve_case()
{
  row = read<size_t>();
  col = read<size_t>();
  vec2<char> map(row, col);
  for (auto&& cv: map) {
    for (auto&& c: cv) {
      std::cin >> c;
    }
  }
  dfs(map, 0, 0);
  print(map);
  return;
  size_t count{};
  for (size_t i{}; i != row; ++i) {
    for (size_t j{}; j != col; ++j) {
      if (map[i][j] != '0' && map[i][j] != '1') {
        search(map, i, j, map[i][j]);
        print(map);
        ++count;
      }
    }
  }
  std::cout << count;
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
