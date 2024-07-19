// Problem: G - Sum of Tree Distance
// Contest: UNIQUE VISION Programming Contest 2024 Summer (AtCoder Beginner
// Contest 359) Judge: AtCoder URL:
// https://atcoder.jp/contests/abc359/tasks/abc359_g Memory Limit: 1024 Time
// Limit: 4000 Start: Sat 22 Jun 2024 08:00:12 PM CST Author: ShelpAm

#include <bits/stdc++.h>

#ifdef __cpp_lib_ranges
#include <ranges>
#endif

using i64 = std::int_fast64_t;
using u64 = std::uint_fast64_t;
using vi = std::vector<i64>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;
using vvvvi = std::vector<vvvi>;
using vu = std::vector<u64>;
using vvu = std::vector<vu>;
using vvvu = std::vector<vvu>;
using vvvvu = std::vector<vvvu>;
using vb = std::vector<bool>;
using vvb = std::vector<vb>;
using vc = std::vector<char>;
using vvc = std::vector<vc>;
using vd = std::vector<double>;
using vvd = std::vector<vd>;
using pii = std::pair<i64, i64>;
using puu = std::pair<u64, u64>;
using triplei = std::tuple<i64, i64, i64>;
using tripleu = std::tuple<u64, u64, u64>;
using quadratici = std::tuple<i64, i64, i64, i64>;
using quadraticu = std::tuple<u64, u64, u64, u64>;

