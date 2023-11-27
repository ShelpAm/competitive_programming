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
size_t id(size_t i, size_t j, size_t n)
{
  return i * n + j;
}
const int xs[] = {-1, 0, 1, 0};
const int ys[] = {0, -1, 0, 1};
bool visited[22][22] = {};
std::vector<std::pair<size_t, size_t>> path;
void dfs(std::vector<size_t>& cols, std::vector<size_t>& rows, size_t const n,
         size_t const x, size_t const y)
{
  if (x == -1 || y == -1 || x == n || y == n) {
    return;
  }
  if (rows[x] == 0 || cols[y] == 0) {
    return;
  }
  if (visited[x][y]) {
    return;
  }
  --rows[x];
  --cols[y];
  path.push_back({x, y});
  visited[x][y] = true;
  if (x == n - 1 && y == n - 1) {
    for (size_t i: cols) {
      if (i != 0) {
        ++rows[x];
        ++cols[y];
        path.pop_back();
        visited[x][y] = false;
        return;
      }
    }
    for (size_t i: rows) {
      if (i != 0) {
        ++rows[x];
        ++cols[y];
        path.pop_back();
        visited[x][y] = false;
        return;
      }
    }
    for (std::pair<size_t, size_t> const& pos: path) {
      std::cout << id(pos.first, pos.second, n) << ' ';
    }
    exit(0);
  }

  for (size_t i = 0; i != 4; ++i) {
    dfs(cols, rows, n, x + xs[i], y + ys[i]);
  }
  ++rows[x];
  ++cols[y];
  path.pop_back();
  visited[x][y] = false;
}
void solve_case()
{
  size_t n;
  std::cin >> n;
  std::vector<size_t> cols(n);
  std::vector<size_t> rows(n);
  for (size_t& col: cols) {
    std::cin >> col;
  }
  for (size_t& row: rows) {
    std::cin >> row;
  }
  std::vector<std::pair<size_t, size_t>> path;
  dfs(cols, rows, n, 0, 0);
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
