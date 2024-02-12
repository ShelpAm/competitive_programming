#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <deque>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#ifdef __cpp_concepts
#include <ranges>
#endif

// configs
using ::std::cin;
using ::std::cout;
using ::std::endl;
using ::std::size_t;
using ::std::string;
using ::std::string_view;
using ::std::operator""sv;
using ::std::greater;
using ::std::less;
using ::std::map;
using ::std::numeric_limits;
using ::std::pair;
using ::std::priority_queue;
using ::std::queue;
using ::std::set;
using ::std::stack;
using ::std::unordered_map;
using ::std::unordered_set;
#ifdef __cpp_lib_ranges
using ::std::ranges::max;
using ::std::ranges::min;
using ::std::ranges::sort;
using ::std::ranges::swap;
using ::std::ranges::views::drop;
using ::std::ranges::views::iota;
using ::std::ranges::views::reverse;
using ::std::ranges::views::split;
using ::std::ranges::views::take;
#else
// TODO: Defines my own sort, etc.
#endif
template<typename T>
[[maybe_unused]] constexpr T mod{static_cast<T>(998244353ULL)};
template<typename T>
[[maybe_unused]] constexpr T inf{numeric_limits<T>::max() >> 16};
namespace impl {
template<typename value_type> using vec2_placeholder
    = std::vector<std::vector<value_type>>;
template<typename value_type, size_t size> using arr1
    = ::std::array<value_type, size>;
template<size_t i, size_t j, typename value_type> using arr2
    = std::array<std::array<value_type, j>, i>;
template<typename value_type> using vec1 = ::std::vector<value_type>;
template<typename value_type> class vec2 : public vec2_placeholder<value_type> {
public:
  constexpr vec2(size_t const i, size_t const j, value_type const& value = {})
      : vec2_placeholder<value_type>(i, std::vector<value_type>(j, value))
  {}
};

#ifdef __cpp_concepts
template<typename T> concept pair = requires(T t) {
  t.first;
  t.second;
};

template<typename> struct is_tuple_t : std::false_type {};
template<typename... T> struct is_tuple_t<std::tuple<T...>> : std::true_type {};
template<typename... T> concept tuple = is_tuple_t<T...>::value;

template<typename T> concept c_str
    = std::same_as<char const*, std::remove_cvref_t<T>>;
template<typename T> concept string
    = std::same_as<string, std::remove_cvref_t<T>>;
template<typename T> concept string_view
    = std::same_as<string_view, std::remove_cvref_t<T>>;
template<typename T> concept string_like
    = string<T> || string_view<T> || c_str<T>;
#endif
} // namespace impl
using i64 = long long;
// using i64 = ::std::ptrdiff_t;
// using u64 = size_t;
using vi = std::vector<i64>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;
using vvvvi = std::vector<vvvi>;
using vb = std::vector<bool>;
using vvb = std::vector<vb>;
using pii = pair<i64, i64>;
using puz = pair<size_t, size_t>;
using pll = pair<long long, long long>;
template<size_t i, size_t j> using arr2uz = impl::arr2<i, j, size_t>;
template<size_t i, size_t j> using arr2ll = impl::arr2<i, j, long long>;
template<size_t i, size_t j> using arr2b = impl::arr2<i, j, bool>;
using vec1uz = impl::vec1<size_t>;
using vec1ll = impl::vec1<long long>;
using vec1b = impl::vec1<bool>;
using vec2uz = impl::vec2<size_t>;
using vec2ll = impl::vec2<long long>;
using vec2b = impl::vec2<bool>;
namespace impl {
class io_accelerator {
public:
  io_accelerator()
  {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    // The following line needn't to be executed because the above line actually
    // had done this. std::cout.tie(nullptr);
  }
  io_accelerator(const io_accelerator&) = delete;
  io_accelerator(io_accelerator&&) = delete;
  io_accelerator& operator=(const io_accelerator&) = delete;
  io_accelerator& operator=(io_accelerator&&) = delete;
  ~io_accelerator()
  {
    std::ios::sync_with_stdio(true);
    std::cin.tie(&std::cout);
  }
};
} // namespace impl
[[maybe_unused]] static inline constexpr bool check_max(auto&& value,
                                                        auto&& other)
{
  if (value < other) {
    value = other;
    return true;
  }
  return false;
}
[[maybe_unused]] static inline constexpr bool check_min(auto&& value,
                                                        auto&& other)
{
  if (value > other) {
    value = other;
    return true;
  }
  return false;
}
struct prime_fileter_result {
  // prime_fileter_result(size_t const size): not_prime(size) {}
  vi primes;
  vb not_prime;
};
// upper_bound The maximum number you would like to query.
auto prime_filter(size_t const upper_bound)
{
  vi primes(upper_bound + 1);
  vb not_prime(upper_bound + 1);
  for (size_t i{2}; i != upper_bound + 1; ++i) {
    if (!not_prime[i]) {
      primes.emplace_back(i);
    }
    for (auto const p: primes) {
      if (i * p > upper_bound) {
        break;
      }
      not_prime[i * p] = true;
      if (i % p == 0) {
        break;
      }
    }
  }
  return prime_fileter_result{primes, not_prime};
}
// namespace graph {
auto read_graph(size_t const num_of_vertices, size_t const num_of_edges,
                bool const bidirectional, bool const contains_w,
                bool const read_from_1 = true)
{
  impl::vec2<pii> adj(num_of_vertices, 0);
  for (size_t i{}; i != num_of_edges; ++i) {
    size_t u, v, w;
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
    adj[u].emplace_back(w, v);
    if (bidirectional) {
      adj[v].emplace_back(w, u);
    }
  }
  return adj;
}
struct dijkstra_result {
  // dijkstra_result(size_t const size): dis(size), prev(size){};
  vi dis;
  vi prev;
};
auto dijkstra(impl::vec2<pii> const& adjacent, size_t const source)
{
  vi dis(adjacent.size(), inf<i64>);
  vi prev(adjacent.size());
  dis[source] = 0;

  priority_queue<pii, impl::vec1<pii>, greater<>> q;
  q.emplace(dis[source], source);

  while (!q.empty()) { // The main loop
    auto const [_, u]{
        q.top()}; // Extract closest vertex. (Get and remove best vertex)
    q.pop();

    for (auto const& [d, v]: adjacent[u]) {
      if (auto const alt{dis[u] + d}; alt < dis[v]) {
        dis[v] = alt;
        prev[v] = u;
        q.emplace(alt, v);
      }
    }
  }

  return dijkstra_result{dis, prev};
}
auto floyd(impl::vec2<pii> const& adj)
{
  auto const n{static_cast<i64>(adj.size())};

  vvi f(adj.size(), vi(adj.size(), inf<i64>));
  // Initialize data
  for (i64 u{}; u != n; ++u) {
    f[u][u] = 0;
    for (auto const& [w, v]: adj[u]) {
      f[u][v] = w;
    }
  }

  for (i64 k{}; k != n; ++k) {
    // In k-th round (At the end of the round), f[i][j] denotes the minimum
    // distance between i, j, concerning first k vertices.
    for (i64 i{}; i != n; ++i) {
      for (i64 j{}; j != n; ++j) {
        check_min(f[i][j], f[i][k] + f[k][j]);
      }
    }
  }

  return f;
}
// } // namespace graph
class disjoint_set_union {
public:
  disjoint_set_union(size_t size): parent_(size), size_(size, 1)
  {
    std::iota(parent_.begin(), parent_.end(), 0);
  }
  // with path compression
  size_t find(size_t const x)
  {
    return parent_[x] == x ? x : parent_[x] = find(parent_[x]);
  }
  /// return:
  /// false - if there has been pair x,y in the set
  /// true  - successfully united
  bool unite(size_t x, size_t y)
  {
    x = find(x);
    y = find(y);
    if (x == y) {
      return false;
    }
    if (size_[x] < size_[y]) {
      std::ranges::swap(x, y);
    }
    parent_[y] = x;
    size_[x] += size_[y];
    return true;
  }
  bool united(size_t const x, size_t const y) { return find(x) == find(y); }
private:
  std::vector<size_t> parent_;
  std::vector<size_t> size_;
};
using dsu = disjoint_set_union;
auto lsb(i64 const i)
{
  return i & (-i);
}
class fenwick_tree {
public:
  fenwick_tree(size_t const size): tree_(size) {}
  // The input array should start from the index 1.
  fenwick_tree(vi coll): tree_{std::move(coll)}
  {
    for (size_t i{1}; i != tree_.size(); ++i) {
      auto parent_index{i + lsb(static_cast<i64>(i))};
      if (parent_index < tree_.size()) {
        tree_[parent_index] += tree_[i];
      }
    }
  }
  [[nodiscard]] i64 query(i64 index) const
  {
    i64 sum{};
    while (index > 0) {
      sum += tree_[index];
      index -= lsb(index);
    }
    return sum;
  }
  void update(size_t index, i64 const value)
  {
    while (index < tree_.size()) {
      tree_[index] += value;
      index += lsb(static_cast<i64>(index));
    }
  }
private:
  vi tree_;
};
class segment_tree {};
static inline constexpr auto&& operator>>(auto&& is, auto&& t)
{
  using T = std::remove_cvref_t<decltype(t)>;
#ifdef __cpp_lib_ranges
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      is >> ele;
    }
    return is;
  }
