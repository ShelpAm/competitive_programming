/*Problem: 狼狼的备忘录*/
/*Contest: unknown_contest*/
/*Judge: NowCoder*/
/*URL: https://ac.nowcoder.com/acm/contest/87255/H*/
/*Start: Wed 24 Jul 2024 03:00:55 PM CST*/
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
void solve_case()
{
  int n;
  std::cin >> n;
  std::map<std::string, std::vector<std::string>> a;
  for (int i{}; i != n; ++i) {
    std::string s;
    int k;
    std::cin >> s >> k;
    for (int j{}; j != k; ++j) {
      std::string t;
      std::cin >> t;
      a[s].push_back(t);
    }
  }
  std::cout << a.size() << '\n';
  for (auto &[k, v] : a) {
    std::sort(v.begin(), v.end());
    std::vector<int> discarded(v.size());
    for (int i{}; i != v.size(); ++i) {
      for (int j{}; j != v.size(); ++j) {
        if (i != j) {
          if (v[i].size() < v[j].size()) {
            if (v[j].substr(v[j].size() - v[i].size()) == v[i]) {
              discarded[i] = 1;
            }
          }
          else if (v[i].size() > v[j].size()) {
            if (v[i].substr(v[i].size() - v[j].size()) == v[j]) {
              discarded[j] = 1;
            }
          }
          else if (v[i] == v[j]) {
            discarded[std::max(i, j)] = 1;
          }
        }
      }
    }
    for (auto const &e : v) {
      std::cerr << e << ' ';
    }
    std::cerr << '\n';
    debug("discarded", discarded);
    std::cout << k << ' '
              << v.size() - std::count(discarded.begin(), discarded.end(), 1)
              << ' ';
    for (int i{}; i != v.size(); ++i) {
      if (!discarded[i]) {
        std::cout << v[i] << ' ';
      }
    }
    std::cout << '\n';
  }
}
} // namespace
