#pragma once

#include "../templates/main.cpp"
#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <vector>

namespace shelpam::graph {

using Node_type = int;

constexpr auto infinity{std::numeric_limits<std::int_fast64_t>::max() / 4};
class Graph {
  public:
    static auto read(int num_of_vertices, int num_of_edges, bool directed,
                     bool contains_w, bool read_from_1 = true) -> Graph
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

    explicit Graph(std::size_t max_num_of_vertices)
        : adjacent(max_num_of_vertices)
    {
    }

    void add_edge(std::size_t u, std::size_t v, std::int_fast64_t w)
    {
        adjacent[u].emplace_back(w, v);
    }

    [[nodiscard]] auto edges_of(std::size_t u) const
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
    std::deque<bool> visited(g.size());
    std::size_t num_visited{};

    std::priority_queue<std::pair<std::int_fast64_t, int>,
                        std::vector<std::pair<std::int_fast64_t, int>>,
                        std::greater<>>
        q;
    q.emplace(distance[defined_source], defined_source);

    std::int_fast64_t sum_weights{};
    while (!q.empty()) {
        auto const [w,
                    u]{q.top()}; // Extract unvisited closest vertex to sources.
        q.pop();

        // If some vertex was set visited, then it has had been start point to
        // its neighbours, hence there is no need to begin edges with that.
        if (visited[u]) {
            continue;
        }
        visited[u] = true;
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
auto bellman_ford(Graph const &g, int source, std::deque<bool> &visited)
    -> Bellman_ford_result
{
    std::vector<std::int_fast64_t> dist(g.size(), infinity);
    std::vector<std::size_t> num_intermediates(g.size());
    // std::vector<int> vis(g.size());

    dist[source] = 0;
    visited[source] = true;
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
        visited[u] = false;

        for (auto const [w, v] : g.edges_of(u)) {
            if (auto const alt{dist[u] + w}; chmin(dist[v], alt)) {
                num_intermediates[v] = num_intermediates[u] + 1;
                if (num_intermediates[v] >= g.size()) {
                    return {.contains_negative_circle = true, .distance = {}};
                }
                if (!visited[v]) {
                    visited[v] = true;
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
    std::vector<int> previous;
};
auto dijkstra(Graph const &g, std::vector<int> const &sources)
    -> Dijkstra_result
{
    std::vector<std::int_fast64_t> dist(g.size(), infinity);
    std::vector<int> prev(g.size(), -1);

    // Nodes not in q had got the shortest distance from source(s)
    auto by_dist{[&](int l, int r) {
        return std::tie(dist[l], l) < std::tie(dist[r], r);
    }};
    std::set<int, decltype(by_dist)> q{by_dist};
    for (auto const source : sources) {
        dist[source] = 0;
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

using adjacent_matrix_t = std::vector<std::vector<std::int_fast64_t>>;
auto floyd(Graph const &g) -> adjacent_matrix_t
{
    auto const n = static_cast<int>(g.size());

    adjacent_matrix_t f(n, std::vector<std::int_fast64_t>(n, infinity));

    // Initializes data
    for (int u = 0; u != n; ++u) {
        f[u][u] = 0;
        for (auto const &[w, v] : g.edges_of(u)) {
            chmin(f[u][v],
                  w); // Do not directly use `f[u][v] = w;` to fight against
                      // multiple edges connecting the same vertices.
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
auto maximum_matching(Graph const &g, int left_size, int right_size) -> int
{
    assert(left_size >= 0 && right_size >= 0);
    assert(g.size() == static_cast<std::size_t>(left_size));
    int num_of_matches{};

    int idx{}; // dfs order, identifying if a vertex was visited in current
               // round
    std::vector<int> dfn(left_size);

    // Matches from a and matches from b
    std::vector<int> pa(left_size, -1);
    std::vector<int> pb(right_size, -1);

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
        num_of_matches += cnt;
    }
    return num_of_matches;
}
struct Tarjan_cuts {
    Tarjan_cuts(Graph const &g) : g(g), n(g.size()), low(n), dfn(n) {}
    Graph g;
    std::size_t n;
    int idx{};
    // You can check dfn[i] to identify if vertex i has been visited.
    std::vector<int> low, dfn;
    std::vector<int> cuts;
    void run(int u, bool isroot = true)
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
    void run(int u, int p)
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
    void strong_connect(int u)
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

} // namespace shelpam::graph
