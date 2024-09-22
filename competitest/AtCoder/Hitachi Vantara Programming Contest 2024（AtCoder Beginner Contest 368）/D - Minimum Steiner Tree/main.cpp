/*Problem: D - Minimum Steiner Tree*/
/*Contest: Hitachi Vantara Programming Contest 2024（AtCoder Beginner Contest
 * 368）*/
/*Judge: AtCoder*/
/*URL: https://atcoder.jp/contests/abc368/tasks/abc368_d*/
/*Start: Sun 25 Aug 2024 04:54:06 PM CST*/
/*Author: ShelpAm*/

#include <bits/stdc++.h>

#ifdef __cpp_lib_ranges
#include <ranges>
#endif

namespace {
[[maybe_unused]] constexpr std::int_fast64_t mod998244353{998'244'353LL};
[[maybe_unused]] constexpr std::int_fast64_t mod1e9p7{1'000'000'007LL};
[[maybe_unused]] constexpr double eps{1e-8};
template <typename T>
[[maybe_unused]] constexpr T inf{std::numeric_limits<T>::max() / 2};

#ifdef __cpp_concepts
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

constexpr auto operator>>(auto &istream, auto &&t) -> std::istream &
{
  using T = std::remove_cvref_t<decltype(t)>;
  static_assert(!shelpam::concepts::tuple<T>, "tuple: not implemented yet.\n");
#ifdef __cpp_lib_ranges
  if constexpr (std::ranges::range<T>) {
    for (auto &ele : t) {
      istream >> ele;
    }
  }
#endif
  else if constexpr (shelpam::concepts::pair<T>) {
    istream >> t.first >> t.second;
  }
  else {
    istream >> t;
  }
  return istream;
}
#endif
#ifndef ONLINE_JUDGE
#include "/home/shelpam/Documents/projects/competitive-programming/libs/debug.h"
#else
#define debug(...)
#endif
template <typename T, typename U>
constexpr auto chmax(T &value, U const &other) noexcept -> bool
{
  if (value < other) {
    value = other;
    return true;
  }
  return false;
}
template <typename T, typename U>
constexpr auto chmin(T &value, U const &other) noexcept -> bool
{
  if (value > other) {
    value = other;
    return true;
  }
  return false;
}
template <typename C> constexpr auto sum_of(C const &coll) noexcept
{
  return std::accumulate(coll.begin(), coll.end(), std::int_fast64_t{});
}
constexpr auto pow(int a, std::int_fast64_t b,
                   std::uint_fast64_t p) noexcept = delete;
template <typename T>
constexpr auto pow(T a, std::int_fast64_t b, std::uint_fast64_t p) noexcept
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
template <typename F>
auto binary_search(F check, std::int_fast64_t ok, std::int_fast64_t ng,
                   bool check_ok = true) noexcept -> std::int_fast64_t
{
  if (check_ok) {
    assert(check(ok));
  }
  while (std::abs(ok - ng) > 1) {
    auto const x{(ok + ng) / 2};
    (check(x) ? ok : ng) = x;
  }
  return ok;
}
template <typename T> constexpr auto lsb(T i) noexcept -> T
{
  static_assert(std::is_signed_v<T>,
                "lsb is implemented based on signed integers.");
  return i & -i;
}
// i mustn't be 0
template <typename T>
constexpr auto count_leading_zeros(T const &i) noexcept -> int
{
  assert(i != 0);
  if constexpr (std::is_same_v<T, unsigned long long>) {
    return __builtin_clzll(i);
  }
  if constexpr (std::is_same_v<T, unsigned long>) {
    return __builtin_clzl(i);
  }
  if constexpr (std::is_same_v<T, unsigned int>) {
    return __builtin_clz(i);
  }
  /*static_assert(false, "Unsupported type");*/
  static_assert(!std::is_signed_v<T>,
                "msb is implemented based on unsigned integers");
  return -1; // Unreachable.
}
// i mustn't be 0
template <typename T> constexpr auto msb(T i) noexcept -> int
{
  return static_cast<int>(sizeof(T) * CHAR_BIT - 1 - count_leading_zeros(i));
}
/*[[maybe_unused]] auto gen_rand() noexcept*/
/*{*/
/*  static std::mt19937_64 rng(*/
/*      std::chrono::steady_clock::now().time_since_epoch().count());*/
/*  return rng();*/
/*}*/
void solve_case() noexcept;
} // namespace
auto main() -> int
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  constexpr auto my_precision{10};
  std::cout << std::fixed << std::setprecision(my_precision);
  int t{1};
  /*std::cin >> t;*/
  for (int i{}; i != t; ++i) {
    solve_case();
  }
  return 0;
}
namespace {
using i64 = std::int_fast64_t;
using u64 = std::uint_fast64_t;
namespace graph {
constexpr std::int_fast64_t infinity{
    std::numeric_limits<std::int_fast64_t>::max() / 2};
class Graph {
public:
  explicit Graph(std::size_t const max_num_of_vertices)
      : adjacent(max_num_of_vertices)
  {
  }

