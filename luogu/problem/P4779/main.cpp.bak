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
  auto operator<(pos_t const& other) const { return distance > other.distance; }
  size_t i;
  size_t distance;
};
constexpr auto inf{std::numeric_limits<size_t>::max()};
void solve_case()
{
  size_t n{};
  size_t m{};
  size_t s{};
  std::cin >> n >> m >> s;
  std::vector<std::unordered_map<size_t, size_t>> G(n + 1);
  for (size_t i{}; i != m; ++i) {
    size_t u{};
    size_t v{};
    size_t w{};
    std::cin >> u >> v >> w;
    if (!G[u].contains(v) || G[u][v] > w) {
      G[u][v] = w;
    }
  }
  std::priority_queue<pos_t> q;
  std::vector<size_t> dist(n + 1, inf);
  q.push({s, 0});
  while (!q.empty()) {
    if (dist[q.top().i] == inf) {
      dist[q.top().i] = q.top().distance;
      for (auto const& [dest, distance]: G[q.top().i]) {
        q.push({dest, distance + dist[q.top().i]});
      }
    }
    q.pop();
  }
  std::cout << (dist | std::ranges::views::drop(1));
}
int main()
{
  // freopen("/home/shelpam/in", "r", stdin);
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
