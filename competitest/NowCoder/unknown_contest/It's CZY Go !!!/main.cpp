/*Problem: It's CZY Go !!!*/
/*Contest: unknown_contest*/
/*Judge: NowCoder*/
/*URL: https://ac.nowcoder.com/acm/contest/94329/J*/
/*Start: Sat 26 Oct 2024 03:30:47 PM CST*/
/*Author: ShelpAm*/

// #include <bits/stdc++.h>
#include <algorithm>
#include <bit>
#include <bitset>
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
#include <numbers>
#include <numeric>
#include <queue>
#include <random>
#include <ranges>
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace {
[[maybe_unused]] constexpr std::uint_fast64_t mod998244353{998'244'353ULL};
[[maybe_unused]] constexpr std::uint_fast64_t mod1e9p7{1'000'000'007ULL};
[[maybe_unused]] constexpr double eps{1e-8};
template <typename T> constexpr T inf{std::numeric_limits<T>::max() / 4};
template <typename T> constexpr T max{std::numeric_limits<T>::max()};

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
  std::cin >> t;
  for (int i{}; i != t; ++i) {
    try {
      std::cerr << "Test case " << i << '\n';
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
  i64 q;
  std::cin >> n >> m >> q;
  std::vector<std::vector<int>> a(n);
  std::vector<std::tuple<int, int, int>> instructions;
  for (int i{}; i != m; ++i) {
    std::string s;
    std::cin >> s;
    if (s[0] == 'v') {
      auto const arrow{s.find("<-")};
      auto const v{std::stoi(s.substr(3, arrow - 3))};
      auto const que{std::stoi(s.substr(arrow + 6))};
      instructions.push_back({0, v - 1, que - 1});
    }
    else {
      auto const arrow{s.find("<-")};
      auto const que{std::stoi(s.substr(4, arrow - 4))};
      auto const literal{std::stoi(s.substr(arrow + 2))};
      instructions.push_back({1, que - 1, literal});
    }
  }

  { // Determines if panic.
    std::vector<int> que_size(n);
    for (auto const &[op, x, y] : instructions) {
      if (op == 0) {
        if (--que_size[y] < 0) {
          std::cout << "panic\n";
          return;
        }
      }
      else {
        ++que_size[x];
      }
    }
  }

  std::vector<std::vector<int>> pushed_to(n);
  std::vector<int> pulled_from(n);
  for (auto const &[op, x, y] : instructions) {
    if (op == 1) {
      pushed_to[x].push_back(y);
    }
    else {
      ++pulled_from[y];
    }
  }

  // Of some variable
  std::vector<int> last_pos(n, -1);
  std::vector<int> last_que(n);
  // Fethces
  std::vector<int> before(n);
  // Current fetches of a queue.
  std::vector<int> cur_fetches(n);
  for (int idx{}; auto const &[op, x, y] : instructions) {
    if (op == 0) { // x: variable, y: queue.
      last_pos[x] = idx;
      last_que[x] = y;
      before[x] = cur_fetches[y];

      ++cur_fetches[y];
    }
    ++idx;
  }

  for (int i{}; i != n; ++i) {
    if (last_pos[i] == -1) {
      std::cout << 0 << ' ';
    }
    else {
      auto const index{((q - 1) * pulled_from[last_que[i]] + before[i]) %
                       pushed_to[last_que[i]].size()};
      std::cout << pushed_to[last_que[i]][index] << ' ';
    }
  }
  std::cout << '\n';
}
} // namespace
