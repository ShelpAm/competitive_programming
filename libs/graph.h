#pragma once
#include "libs/generics.h"

struct graph {
 public:
  graph(size_t max_num_of_vertices): adjacent(max_num_of_vertices) {}
  void add_edge(size_t u, u64 v, u64 w) { adjacent[u].emplace_back(w, v); }
  [[nodiscard]] std::vector<puu> const& edges_of(size_t u) const
  {
    return adjacent[u];
  }
  std::vector<std::vector<puu>> adjacent;
};
[[maybe_unused]] graph read_graph(size_t const num_of_vertices,
                                  size_t const num_of_edges,
                                  bool const bidirectional,
                                  bool const contains_w, bool const read_from_1)
{
  graph g(num_of_vertices);
  for (size_t i = 0; i != num_of_edges; ++i) {
    u64 u, v, w;
    cin >> u >> v;
    if (contains_w) {
      cin >> w;
    }
    else {
      w = 1;
    }
    if (read_from_1) {
      --u, --v;
    }
    g.add_edge(u, v, w);
    if (bidirectional) {
      g.add_edge(v, u, w);
    }
  }
  return g;
}
struct dijkstra_result {
  std::vector<u64> distance;
  std::vector<u64> previous;
};
[[maybe_unused]] dijkstra_result dijkstra(graph const& graph, u64 const source)
{
  std::vector<u64> distance(graph.adjacent.size(), inf<u64>);
  std::vector<u64> previous(graph.adjacent.size());
  distance[source] = 0;

  vb visited(graph.adjacent
                 .size()); // `visited[u]` is true means u has been a start
                           // point, and it shouldn't be start point once more.

  priority_queue<puu, std::vector<puu>, greater<>> q;
  q.emplace(distance[source], source);

  while (!q.empty()) { // The main loop
    auto const [_, u]{q.top()}; // Extract the closest vertex. (Get and remove
                                // the best vertex)
    q.pop();

    if (visited[u]) {
      continue;
    }
    visited[u] = true;

    for (auto const& [w, v]: graph.edges_of(u)) {
      if (auto const alt{distance[u] + w}; alt < distance[v]) {
        distance[v] = alt;
        previous[v] = u;
        q.emplace(alt, v);
      }
    }
  }

  return {distance, previous};
}
[[maybe_unused]] vvi floyd(std::vector<std::vector<pii>> const& adjacent)
{
  auto const n = adjacent.size();

  vvi f(n, vi(n, inf<i64>));
  // Initialize data
  for (u64 u = 0; u != n; ++u) {
    f[u][u] = 0;
    for (auto const& [w, v]: adjacent[u]) {
      f[u][v] = w;
    }
  }

  for (size_t k = 0; k != n; ++k) {
    // In k-th round (At the end of the round), f[i][j] denotes the minimum
    // distance between i, j, concerning first k vertices.
    for (size_t i = 0; i != n; ++i) {
      for (size_t j = 0; j != n; ++j) {
        check_min(f[i][j], f[i][k] + f[k][j]);
      }
    }
  }

  return f;
}
