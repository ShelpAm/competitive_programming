#pragma once
#include "../templates/main.cpp"

namespace graph {
constexpr std::int_fast64_t infinity{
    std::numeric_limits<std::int_fast64_t>::max() / 2};
struct Graph {
public:
  Graph(std::size_t max_num_of_vertices) : adjacent(max_num_of_vertices) {}
  void add_edge(int u, int v, std::int_fast64_t w)
  {
    adjacent[u].emplace_back(w, v);
  }
  [[nodiscard]] auto edges_of(int u) const
      -> std::vector<std::pair<std::int_fast64_t, int>> const &
  {
    return adjacent[u];
  }
  std::vector<std::vector<std::pair<std::int_fast64_t, int>>> adjacent;
};
auto read_graph(int const num_of_vertices, int const num_of_edges,
                bool const directed, bool const contains_w,
                bool const read_from_1) -> Graph
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
  for (int u{}; u != g.adjacent.size(); ++u) {
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
    [[nodiscard]] auto size(int x) -> int { return _size[find(x)]; }

  private:
    std::vector<int> _parent;
    std::vector<int> _size;
  };
  auto edges{to_edges(g)};
  std::ranges::sort(edges);
  Disjoint_set_union dsu(static_cast<int>(g.adjacent.size()));
  std::int_fast64_t weight{};
  for (auto const &[w, u, v] : edges) {
    if (dsu.unite(u, v)) {
      weight += w;
    }
  }
  if (dsu.size(0) != g.adjacent.size()) {
    return -1;
  }
  return weight;
}
// Tested in https://www.luogu.com.cn/problem/P3366
auto prim(Graph const &g) -> std::int_fast64_t
{
  // `distance[i]` means the distance from connected block to unconnected
  // block (aka i), not from source to i.
  std::vector<std::int_fast64_t> distance(g.adjacent.size(), infinity);

  constexpr auto defined_source{0};
  distance[defined_source] = 0;

  // `visited[u]` is true means u has been a start point, and it shouldn't be
  // start point once more.
  std::vector<int> visited(g.adjacent.size());
  std::size_t num_visited{};

  std::priority_queue<std::pair<std::int_fast64_t, int>,
                      std::vector<std::pair<std::int_fast64_t, int>>,
                      std::greater<>>
      q;
  q.emplace(distance[defined_source], defined_source);

  std::int_fast64_t weight{};
  while (!q.empty()) {          // The main loop
    auto const [w, u]{q.top()}; // Extract the closest vertex. (Get and remove
                                // the best vertex)
    q.pop();

    if (visited[u]) {
      continue;
    }
    visited[u] = true;
    weight += w;
    if (++num_visited == g.adjacent.size()) {
      return weight;
    }

    for (auto const &[w, v] : g.edges_of(u)) {
      if (check_min(distance[v], w)) {
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
  std::vector<std::int_fast64_t>
      distance; // When `no_negative_circle` is false, this is usable.
};
auto bellman_ford(Graph const &g, int const source,
                  std::vector<int> &visited) -> Bellman_ford_result
{
  int const n{static_cast<int>(g.adjacent.size())};
  std::vector<std::int_fast64_t> dist(g.adjacent.size(), infinity);
  std::vector<int> num_intermediates(g.adjacent.size());
  // std::vector<int> vis(g.adjacent.size());

  dist[source] = 0;
  visited[source] = true;
  // Only those in `q` could lead to relaxation.
  std::deque<int> q{source};
  auto swap_smaller_to_front{[](std::deque<int> &q) {
    if (q.back() < q.front()) {
      std::swap(q.back(), q.front());
    }
  }};
  while (!q.empty()) {
    auto const u{q.front()};
    q.pop_front();
    swap_smaller_to_front(q);
    visited[u] = false;

    for (auto const [w, v] : g.edges_of(u)) {
      if (auto const alt{dist[u] + w}; check_min(dist[v], alt)) {
        num_intermediates[v] = num_intermediates[u] + 1;
        if (num_intermediates[v] >= n) {
          return {true, {}};
        }
        if (!visited[v]) {
          visited[v] = true;
          q.push_back(v);
          swap_smaller_to_front(q);
        }
      }
    }
  }
  return {false, dist};
}
struct Dijkstra_result {
  std::vector<std::int_fast64_t> distance;
  std::vector<std::int_fast64_t> previous;
};
auto dijkstra(Graph const &graph, int const source) -> Dijkstra_result
{
  std::vector<std::int_fast64_t> distance(graph.adjacent.size(), infinity);
  std::vector<std::int_fast64_t> previous(graph.adjacent.size());
  distance[source] = 0;

  // `visited[u]` is true means u has been a start point, and it shouldn't be
  // start point once more.
  std::vector<int> visited(graph.adjacent.size());

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
      if (auto const alt{distance[u] + w}; check_min(distance[v], alt)) {
        previous[v] = u;
        q.emplace(alt, v);
      }
    }
  }

  return {distance, previous};
}
using adjacent_matrix_t = std::vector<std::vector<std::int_fast64_t>>;
auto floyd(Graph const &g) -> adjacent_matrix_t
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
struct Toposort_result {
  bool acyclic;
  std::vector<int> order;
};
auto toposort(Graph const &g, bool directed) -> Toposort_result
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
auto maximum_matching(Graph const &g, int left_size, int right_size) -> int
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
struct Tarjan_cuts {
  Tarjan_cuts(Graph const &g) : g(g), n(g.adjacent.size()), low(n), dfn(n) {}
  Graph g;
  int n;
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
struct Tarjan_bridges {
  Tarjan_bridges(Graph const &g) : g(g), n(g.adjacent.size()), low(n), dfn(n) {}
  Graph g;
  int n;
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
