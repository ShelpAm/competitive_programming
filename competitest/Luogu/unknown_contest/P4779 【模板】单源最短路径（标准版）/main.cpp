#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>
#include <set>
#include <vector>

namespace {
void solve_case();
} // namespace
auto main() -> int
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  constexpr auto my_precision{10};
  std::cout << std::fixed << std::setprecision(my_precision);
  int t{1};
  // std::cin >> t;
  for (int i{}; i != t; ++i) {
    try {
      solve_case();
    }
    catch (std::exception &e) {
      std::cerr << "Exception: " << e.what() << '\n';
    }
  }
  return 0;
}
namespace {
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
    int u;
    int v;
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

struct Dijkstra_result {
  std::vector<std::int_fast64_t> distance;
  std::vector<int> previous;
};
auto dijkstra(Graph const &g,
              std::vector<int> const &sources) -> Dijkstra_result
{
  std::vector<std::int_fast64_t> dist(g.size(), infinity);
  std::vector<int> prev(g.size(), -1);

  // Nodes not in q had got the shortest distance from source(s)
  auto by_dist{[&dist](int l, int r) {
    if (dist[l] != dist[r]) {
      return dist[l] < dist[r];
    }
    return l < r;
  }};
  std::set<int, decltype(by_dist)> q{by_dist};
  for (auto const source : sources) {
    dist[source] = 0;
    q.insert(source);
  }

  while (!q.empty()) { // The main loop
    // Extract the closest vertex. (Get and remove the best vertex)
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

} // namespace graph
void solve_case()
{
  int n, m, s;
  std::cin >> n >> m >> s;
  auto d{graph::dijkstra(graph::read(n, m, true, true), --s)};
  for (auto e : d.distance) {
    std::cout << e << ' ';
  }
}
} // namespace
