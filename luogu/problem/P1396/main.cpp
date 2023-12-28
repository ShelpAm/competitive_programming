#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <map>
#include <queue>
#include <ranges>
#include <set>
#include <string_view>
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
void solve_case()
{
  size_t n = 0;
  size_t m = 0;
  size_t s = 0;
  size_t t = 0;
  std::cin >> n >> m >> s >> t;
  std::vector<std::map<size_t, size_t>> conn(n + 1);

  size_t max_w{};
  size_t min_w{0x3f3f3f};
  for (size_t i{}; i != m; ++i) {
    size_t u{};
    size_t v{};
    size_t w{};
    std::cin >> u >> v >> w;
    if (conn[u].contains(v)) {
      conn[u][v] = std::ranges::min(conn[u][v], w);
      conn[v][u] = std::ranges::min(conn[v][u], w);
    }
    else {
      conn[u][v] = w;
      conn[v][u] = w;
    }
    max_w = std::ranges::max(max_w, w);
    min_w = std::ranges::min(min_w, w);
  }

  auto check{[&](size_t const mid) {
    std::vector<bool> visited(n + 1);
    std::queue<size_t> q;
    q.push(s);
    while (!q.empty()) {
      // std::cout << "Now q.front is " << q.front() << '\n';
      if (q.front() == t) {
        // std::cout << "GETTING ENDING POINT.\n";
        return true;
      }
      if (!visited[q.front()]) {
        for (auto&& [to, w]: conn[q.front()]) {
          // std::cout << "Considering to go to " << to << ", with a w being " << w << '\n';
          if (w > mid) {
            // std::cout << "But w is too great(" << w << ") that is beyond the limit(mid) " << mid
            //           << '\n';
            continue;
          }
          q.push(to);
          // std::cout << "New point(" << to << ") pushed.\n";
        }
        visited[q.front()] = true;
      }
      // else {
      //   std::cout << "But here has been visited before.\n";
      // }
      q.pop();
    }
    return false;
  }};

  size_t l{min_w};
  size_t r{max_w};
  while (l < r) {
    auto mid{(l + r) >> 1};
    if (check(mid)) {
      r = mid;
    }
    else {
      l = mid + 1;
    }
  }
  std::cout << l;
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
