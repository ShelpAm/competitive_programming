/*Problem: K. 复合函数*/
/*Contest: JXNU Summer Train 4*/
/*Judge: Codeforces*/
/*URL: https://codeforces.com/gym/538008/problem/K*/
/*Start: Wed 24 Jul 2024 07:57:05 PM CST*/
/*Author: ShelpAm*/

#include <bits/stdc++.h>

#ifdef __cpp_lib_ranges
#include <ranges>
#endif

namespace {
[[maybe_unused]] constexpr std::int_fast64_t mod998244353{998'244'353LL};
[[maybe_unused]] constexpr std::int_fast64_t mod1e9p7{1'000'000'007LL};
template <typename T>
[[maybe_unused]] constexpr T inf{std::numeric_limits<T>::max() / 2};
[[maybe_unused]] constexpr double eps{1e-8};

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

constexpr auto operator>>(std::istream &istream, auto &&t) -> std::istream &
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
  [[nodiscard]] auto size(int x) -> int
  {
    return _size[find(x)];
  }

private:
  std::vector<int> _parent;
  std::vector<int> _size;
};
using Dsu = Disjoint_set_union;
void solve_case()
{
  int n;
  std::cin >> n;
  std::vector<int> f(n);
  std::cin >> f;
  std::vector<std::vector<int>> pa(n);
  for (int i{}; i != n; ++i) {
    pa[--f[i]].push_back(i);
  }

  std::unordered_map<int, std::unordered_map<i64, int>> pref;
  Dsu dsu(n);
  for (int i{}; i != n; ++i) {
    if (!dsu.unite(i, f[i])) {
      std::vector<int> path{i};
      while (f[path.back()] != i) {
        path.push_back(f[path.back()]);
      }
      std::function<void(int, int)> dfs{[&](int const u, int const dist) {
        ++pref[path.size()][dist];
        for (auto const v : pa[u]) {
          dfs(v, dist + 1);
        }
      }};
      pref[path.size()][0] += path.size();
      for (int i{}; i != path.size(); ++i) {
        for (auto const v : pa[path[i]]) {
          if (v != path[(i - 1 + path.size()) % path.size()]) {
            dfs(v, 1);
          }
        }
      }
    }
  }
  for (auto &[k, v] : pref) {
    int m{};
    for (auto const &[p, q] : v) {
      check_max(m, p);
    }
    for (int i{1}; i <= m; ++i) {
      v[i] += v[i - 1];
    }
  }

  int q;
  std::cin >> q;
  for (int i{}; i != q; ++i) {
    i64 a, b;
    std::cin >> a >> b;
    if (a == b) {
      std::cout << n << '\n';
      continue;
    }
    i64 ans{};
    for (auto const &[k, v] : pref) {
      if ((a - b) % k == 0) {
        ans += v.at(std::min({a, b, static_cast<i64>(v.size() - 1)}));
      }
    }
    std::cout << ans << '\n';
  }
}
} // namespace
