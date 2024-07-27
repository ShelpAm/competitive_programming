/*Problem: A. Another A+B Problem*/
/*Contest: JXNU Summer Train 5*/
/*Judge: Codeforces*/
/*URL: https://codeforces.com/gym/538532/problem/A*/
/*Start: Fri 26 Jul 2024 03:24:48 PM CST*/
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
template <typename T, typename U>
constexpr auto check_max(T &value, U const &other) noexcept -> bool
{
  if (value < other) {
    value = other;
    return true;
  }
  return false;
}
template <typename T, typename U>
constexpr auto check_min(T &value, U const &other) noexcept -> bool
{
  if (value > other) {
    value = other;
    return true;
  }
  return false;
}
template <typename T> constexpr auto sum_of(T const &coll) noexcept
{
  return std::accumulate(coll.begin(), coll.end(), std::int_fast64_t{});
}
constexpr auto pow(int a, std::int_fast64_t b,
                   std::uint_fast64_t p) noexcept = delete;
template <typename T>
constexpr auto pow(T a, std::int_fast64_t b, std::uint_fast64_t p) noexcept
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
template <typename F>
auto binary_search(F check, std::int_fast64_t ok, std::int_fast64_t ng,
                   bool check_ok = true) -> std::int_fast64_t
{
  if (check_ok) {
    assert(check(ok));
  }
  while (std::abs(ok - ng) > 1) {
    auto const x{(ok + ng) / 2};
    (check(x) ? ok : ng) = x;
  }
  return ok;
}
template <typename T> constexpr auto lsb(T i) -> T
{
  static_assert(std::is_signed_v<T>,
                "lsb is implemented based on signed integers.");
  return i & -i;
}
// i mustn't be 0
template <typename T> constexpr auto msb(T i) -> int
{
  static_assert(!std::is_signed_v<T>,
                "msb is implemented based on unsigned integers");
  assert(i != 0);
  return static_cast<int>(sizeof(T) * CHAR_BIT - 1 - __builtin_clzll(i));
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
  std::string s, t;
  std::cin >> s >> t;
  std::vector<int> need(10);
  std::vector<int> disabled(10);
  for (int i{}; i != t.size(); ++i) {
    if (t[i] == 'P') {
      ++need[s[i] - '0'];
    }
    else if (t[i] == 'B') {
      disabled[s[i] - '0'] = 1;
    }
  }
  std::vector<std::vector<int>> ans;
  auto const index = std::vector{0, 1, 3, 4, 6, 7};
  constexpr auto end{pow(10ULL, 4ULL, inf<u64>)};
  for (int i{}; i != end; ++i) {
    std::vector<int> bits;
    auto k{i};
    for (int j{}; j != 4; ++j) {
      bits.push_back(k % 10);
      k /= 10;
    }
    auto const r{(bits[0] + bits[2]) * 10 + bits[1] + bits[3]};
    if (r >= 100) {
      continue;
    }
    bits.push_back(r / 10);
    bits.push_back(r % 10);
    auto ok{[&] {
      std::vector<int> cnt(10);
      for (int i{}; i != 6; ++i) {
        if (t[index[i]] != 'G') {
          ++cnt[bits[i]];
        }
      }
      for (int i{}; i != 6; ++i) {
        auto const idx{index[i]};
        if (disabled[s[idx] - '0']) {
          if (need[s[idx] - '0'] != cnt[s[idx] - '0']) {
            return false;
          }
        }
        else {
          if (need[s[idx] - '0'] > cnt[s[idx] - '0']) {
            return false;
          }
        }
        if (t[idx] == 'G' && bits[i] != s[idx] - '0') {
          return false;
        }
        if ((t[idx] == 'P' || t[idx] == 'B') && bits[i] == s[idx] - '0') {
          return false;
        }
      }
      return true;
    }};
    if (ok()) {
      ans.push_back(bits);
    }
  }
  std::cout << ans.size() << '\n';
  /*std::sort(ans.begin(), ans.end());*/
  for (auto const &bits : ans) {
    for (int j{}; j != 6; ++j) {
      std::cout << bits[j];
      if (j == 1) {
        std::cout << "+";
      }
      else if (j == 3) {
        std::cout << "=";
      }
    }
    std::cout << '\n';
  }
}
} // namespace
