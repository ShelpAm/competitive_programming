/*Problem: C1. Adjust The Presentation (Easy Version)*/
/*Contest: Codeforces Round 977 (Div. 2, based on COMPFEST 16 - Final Round)*/
/*Judge: Codeforces*/
/*URL: https://codeforces.com/contest/2021/problem/C1*/
/*Start: Sun 13 Oct 2024 10:27:09 AM CST*/
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
  int n, m, q;
  std::cin >> n >> m >> q;
  std::vector<int> a(n);
  std::cin >> a;
  std::vector<int> b(m);
  std::cin >> b;

  // Solution 1
  // std::set<int> s;
  // int i{};
  // bool ok{true};
  // for (auto const e : b) {
  //   if (s.contains(e)) {
  //   }
  //   else if (i != n && a[i] == e) {
  //     s.insert(a[i++]);
  //   }
  //   else {
  //     ok = false;
  //   }
  // }
  // std::cout << (ok ? "YA\n" : "TIDAK\n");

  // Solution 2
  std::vector<int> c;
  std::deque<bool> presented(n + 1);
  for (auto const e : b) {
    if (!presented[e]) {
      c.push_back(e);
      presented[e] = true;
    }
  }
  auto const size{std::min(c.size(), a.size())};
  c.resize(size);
  a.resize(size);
  std::cout << (std::ranges::equal(c, a) ? "YA\n" : "TIDAK\n");

  // for (int i{}; i != q; ++i) {
  //   int s, t;
  //   std::cin >> s >> t;
  //   --s;
  // }
}
} // namespace