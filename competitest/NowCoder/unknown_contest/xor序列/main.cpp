/*Problem: xor序列*/
/*Contest: unknown_contest*/
/*Judge: NowCoder*/
/*URL: https://ac.nowcoder.com/acm/problem/17968*/
/*Start: Tue 10 Sep 2024 03:22:31 PM CST*/
/*Author: ShelpAm*/

// #include <bits/stdc++.h>
#include <algorithm>
#include <bit>
#include <climits>
#include <concepts>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <tuple>
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
namespace math {
template <std::unsigned_integral Value_type> class Xor_basis {
  static constexpr auto num_bits{sizeof(Value_type) * CHAR_BIT};

public:
  void insert(Value_type x)
  {
    for (int i{num_bits - 1}; i != -1; --i) {
      if ((x & Value_type{1} << i) == 0) {
        continue;
      }

      if (_bases.at(i) == 0) {
        _bases.at(i) = x;
        return;
      }

      x ^= _bases.at(i);
    }
  }

  [[nodiscard]] auto find(Value_type x) const -> bool
  {
    for (int i{num_bits - 1}; i != -1; i--) {
      if ((x & Value_type{1} << i) == 0) {
        continue;
      }

      if (_bases.at(i) == 0) {
        return false;
      }

      x ^= _bases.at(i);
    }

    return true;
  }

  [[nodiscard]] auto bases() const -> std::array<Value_type, num_bits> const &
  {
    return _bases;
  }

private:
  std::array<Value_type, num_bits> _bases{};
};
} // namespace math
void solve_case()
{
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  std::cin >> a;
  math::Xor_basis<u64> xb;
  for (auto const e : a) {
    xb.insert(e);
  }

  int q;
  std::cin >> q;
  for (int i{}; i != q; ++i) {
    int x, y;
    std::cin >> x >> y;
    std::cout << (xb.find(x ^ y) ? "YES" : "NO") << '\n';
  }
}
} // namespace