#endif
#ifdef __cpp_concepts
  if constexpr (impl::pair<decltype(t)>) {
    return is >> t.first >> t.second;
  }
  else if constexpr (impl::tuple<T>) {
    std::cout << "[operator>>] TODO: This is a tuple whose output method "
                 "hasn't been implemented.\n";
  }
#endif
  return is >> t;
}
static inline constexpr void print(auto const& t)
{
  using T = std::remove_cvref_t<decltype(t)>;
  if constexpr (impl::string_like<T>) {
    cout << t;
  }
  else if constexpr (std::is_convertible_v<T, char const*>) {
    cout << static_cast<char const*>(t);
  }
#ifdef __cpp_lib_ranges
  else if constexpr (std::ranges::range<T>) {
    for (auto&& ele: t) {
      print(ele);
    }
    std::cout << endl;
  }
#endif
#ifdef __cpp_concepts
  else if constexpr (impl::pair<T>) {
    std::cout << t.first << ": " << t.second << ", ";
  }
  else if constexpr (impl::tuple<T>) {
    std::cout << "[print] TODO: This is a tuple whose output method hasn't "
                 "been implemented.\n";
  }
#endif
  else {
    std::cout << t << ' ';
  }
}
static inline constexpr void debug([[maybe_unused]] std::string_view s,
                                   [[maybe_unused]] auto&& t)
{
#ifdef DEBUG
  std::cout << "[debug] " << s << ":\n";
  print(t);
  std::cout << endl;
#endif
}
static inline auto solve_case()
{
  using edge = std::tuple<i64, i64, i64>;

  i64 n, m;
  cin >> n >> m;
  impl::vec1<edge> edges(m);
  vvi adj(n);
  for (auto& [w, u, v]: edges) {
    cin >> u >> v >> w;
    --u, --v;
  }
  sort(edges, greater<>());

  dsu d(n);
  // The problem says there must be at least one simple cycle.
  edge ans_edge{-1, -1, -1};
  for (auto const& [w, u, v]: edges) {
    if (d.united(u, v)) {
      ans_edge = {w, u, v};
    }
    else {
      d.unite(u, v);
      adj[u].emplace_back(v);
      adj[v].emplace_back(u);
    }
  }

  auto const& [w, u, v]{ans_edge};
  vi path{u}, ans;
  auto dfs{[&](auto self, i64 cur, i64 prev) {
    if (cur == v) {
      ans = path;
      return;
    }

    for (auto const next: adj[cur]) {
      if (next != prev) {
        path.emplace_back(next);
        self(self, next, cur);
        path.pop_back();
      }
    }
  }};
  dfs(dfs, u, v);
  cout << w << ' ' << ans.size() << '\n';
  for (auto const i: ans) {
    cout << i + 1 << ' ';
  }
  cout << '\n';
}
static inline constexpr void solve_all_cases(auto&& solve_case_f)
{
  size_t t{1};
  std::cin >> t;
  for (size_t i{}; i != t; ++i) {
    if constexpr (std::is_void_v<decltype(solve_case_f())>) {
      solve_case_f();
    }
    else {
      print(solve_case_f());
      cout << endl;
    }
  }
}
int main()
{
  impl::io_accelerator accelerator;
  solve_all_cases(solve_case);
  return 0;
}