namespace {
[[maybe_unused]] constexpr std::int_fast64_t mod998244353{998'244'353LL};
[[maybe_unused]] constexpr std::int_fast64_t mod1e9p7{1'000'000'007LL};
template <typename T>
[[maybe_unused]] constexpr T inf{std::numeric_limits<T>::max() / 2};
[[maybe_unused]] constexpr double eps{1e-8};

#ifdef __cpp_concepts
namespace impl {
// Concepts.
template <typename T>
concept pair = requires(T t) {
  t.first;
  t.second;
};
template <typename T>
concept string_like = std::same_as<std::string, std::remove_cvref_t<T>> ||
                      std::same_as<std::string_view, std::remove_cvref_t<T>> ||
                      std::convertible_to<std::remove_cvref_t<T>, char const *>;
template <typename> struct is_tuple_t : std::false_type {};
template <typename... T>
struct is_tuple_t<std::tuple<T...>> : std::true_type {};
template <typename... T>
concept tuple = is_tuple_t<T...>::value;
} // namespace impl

constexpr auto &operator>>(auto &istream, auto &&t)
{
  using T = std::remove_cvref_t<decltype(t)>;
  static_assert(!impl::tuple<T>, "[print] tuple: not implemented yet.\n");
#ifdef __cpp_lib_ranges
  if constexpr (std::ranges::range<T>) {
    for (auto &ele : t) {
      istream >> ele;
    }
  }
#endif
  else if constexpr (impl::pair<T>) {
    istream >> t.first >> t.second;
  }
  else {
    istream >> t;
  }
  return istream;
}
constexpr auto print(auto &&t, int depth = 0, auto &out = std::cout) -> void
{
  using T = std::remove_cvref_t<decltype(t)>;
  static_assert(!impl::tuple<T>, "[print] tuple: not implemented yet.\n");
  if constexpr (impl::string_like<T>) {
    out << t;
  }
#ifdef __cpp_lib_ranges
  else if constexpr (std::ranges::range<T>) {
    for (auto const &ele : t) {
      print(ele, depth + 1, out);
    }
    if (depth != 0) {
      out << '\n';
    }
  }
#endif
  else if constexpr (impl::pair<T>) {
    out << "{ ";
    print(t.first, depth + 1, out);
    out << ", ";
    print(t.second, depth + 1, out);
    out << " }, ";
  }
  else {
    out << t << ' ';
  }

  if (depth == 0) {
    out << '\n';
  }
}
#endif
#ifndef ONLINE_JUDGE
constexpr auto debug(std::string_view s, auto &&t) -> void
{
  std::cerr << "[debug] " << s << ": ";
  if constexpr (std::ranges::range<decltype(t)>) {
    std::cerr << '\n';
  }
  print(t, 0, std::cerr);
  std::cerr.flush();
}
#else
#define debug(...)
#endif
#ifdef __cpp_lib_ranges
constexpr auto check_max(auto &value, auto const &other) noexcept -> bool
#else
template <typename T, typename S>
constexpr bool check_max(T &value, S const &other) noexcept
#endif
{
  if (value < other) {
    value = other;
    return true;
  }
  return false;
}
#ifdef __cpp_concepts
constexpr auto check_min(auto &value, auto const &other) noexcept -> bool
#else
template <typename T, typename S>
constexpr bool check_min(T &value, S const &other) noexcept
#endif
{
  if (value > other) {
    value = other;
    return true;
  }
  return false;
}
#ifdef __cpp_concepts
constexpr auto sum_of(auto const &coll) noexcept
#else
template <typename Range> constexpr auto sum_of(Range const &coll) noexcept
#endif
{
  return std::accumulate(coll.begin(), coll.end(), std::int_fast64_t{});
}
#ifdef __cpp_concepts
constexpr auto pow(auto a, std::int_fast64_t b, std::int_fast64_t p) noexcept
#else
template <typename T>
constexpr auto pow(T a, std::int_fast64_t b, std::uint_fast64_t p) noexcept
#endif
{
  assert(b >= 0);
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
template <typename T> [[maybe_unused]] constexpr auto lsb(T i) -> T
{
  static_assert(std::is_signed_v<T>,
                "lsb is implemented based on signed integers.");
  return i & (-i);
}
// i mustn't be 0
[[maybe_unused]] constexpr auto msb(std::uint_fast64_t i) -> int
{
  assert(i != 0);
  return static_cast<int>(sizeof(decltype(i)) * CHAR_BIT - 1 -
                          __builtin_clzll(i));
}
[[maybe_unused]] auto gen_rand()
{
  static std::mt19937_64 rng(
      std::chrono::steady_clock::now().time_since_epoch().count());
  return rng();
}
void solve_case();
void solve_all_cases()
{
  constexpr auto my_precision{10};
  std::cout << std::fixed << std::setprecision(my_precision);
  int t{1};
  /*std::cin >> t;*/
  for (int i = 0; i != t; ++i) {
    solve_case();
  }
}
} // namespace
int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve_all_cases();
  return 0;
}
namespace graph {
constexpr std::int_fast64_t infinity{
    std::numeric_limits<std::int_fast64_t>::max() / 2};
struct graph {
public:
  graph(std::size_t max_num_of_vertices) : adjacent(max_num_of_vertices) {}
  void add_edge(int u, int v, std::int_fast64_t w)
  {
    adjacent[u].emplace_back(w, v);
  }
  [[nodiscard]] std::vector<std::pair<std::int_fast64_t, int>> const &
  edges_of(int u) const
  {
    return adjacent[u];
  }
  std::vector<std::vector<std::pair<std::int_fast64_t, int>>> adjacent;
};
graph read_graph(int const num_of_vertices, int const num_of_edges,
                 bool const directed, bool const contains_w,
                 bool const read_from_1)
{
  graph g(num_of_vertices);
  for (int i = 0; i != num_of_edges; ++i) {
    int u, v;
    std::int_fast64_t w;
    std::cin >> u >> v;
    if (contains_w) {
      std::cin >> w;
    }
    else {
      w = 1;
    }
    if (read_from_1) {
      --u, --v;
    }
    g.add_edge(u, v, w);
    if (!directed) {
      g.add_edge(v, u, w);
    }
  }
  return g;
}
struct bellman_ford_result {
  bool contains_negative_circle;
  std::vector<std::int_fast64_t>
      distance; // When `no_negative_circle` is false, this is usable.
};
bellman_ford_result bellman_ford(graph const &g, int const src,
                                 std::vector<bool> &vis)
{
  int const n{static_cast<int>(g.adjacent.size())};
  std::vector<std::int_fast64_t> dist(g.adjacent.size(), infinity);
  std::vector<int> num_intermediates(g.adjacent.size());
  // std::vector<bool> vis(g.adjacent.size());

  dist[src] = 0;
  vis[src] = true;
  // Only those in `q` could lead to relaxation.
  std::deque<int> q{src};
  auto swap_smaller_to_front{[](std::deque<int> &q) {
    if (q.back() < q.front()) {
      std::swap(q.back(), q.front());
    }
  }};
  while (!q.empty()) {
    auto const u{q.front()};
    q.pop_front();
    swap_smaller_to_front(q);
    vis[u] = false;

    for (auto const [w, v] : g.edges_of(u)) {
      if (auto const alt{dist[u] + w}; check_min(dist[v], alt)) {
        num_intermediates[v] = num_intermediates[u] + 1;
        if (num_intermediates[v] >= n) {
          return {true, {}};
        }
        if (!vis[v]) {
          vis[v] = true;
          q.push_back(v);
          swap_smaller_to_front(q);
        }
      }
    }
  }
  return {false, dist};
}
struct dijkstra_result {
  std::vector<std::int_fast64_t> distance;
  std::vector<std::int_fast64_t> previous;
};
dijkstra_result dijkstra(graph const &graph, int const source)
{
  std::vector<std::int_fast64_t> distance(graph.adjacent.size(), infinity);
  std::vector<std::int_fast64_t> previous(graph.adjacent.size());
  distance[source] = 0;

  // `visited[u]` is true means u has been a start point, and it shouldn't be
  // start point once more.
  std::vector<bool> visited(graph.adjacent.size());

  std::priority_queue<std::pair<std::int_fast64_t, int>,
                      std::vector<std::pair<std::int_fast64_t, int>>,
                      std::greater<>>
      q;
  q.emplace(distance[source], source);

  while (!q.empty()) {          // The main loop
    auto const [_, u]{q.top()}; // Extract the closest vertex. (Get and remove
                                // the best vertex)
    q.pop();

    if (visited[u]) {
      continue;
    }
    visited[u] = true;

    for (auto const &[w, v] : graph.edges_of(u)) {
      if (auto const alt{distance[u] + w}; alt < distance[v]) {
        distance[v] = alt;
        previous[v] = u;
        q.emplace(alt, v);
      }
    }
  }

  return {distance, previous};
}
using adjacent_matrix_t = std::vector<std::vector<std::int_fast64_t>>;
adjacent_matrix_t floyd(graph const &g)
{
  auto const &adjacent{g.adjacent};
  auto const n = static_cast<int>(adjacent.size());

  adjacent_matrix_t f(n, std::vector<std::int_fast64_t>(n, infinity));

  // Initializes data
  for (int u = 0; u != n; ++u) {
    f[u][u] = 0;
    for (auto const &[w, v] : adjacent[u]) {
      f[u][v] = w;
    }
  }

  for (int k = 0; k != n; ++k) {
    // In k-th round (At the end of the round), f[i][j] denotes the minimum
    // distance between i, j, concerning first k vertices.
    for (int i = 0; i != n; ++i) {
      for (int j = 0; j != n; ++j) {
        check_min(f[i][j], f[i][k] + f[k][j]);
      }
    }
  }

  return f;
}
struct toposort_result {
  bool acyclic;
  std::vector<int> order;
};
toposort_result toposort(graph const &g, bool directed)
{
  assert(directed && "haven't implement undirected");
  int const n{static_cast<int>(g.adjacent.size())};
  std::vector<int> in(n);
  for (auto const &edges : g.adjacent) {
    for (auto const [_, v] : edges) {
      ++in[v];
    }
  }
  std::vector<int> order;
  std::queue<int> q;
  for (int i{}; i != n; ++i) {
    if (in[i] == 0) {
      q.push(i);
    }
  }
  if (directed) {
    while (!q.empty()) {
      auto const u{q.front()};
      q.pop();
      order.push_back(u);
      for (auto const [_, v] : g.edges_of(u)) {
        if (--in[v] == 0) {
          q.push(v);
        }
      }
    }
  }
  if (order.size() != g.adjacent.size()) {
    return {false, {}};
  }
  return {true, order};
};
// The graph should only contains left-to-right edges, and should not
// convert/transform the vertices' ID. For example, if you want to make a edge
// from left vertex x to right vertex y, you should use
// `g.add_edge(x, y, 1);` rather than `g.add_edge(x, y + n, 1);`.
int maximum_matching(graph g, int left_size, int right_size)
{
  assert(left_size >= 0 && right_size >= 0);
  assert(g.adjacent.size() == static_cast<std::size_t>(left_size));
  int res{};
  int idx{}; // dfs order, identifying if a vertex was visited in current round
  std::vector<int> dfn(left_size);
  std::vector<int> pa(left_size, -1),
      pb(right_size, -1); // matches from a and matches from b

  // All `u` will represent left side vertices.
  std::function<bool(int)> dfs{[&](int u) {
    dfn[u] = idx;
    // direct match
    for (auto const [_, v] : g.edges_of(u)) {
      if (pb[v] == -1) {
        // make a match: u - v
        pa[u] = v;
        pb[v] = u;
        return true;
      }
    }
    // augmenting path
    for (auto const [_, v] : g.edges_of(u)) {
      if (dfn[pb[v]] != idx && dfs(pb[v])) {
        pa[u] = v;
        pb[v] = u;
        return true;
      }
    }
    return false;
  }};

  while (true) {
    ++idx;
    int cnt{};
    for (int i{}; i != left_size; ++i) {
      if (pa[i] == -1 && dfs(i)) {
        ++cnt;
      }
    }
    if (cnt == 0) {
      break;
    }
    res += cnt;
  }
  return res;
}
struct tarjan_cuts {
  tarjan_cuts(graph const &g)
      : g(g), n(static_cast<int>(g.adjacent.size())), low(n), dfn(n)
  {
  }
  graph const g;
  int const n;
  int idx{};
  // You can check dfn[i] to identify if vertex i has been visited.
  std::vector<int> low, dfn;
  std::vector<int> cuts;
  void run(int u, bool isroot = true)
  {
    low[u] = dfn[u] = ++idx;
    u64 cnt{};
    for (auto const [_, v] : g.edges_of(u)) {
      if (!dfn[v]) {
        run(v, false);
        check_min(low[u], low[v]);
        cnt += dfn[u] <= low[v];
      }
      else {
        check_min(low[u], dfn[v]);
      }
    }
    if (cnt > isroot) {
      cuts.push_back(u);
    }
  }
};
struct tarjan_bridges {
  tarjan_bridges(graph const &g)
      : g(g), n(static_cast<int>(g.adjacent.size())), low(n), dfn(n)
  {
  }
  graph const g;
  int const n;
  int idx{};
  std::vector<int> low, dfn;
  std::vector<std::pair<int, int>> bridges;
  void run(int u, int p)
  {
    low[u] = dfn[u] = ++idx;
    for (auto const [_, v] : g.edges_of(u)) {
      if (!dfn[v]) {
        run(v, u);
        check_min(low[u], low[v]);
        if (low[v] > dfn[u]) {
          bridges.emplace_back(u, v);
        }
      }
      else if (v != p) {
        check_min(low[u], dfn[v]);
      }
    }
  }
};
} // namespace graph
namespace {
void solve_case()
{
  using namespace std;
  int n;
  cin >> n;
  auto g{graph::read_graph(n, n - 1, false, false, true)};
  vector<int> a(n);
  cin >> a;
  unordered_map<int, unordered_map<int, u64>> dist, size;
  vector<int> depth(n);
  u64 ans{};
  auto merge{[&ans](auto &d1, auto &s1, auto &d2, auto &s2, u64 d) {
    if (s1.size() < s2.size()) {
      swap(d1, d2);
      swap(s1, s2);
    }
    for (auto [c, _] : s2) {
      ans += d1[c] * s2[c] + d2[c] * s1[c] - 2 * d * s1[c] * s2[c];
    }
    for (auto [c, val] : d2) {
      d1[c] += val;
    }
    for (auto [c, val] : s2) {
      s1[c] += val;
    }
  }};
  auto dfs{[&](auto self, int u, int p) -> void {
    size[u][a[u]] = 1;
    dist[u][a[u]] = depth[u] = depth[p] + 1;
    for (auto [_, v] : g.edges_of(u)) {
      if (v != p) {
        self(self, v, u);
        merge(dist[u], size[u], dist[v], size[v], depth[u]);
      }
    }
  }};
  dfs(dfs, 0, 0);
  cout << ans;
}
} // namespace
