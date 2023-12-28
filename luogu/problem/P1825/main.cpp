#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <queue>
#include <ranges>
#include <string_view>
#include <unordered_map>
#include <vector>

// configs
using ::std::size_t;

namespace impl {
  template<typename value_t> using vec2 = std::vector<std::vector<value_t>>;
  template<typename T> concept is_pair = requires(T t) {
    t.first;
    t.second;
  };
} // namespace impl
template<size_t i, size_t j, typename value_t> using arr2 = std::array<std::array<value_t, j>, i>;
template<size_t i, size_t j> using arr2uz = arr2<i, j, size_t>;
template<size_t i, size_t j> using arr2ll = arr2<i, j, long long>;
template<typename value_t> class vec2 : public impl::vec2<value_t> {
public:
  vec2(size_t const i, size_t const j): impl::vec2<value_t>(i, std::vector<value_t>(j)) {}
};
using vec2uz = vec2<size_t>;
using vec2ll = vec2<long long>;
auto&& operator>>(auto&& is, auto&& t)
{
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      is >> ele;
    }
  }
  else if constexpr (impl::is_pair<decltype(t)>) {
    is >> t.first >> t.second;
  }
  else {
    is >> t;
  }
  return is;
}
auto&& operator<<(auto&& os, auto&& t)
{
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      os << ele << ' ';
    }
    os << '\n';
  }
  else if constexpr (impl::is_pair<decltype(t)>) {
    os << t.first << ": " << t.second << ", ";
  }
  else {
    os << t << ' ';
  }
  return os;
}
void debug([[maybe_unused]] std::string_view const& sv, [[maybe_unused]] auto&& t)
{
#ifdef DEBUG
  std::cout << sv << ": " << t << '\n';
#endif
}
struct pos_t {
  auto operator<=>(pos_t const&) const = delete;
  auto operator+(pos_t const& rhs) const { return pos_t{x + rhs.x, y + rhs.y, depth + 1}; }
  long long x;
  long long y;
  size_t depth;
};
void solve_case()
{
  long long n{};
  long long m{};
  std::cin >> n >> m;
  vec2<char> v(n, m);
  std::cin >> v;
  pos_t start{};
  pos_t end{};
  std::unordered_map<char, std::vector<pos_t>> trans;
  for (long long i{}; i != n; ++i) {
    for (long long j{}; j != m; ++j) {
      if (v[i][j] == '@') {
        start = pos_t{i, j, 0};
      }
      else if (std::isalpha(v[i][j]) != 0) {
        trans[v[i][j]].emplace_back(i, j);
      }
      else if (v[i][j] == '=') {
        end = pos_t{i, j, 0};
      }
    }
  }

  constexpr std::array<pos_t, 4> dirs{pos_t{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

  std::queue<pos_t> q;
  vec2<bool> visited(n, m);
  q.push(start);
  while (!q.empty()) {
    auto front{q.front()};
    auto x{front.x};
    auto y{front.y};
    auto c{v[x][y]};
    if (c == '=') {
      std::cout << front.depth;
      return;
    }
    if (!visited[x][y] && c != '#') {
      // std::cout << "x,y,c: " << x << ' ' << y << ' ' << c << '\n';
      if (isalpha(c) != 0) {
        auto&& dest{x == trans[c][0].x && y == trans[c][0].y ? trans[c][1] : trans[c][0]};
        front = {dest.x, dest.y, front.depth};
      }
      if (c != '#') {
        for (auto&& dir: dirs) {
          q.push(front + dir);
        }
        visited[x][y] = true;
      }
    }
    q.pop();
  }
  std::cout << -1;
}
int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // std::cout.tie(nullptr);

  size_t t{1};
  // std::cin >> t;
  for (size_t i{}; i != t; ++i) {
    solve_case();
  }
  return 0;
}