  void add_edge(std::size_t const u, std::size_t const v,
                std::int_fast64_t const w)
  {
    adjacent[u].emplace_back(w, v);
  }

  [[nodiscard]] auto edges_of(std::size_t const u) const
      -> std::vector<std::pair<std::int_fast64_t, int>> const &
  {
    return adjacent[u];
  }

  [[nodiscard]] auto size() const -> std::size_t
  {
    return adjacent.size();
  }

private:
  std::vector<std::vector<std::pair<std::int_fast64_t, int>>> adjacent;
};
auto read(int const num_of_vertices, int const num_of_edges,
          bool const directed, bool const contains_w,
          bool const read_from_1 = true) -> Graph
{
  Graph g(num_of_vertices);
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
auto to_edges(Graph const &g)
    -> std::vector<std::tuple<std::int_fast64_t, int, int>>
{
  std::vector<std::tuple<std::int_fast64_t, int, int>> edges;
  for (std::size_t u{}; u != g.size(); ++u) {
    for (auto const &[w, v] : g.edges_of(u)) {
      edges.emplace_back(w, u, v);
    }
  }
  return edges;
}
// Tested in https://www.luogu.com.cn/problem/P3366
/// @return:
///   -1 to denote that the graph is not connected.
///   weight of minimum spanning tree.
auto kruskal(Graph const &g) -> std::int_fast64_t
{
  class Disjoint_set_union {
  public:
    explicit Disjoint_set_union(int size) : _parent(size), _size(size, 1)
    {
      std::iota(_parent.begin(), _parent.end(), 0);
    }
    // with path compression
    auto find(int x) -> int
    {
      return _parent[x] == x ? x : _parent[x] = find(_parent[x]);
    }
    /// @return:
    /// false if there has been pair x,y in the set.
    /// true successfully united
    auto unite(int x, int y) -> bool
    {
      x = find(x), y = find(y);
      if (x == y) {
        return false;
      }
      if (_size[x] < _size[y]) {
        std::swap(x, y);
      }
      _parent[y] = x;
      _size[x] += _size[y];
      return true;
    }
    [[nodiscard]] auto united(int x, int y) -> bool
    {
      return find(x) == find(y);
    }
    [[nodiscard]] auto size(int x) -> std::size_t
    {
      return _size[find(x)];
    }

  private:
    std::vector<int> _parent;
    std::vector<std::size_t> _size;
  };
  auto edges{to_edges(g)};
  std::sort(edges.begin(), edges.end());
  Disjoint_set_union dsu(static_cast<int>(g.size()));
  std::int_fast64_t sum_weights{};
  for (auto const &[w, u, v] : edges) {
    if (dsu.unite(u, v)) {
      sum_weights += w;
    }
  }
  if (dsu.size(0) != g.size()) {
    return -1;
  }
  return sum_weights;
}
// Tested in https://www.luogu.com.cn/problem/P3366
auto prim(Graph const &g) -> std::int_fast64_t
{
  // `distance[i]` means the distance from connected block to unconnected
  // block (aka i), not from source to i.
  std::vector<std::int_fast64_t> distance(g.size(), infinity);

  constexpr auto defined_source{0};
  distance[defined_source] = 0;

  // `visited[u]` is true means u had been a start point, and it shouldn't be
  // start point once more.
  std::vector<int> visited(g.size());
  std::size_t num_visited{};

  std::priority_queue<std::pair<std::int_fast64_t, int>,
                      std::vector<std::pair<std::int_fast64_t, int>>,
                      std::greater<>>
      q;
  q.emplace(distance[defined_source], defined_source);

  std::int_fast64_t sum_weights{};
  while (!q.empty()) {
    auto const [w, u]{q.top()}; // Extract unvisited closest vertex to sources.
    q.pop();

    // If some vertex was set visited, then it has had been start point to its
    // neighbours, hence there is no need to begin edges with that.
    if (visited[u]) {
      continue;
    }
    visited[u] = 1;
    sum_weights += w;
    if (++num_visited == g.size()) {
      return sum_weights;
    }

    for (auto const &[w, v] : g.edges_of(u)) {
      if (chmin(distance[v], w)) {
        q.emplace(w, v);
      }
    }
  }

  // If all vertices were travelled through, the algorithm would have returned
  // in the loop above.
  return -1;
}
struct Bellman_ford_result {
  bool contains_negative_circle;
  // When `no_negative_circle` is true, this is invalid.
  std::vector<std::int_fast64_t> distance;
};
auto bellman_ford(Graph const &g, int const source,
                  std::vector<int> &visited) -> Bellman_ford_result
{
  int const n{static_cast<int>(g.size())};
  std::vector<std::int_fast64_t> dist(g.size(), infinity);
  std::vector<int> num_intermediates(g.size());
  // std::vector<int> vis(g.size());

  dist[source] = 0;
  visited[source] = 1;
  // Only those in `q` could lead to relaxation.
  std::deque<int> q{source};
  auto swap_smaller_to_front{[&](std::deque<int> &q) {
    if (dist[q.back()] < dist[q.front()]) {
      std::swap(q.back(), q.front());
    }
  }};
  while (!q.empty()) {
    auto const u{q.front()};
    q.pop_front();
    swap_smaller_to_front(q);
    visited[u] = 0;

    for (auto const [w, v] : g.edges_of(u)) {
      if (auto const alt{dist[u] + w}; chmin(dist[v], alt)) {
        num_intermediates[v] = num_intermediates[u] + 1;
        if (num_intermediates[v] >= n) {
          return {.contains_negative_circle = true, .distance = {}};
        }
        if (!visited[v]) {
          visited[v] = 1;
          q.push_back(v);
          swap_smaller_to_front(q);
        }
      }
    }
  }
  return {.contains_negative_circle = false, .distance = dist};
}
struct Dijkstra_result {
  std::vector<std::int_fast64_t> distance;
  std::vector<std::int_fast64_t> previous;
};
auto dijkstra(Graph const &graph,
              std::vector<int> const &sources) -> Dijkstra_result
{
  std::vector<std::int_fast64_t> distance(graph.size(), infinity);
  std::vector<std::int_fast64_t> previous(graph.size());

  // `visited[u]` is true means u has been a start point, and it shouldn't be
  // start point once more.
  std::vector<int> visited(graph.size());

  std::priority_queue<std::pair<std::int_fast64_t, int>,
                      std::vector<std::pair<std::int_fast64_t, int>>,
                      std::greater<>>
      q;

  for (auto const source : sources) {
    distance[source] = 0;
    q.emplace(distance[source], source);
  }

  while (!q.empty()) {          // The main loop
    auto const [_, u]{q.top()}; // Extract the closest vertex. (Get and remove
                                // the best vertex)
    q.pop();

    if (visited[u]) {
      continue;
    }
    visited[u] = 1;

    for (auto const &[w, v] : graph.edges_of(u)) {
      if (auto const alt{distance[u] + w}; chmin(distance[v], alt)) {
        previous[v] = u;
        q.emplace(alt, v);
      }
    }
  }

  return {.distance = distance, .previous = previous};
}
auto dijkstra(Graph const &graph, int const source) -> Dijkstra_result
{
  return dijkstra(graph, std::vector<int>{source});
}
using adjacent_matrix_t = std::vector<std::vector<std::int_fast64_t>>;
auto floyd(Graph const &g) -> adjacent_matrix_t
{
  auto const n = static_cast<int>(g.size());

  adjacent_matrix_t f(n, std::vector<std::int_fast64_t>(n, infinity));

  // Initializes data
  for (int u = 0; u != n; ++u) {
    f[u][u] = 0;
    for (auto const &[w, v] : g.edges_of(u)) {
      f[u][v] = w;
    }
  }

  for (int k = 0; k != n; ++k) {
    // In k-th round (At the end of the round), f[i][j] denotes the minimum
    // distance between i, j, concerning first k vertices.
    for (int i = 0; i != n; ++i) {
      for (int j = 0; j != n; ++j) {
        chmin(f[i][j], f[i][k] + f[k][j]);
      }
    }
  }

  return f;
}
struct Toposort_result {
  bool acyclic;
  std::vector<int> order;
};
auto toposort(Graph const &g, bool directed) -> Toposort_result
{
  assert(directed && "haven't implement undirected");
  int const n{static_cast<int>(g.size())};
  std::vector<int> in(n);
  for (std::size_t u{}; u != g.size(); ++u) {
    for (auto const [_, v] : g.edges_of(u)) {
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
  if (order.size() != g.size()) {
    return {.acyclic = false, .order = {}};
  }
  return {.acyclic = true, .order = order};
};
// The graph should only contains left-to-right edges, and should not
// convert/transform the vertices' ID. For example, if you want to make a edge
// from left vertex x to right vertex y, you should use
// `g.add_edge(x, y, 1);` rather than `g.add_edge(x, y + n, 1);`.
auto maximum_matching(Graph const &g, int const left_size,
                      int const right_size) -> int
{
  assert(left_size >= 0 && right_size >= 0);
  assert(g.size() == static_cast<std::size_t>(left_size));
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
struct Tarjan_cuts {
  Tarjan_cuts(Graph const &g) : g(g), n(g.size()), low(n), dfn(n) {}
  Graph g;
  std::size_t n;
  int idx{};
  // You can check dfn[i] to identify if vertex i has been visited.
  std::vector<int> low, dfn;
  std::vector<int> cuts;
  void run(int const u, bool const isroot = true)
  {
    low[u] = dfn[u] = ++idx;
    int cnt{};
    for (auto const [_, v] : g.edges_of(u)) {
      if (!dfn[v]) {
        run(v, false);
        chmin(low[u], low[v]);
        cnt += dfn[u] <= low[v];
      }
      else {
        chmin(low[u], dfn[v]);
      }
    }
    if (cnt > isroot) {
      cuts.push_back(u);
    }
  }
};
struct Tarjan_bridges {
  Tarjan_bridges(Graph g) : g(std::move(g)), n(g.size()), low(n), dfn(n) {}
  Graph g;
  std::size_t n;
  int idx{};
  std::vector<int> low, dfn;
  std::vector<std::pair<int, int>> bridges;
  void run(int const u, int const p)
  {
    low[u] = dfn[u] = ++idx;
    for (auto const [_, v] : g.edges_of(u)) {
      if (!dfn[v]) {
        run(v, u);
        chmin(low[u], low[v]);
        if (low[v] > dfn[u]) {
          bridges.emplace_back(u, v);
        }
      }
      else if (v != p) {
        chmin(low[u], dfn[v]);
      }
    }
  }
};

// Time complexity: linear, O(|g.E| + |g.V|)
struct Tarjan_scc {
public:
  Tarjan_scc(Graph g)
      : _g{std::move(g)}, _n(static_cast<int>(_g.size())), _index(_n),
        _lowlink(_n), _on_stack(_n)
  {
    for (int i{}; i != _n; ++i) {
      if (!_index[i]) {
        strong_connect(i);
      }
    }
  }

  std::vector<std::vector<int>> scc;

private:
  void strong_connect(int const u)
  {
    _lowlink[u] = _index[u] = ++_idx;
    _stack.push(u);
    _on_stack[u] = 1;

    // Consider successors of u
    for (auto const &[_, v] : _g.edges_of(u)) {
      if (!_index[v]) {
        // Successor w has not yet been visited; recurse on it
        strong_connect(v);
        chmin(_lowlink[u], _lowlink[v]);
      }
      else if (_on_stack[v]) {
        chmin(_lowlink[u], _index[v]);
      }
    }

    // If v is a root node, pop the stack and generate an SCC
    if (_lowlink[u] == _index[u]) {
      scc.emplace_back();
      int v;
      do {
        _on_stack[v = _stack.top()] = 0;
        _stack.pop();
        scc.back().push_back(v);
      } while (v != u);
    }
  }

  Graph _g;
  int _n;
  int _idx{};
  std::stack<int> _stack;
  std::vector<int> _index; // DFS order of each vertex
  std::vector<int> _lowlink;
  std::vector<int> _on_stack;
};
struct Contract_edges_result {
  Graph h;
  std::vector<std::size_t> scc_id;
};
auto contract_edges(Graph const &g) -> Contract_edges_result
{
  auto const scc{std::move(Tarjan_scc(g).scc)};

  std::vector<std::size_t> scc_id(g.size());
  Graph h(scc.size());
  for (std::size_t i{}; i != scc.size(); ++i) {
    for (auto const u : scc[i]) {
      scc_id[u] = i;
    }
  }
  for (std::size_t i{}; i != scc.size(); ++i) {
    for (auto const u : scc[i]) {
      for (auto const &[w, v] : g.edges_of(u)) {
        if (i != scc_id[v]) {
          h.add_edge(i, scc_id[v], w);
        }
      }
    }
  }
  return Contract_edges_result{.h = h, .scc_id = scc_id};
}
} // namespace graph
void solve_case() noexcept
{
  int n, k;
  std::cin >> n >> k;
  auto const g{graph::read(n, n - 1, false, false)};
  std::vector<int> v(k);
  std::vector<int> set(n);
  for (int i{}; i != k; ++i) {
    std::cin >> v[i];
    set[--v[i]] = 1;
  }
  int ans{n};
  auto dfs{[&](auto self, int const u, int const p) -> bool {
    bool found{};
    for (auto const &[_, v] : g.edges_of(u)) {
      if (v == p) {
        continue;
      }
      if (self(self, v, u)) {
        found = true;
      }
      else {
        --ans;
      }
    }
    return found || set[u];
  }};
  dfs(dfs, v[0], v[0]);
  std::cout << ans;
}
} // namespace
