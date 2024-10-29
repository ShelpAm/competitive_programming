/*Problem: 图与传送*/
/*Contest: unknown_contest*/
/*Judge: NowCoder*/
/*URL: https://ac.nowcoder.com/acm/contest/94329/I*/
/*Start: Sat 26 Oct 2024 04:13:51 PM CST*/
/*Author: ShelpAm*/

// #include <bits/stdc++.h>
#include <algorithm>
#include <bit>
#include <bitset>
#include <cassert>
#include <chrono>
#include <climits>
#include <complex>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numbers>
#include <numeric>
#include <queue>
#include <random>
#include <ranges>
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace {
[[maybe_unused]] constexpr std::uint_fast64_t mod998244353{998'244'353ULL};
[[maybe_unused]] constexpr std::uint_fast64_t mod1e9p7{1'000'000'007ULL};
[[maybe_unused]] constexpr double eps{1e-8};
template <typename T> constexpr T inf{std::numeric_limits<T>::max() / 4};
template <typename T> constexpr T max{std::numeric_limits<T>::max()};

// Concepts.
namespace shelpam::concepts {
template <typename> struct is_pair_t : std::false_type {};
template <typename T, typename U>
struct is_pair_t<std::pair<T, U>> : std::true_type {};
template <typename T>
concept pair = is_pair_t<T>::value;
template <typename> struct is_tuple_t : std::false_type {};
template <typename... Ts>
struct is_tuple_t<std::tuple<Ts...>> : std::true_type {};
template <typename... Ts>
concept tuple = is_tuple_t<Ts...>::value;
} // namespace shelpam::concepts

auto operator>>(auto &istream, auto &&t) -> decltype(istream)
{
  using T = std::remove_cvref_t<decltype(t)>;
  static_assert(!shelpam::concepts::tuple<T>, "tuple: not implemented yet.\n");
  if constexpr (std::ranges::range<T>) {
    for (auto &ele : t) {
      istream >> ele;
    }
  }
  else if constexpr (shelpam::concepts::pair<T>) {
    istream >> t.first >> t.second;
  }
  else {
    istream >> t;
  }
  return istream;
}
#ifndef ONLINE_JUDGE
#include "/home/shelpam/Documents/projects/competitive-programming/libs/debug.h"
#else
#define debug(...)
#endif
auto chmax(auto &value, auto const &other) noexcept -> bool
{
  if (value < other) {
    value = other;
    return true;
  }
  return false;
}
auto chmin(auto &value, auto const &other) noexcept -> bool
{
  if (value > other) {
    value = other;
    return true;
  }
  return false;
}
constexpr auto sum_of(std::ranges::range auto const &coll) noexcept
{
  return std::accumulate(coll.begin(), coll.end(), std::int_fast64_t{});
}
constexpr auto pow(auto a, std::int_fast64_t b, std::uint_fast64_t p)
{
  static_assert(sizeof(a) > sizeof(int), "Use of int is bug-prone.");
  if (b < 0) {
    throw std::invalid_argument{"Invalid exponent. It should be positive."};
  }
  decltype(a) res{1};
  while (b != 0) {
    if ((b & 1) == 1) {
      res = res * a % p;
    }
    a = a * a % p;
    b >>= 1;
  }
  return res;
}
auto binary_search(std::invocable<std::int_fast64_t> auto check,
                   std::int_fast64_t ok, std::int_fast64_t ng,
                   bool check_ok = true) -> std::int_fast64_t
{
  if (check_ok && !check(ok)) {
    throw std::invalid_argument{"check isn't true on 'ok'."};
  }
  while (std::abs(ok - ng) > 1) {
    auto const x{(ok + ng) / 2};
    (check(x) ? ok : ng) = x;
  }
  return ok;
}
constexpr auto lsb(std::signed_integral auto i) noexcept -> decltype(i)
{
  return i & -i;
}
// i mustn't be 0
constexpr auto msb(std::unsigned_integral auto i) -> int
{
  if (i == 0) {
    throw std::invalid_argument{"i must be positive."};
  }
  return sizeof(i) * CHAR_BIT - 1 - std::countl_zero(i);
}
/*[[maybe_unused]] auto gen_rand() noexcept*/
/*{*/
/*  static std::mt19937_64 rng(*/
/*      std::chrono::steady_clock::now().time_since_epoch().count());*/
/*  return rng();*/
/*}*/
void solve_case();
} // namespace
auto main() -> int
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  constexpr auto my_precision{10};
  std::cout << std::fixed << std::setprecision(my_precision);
  int t{1};
  std::cin >> t;
  for (int i{}; i != t; ++i) {
    try {
      std::cerr << "Test case " << i << '\n';
      solve_case();
    }
    catch (std::exception &e) {
      std::cerr << "Exception: " << e.what() << '\n';
    }
  }
  return 0;
}
namespace {
using i64 = std::int_fast64_t;
using u64 = std::uint_fast64_t;
namespace shelpam::graph {
constexpr auto infinity{std::numeric_limits<std::int_fast64_t>::max() / 4};
struct Edge : public std::pair<std::int_fast64_t, int> {
  Edge() = default;
  Edge(std::int_fast64_t f, std::int_fast64_t s)
      : std::pair<std::int_fast64_t, int>{f, s}
  {
  }
  auto operator+(Edge const &other) const -> Edge
  {
    return Edge{first + other.first, second + other.second};
  }
  auto operator>(Edge const &other) const
  {
    return std::tie(first, second) > std::tie(other.first, other.second);
  }
};
using edge_t = Edge;
class Graph {
public:
  // static auto read(int num_of_vertices, int num_of_edges, bool directed,
  //                  bool contains_w, bool read_from_1 = true) -> Graph
  // {
  //   Graph g(num_of_vertices);
  //   for (int i = 0; i != num_of_edges; ++i) {
  //     int u;
  //     int v;
  //     std::int_fast64_t w;
  //     std::cin >> u >> v;
  //     if (contains_w) {
  //       std::cin >> w;
  //     }
  //     else {
  //       w = 1;
  //     }
  //     if (read_from_1) {
  //       --u, --v;
  //     }
  //     g.add_edge(u, v, w);
  //     if (!directed) {
  //       g.add_edge(v, u, w);
  //     }
  //   }
  //   return g;
  // }

