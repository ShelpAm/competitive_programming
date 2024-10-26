/*Problem: G. Pumpkin Patch*/
/*Contest: JXNU_TRAIN_1*/
/*Judge: Codeforces*/
/*URL: https://codeforces.com/gym/552292/problem/G*/
/*Start: Tue 24 Sep 2024 03:44:19 PM CST*/
/*Author: ShelpAm*/

// #include <bits/stdc++.h>
#include <algorithm>
#include <bit>
#include <cassert>
#include <chrono>
#include <climits>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <ranges>
#include <set>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace {
[[maybe_unused]] constexpr std::uint_fast64_t mod998244353{998'244'353ULL};
[[maybe_unused]] constexpr std::uint_fast64_t mod1e9p7{1'000'000'007ULL};
[[maybe_unused]] constexpr double eps{1e-8};
template <typename T> constexpr T inf{std::numeric_limits<T>::max() / 2};

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
using i64 = std::int_fast64_t;
using u64 = std::uint_fast64_t;
void solve_case()
{
  int n, m;
  std::cin >> n >> m;
  std::vector<std::string> a(n);
  std::cin >> a;

  std::pair<int, int> s{-1, -1}, e{-1, -1};
  for (int i{}; i != n; ++i) {
    for (int j{}; j != m; ++j) {
      if (a[i][j] == 'S') {
        s = {i, j};
      }
      else if (a[i][j] == 'E') {
        e = {i, j};
      }
    }
  }
  //
  // if (s == std::make_pair(-1, -1) || e == std::make_pair(-1, -1)) {
  //   std::cout << "FUCK" << std::endl;
  // }

  std::vector<std::pair<int, int>> const dirs{
      std::make_pair(1, 0), {0, 1}, {-1, 0}, {0, -1}};
  std::vector<std::vector<std::vector<int>>> dist(
      n, std::vector<std::vector<int>>(m, std::vector<int>(9, inf<int>))); // in
  // i,j, left k corn.  min dist.

  std::queue<std::array<int, 4>> q;
  q.push({s.first, s.second, 0, 0});
  dist[s.first][s.second][0] = 0;
  // int ans{inf<int>};
  while (!q.empty()) {
    auto const [x, y, d, c]{q.front()};
    q.pop();

    for (auto [i, j] : dirs) {
      i += x, j += y;
      if (i < 0 || i >= n || j < 0 || j >= m || a[i][j] == 'P') {
        continue;
      }
      auto const dc{static_cast<int>(a[i][j] == 'C') -
                    static_cast<int>(a[i][j] == 'J')};
      if (c + dc >= 0 && chmin(dist[i][j][c + dc], d + 1)) {
        q.push({i, j, d + 1, c + dc});
      }
    }
  }

  auto ans{std::ranges::min(dist[e.first][e.second])};
  if (ans == inf<int>) {
    std::cout << "SPOOKED!\n";
  }
  else {
    std::cout << ans << '\n';
  }
}
} // namespace
