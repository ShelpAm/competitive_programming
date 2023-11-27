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
void search(auto&& maze, auto&& was_searched_v,
            std::vector<std::pair<size_t, size_t>>& path, size_t const x,
            size_t const y, char const last_value)
{
  if (x < 0 || x >= maze.size() || y < 0 || y >= maze[0].size()) {
    return;
  }
  // std::cout << x << y << '\n';
  if (last_value == maze[x][y] || was_searched_v[x][y]) {
    return;
  }
  was_searched_v[x][y] = true;
  path.emplace_back(x, y);
  search(maze, was_searched_v, path, x, y - 1, maze[x][y]);
  search(maze, was_searched_v, path, x, y + 1, maze[x][y]);
  search(maze, was_searched_v, path, x + 1, y, maze[x][y]);
  search(maze, was_searched_v, path, x - 1, y, maze[x][y]);
}
void solve_case()
{
  // std::freopen("input.txt", "r", stdin);
  // std::freopen("out.txt", "w", stdout);
  size_t n{};
  size_t m{};
  std::cin >> n >> m;
  vec2<char> maze(n, n);
  input(maze);
  vec2<size_t> searched_blocks(n, n);
  for (size_t i{}; i != m; ++i) {
    size_t x{};
    size_t y{};
    std::cin >> x >> y;
    --x;
    --y;
    auto count{[&]() {
      if (searched_blocks[x][y] != 0) {
        // std::cout << "Using old data: ";
        return searched_blocks[x][y];
      }
      vec2<bool> is_connected_v(n, n);
      std::vector<std::pair<size_t, size_t>> path;
      search(maze, is_connected_v, path, x, y, '2');
      std::ranges::for_each(path, [&searched_blocks, &path](auto&& pair) {
        searched_blocks[pair.first][pair.second] = path.size();
      });
      // std::cout << "New searching: ";
      return path.size();
    }()};
    std::cout
        // << i << ' '
        << count << '\n';
    // print(searched_blocks);
  }
}
int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  size_t n{1};
  // n = read<size_t>();
  for (size_t i{}; i != n; ++i) {
    solve_case();
  }
  return 0;
}