  explicit Graph(std::size_t max_num_of_vertices)
      : adjacent(max_num_of_vertices)
  {
  }

  void add_edge(std::size_t u, std::size_t v, edge_t w)
  {
    adjacent[u].emplace_back(w, v);
  }

  [[nodiscard]] auto edges_of(std::size_t u) const
  {
    return adjacent[u];
  }

  [[nodiscard]] auto size() const -> std::size_t
  {
    return adjacent.size();
  }

private:
  std::vector<std::vector<std::pair<edge_t, int>>> adjacent;
};
struct Dijkstra_result {
  std::vector<edge_t> distance;
  std::vector<int> previous;
};
auto dijkstra(Graph const &g, std::vector<int> const &sources)
    -> Dijkstra_result
{
  std::vector<edge_t> dist(g.size(), edge_t{infinity, infinity});
  std::vector<int> prev(g.size(), -1);

  // Nodes not in q had got the shortest distance from source(s)
  auto by_dist{[&](int l, int r) {
    return std::tie(dist[l], l) < std::tie(dist[r], r);
  }};
  std::set<int, decltype(by_dist)> q{by_dist};
  for (auto const source : sources) {
    dist[source] = {};
    q.insert(source);
  }

  while (!q.empty()) { // The main loop
    // Extract and remove the closest vertex from queue.
    auto const u{*q.begin()};
    q.erase(u);

    for (auto const &[w, v] : g.edges_of(u)) {
      if (auto const alt{dist[u] + w}; dist[v] > alt) {
        q.erase(v);
        dist[v] = alt;
        prev[v] = u;
        q.insert(v);
      }
    }
  }

  return {.distance{dist}, .previous{prev}};
}
auto dijkstra(Graph const &graph, int source) -> Dijkstra_result
{
  return dijkstra(graph, std::vector<int>{source});
}

} // namespace shelpam::graph
void solve_case()
{
  using namespace shelpam::graph;

  int n, m, k;
  i64 w;
  std::cin >> n >> m >> k >> w;

  Graph g(n);
  for (int i{}; i != m; ++i) {
    i64 u, v, w;
    std::cin >> u >> v >> w;
    --u, --v;
    g.add_edge(u, v, {w, 0});
    g.add_edge(v, u, {w, 0});
  }

  for (int i{}; i + k != n; ++i) {
    g.add_edge(i, i + k, {w, 1});
    g.add_edge(k + i, i, {w, 1});
  }

  auto d{dijkstra(g, 0).distance[n - 1]};
  if (d == edge_t{infinity, infinity}) {
    std::cout << -1 << ' ' << -1 << '\n';
  }
  else {
    std::cout << d.first << ' ' << d.second << '\n';
  }
}
} // namespace
