/*Problem: 岗位分配*/
/*Contest: unknown_contest*/
/*Judge: NowCoder*/
/*URL: https://ac.nowcoder.com/acm/contest/88269/C*/
/*Start: Wed 07 Aug 2024 02:44:54 PM CST*/
/*Author: ShelpAm*/

#include <bits/stdc++.h>

#ifdef __cpp_lib_ranges
#include <ranges>
#endif

namespace {
[[maybe_unused]] constexpr std::int_fast64_t mod998244353{998'244'353LL};
[[maybe_unused]] constexpr std::int_fast64_t mod1e9p7{1'000'000'007LL};
[[maybe_unused]] constexpr double eps{1e-8};
template <typename T>
[[maybe_unused]] constexpr T inf{std::numeric_limits<T>::max() / 2};

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
constexpr auto chmax(T &value, U const &other) noexcept -> bool
{
  if (value < other) {
    value = other;
    return true;
  }
  return false;
}
template <typename T, typename U>
constexpr auto chmin(T &value, U const &other) noexcept -> bool
{
  if (value > other) {
    value = other;
    return true;
  }
  return false;
}
template <typename C> constexpr auto sum_of(C const &coll) noexcept
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
                   bool check_ok = true) noexcept -> std::int_fast64_t
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
template <typename T> constexpr auto lsb(T i) noexcept -> T
{
  static_assert(std::is_signed_v<T>,
                "lsb is implemented based on signed integers.");
  return i & -i;
}
// i mustn't be 0
template <typename T>
constexpr auto count_leading_zeros(T const &i) noexcept -> int
{
  assert(i != 0);
  if constexpr (std::is_same_v<T, unsigned long long>) {
    return __builtin_clzll(i);
  }
  if constexpr (std::is_same_v<T, unsigned long>) {
    return __builtin_clzl(i);
  }
  if constexpr (std::is_same_v<T, unsigned int>) {
    return __builtin_clz(i);
  }
  /*static_assert(false, "Unsupported type");*/
  static_assert(!std::is_signed_v<T>,
                "msb is implemented based on unsigned integers");
  return -1; // Unreachable.
}
// i mustn't be 0
template <typename T> constexpr auto msb(T i) noexcept -> int
{
  return static_cast<int>(sizeof(T) * CHAR_BIT - 1 - count_leading_zeros(i));
}
/*[[maybe_unused]] auto gen_rand() noexcept*/
/*{*/
/*  static std::mt19937_64 rng(*/
/*      std::chrono::steady_clock::now().time_since_epoch().count());*/
/*  return rng();*/
/*}*/
void solve_case() noexcept;
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
namespace math {
// Time complexity:
// - initialization: O(upper_bound)
// - query:          O(1)
class Combinatorics {
public:
  /// @param  upper_bound  Maximum number whose inverse can be queried.
  /// @param  mod  Modulos of the results.
  Combinatorics(int upper_bound, std::int_fast64_t const mod)
      : _inverse(upper_bound + 1), _factorial(upper_bound + 1),
        _prefix_inverse(upper_bound + 1), _upper_bound(upper_bound), _mod{mod}
  {
    _inverse[0] = _inverse[1] = _factorial[0] = _factorial[1] =
        _prefix_inverse[0] = _prefix_inverse[1] = 1;
    for (std::int_fast64_t i{2}; i != upper_bound + 1; ++i) {
      _inverse[i] = (mod - mod / i) * _inverse[mod % i] % mod;
      _factorial[i] = _factorial[i - 1] * i % mod;
      _prefix_inverse[i] = _prefix_inverse[i - 1] * _inverse[i] % mod;
    }
  }

  [[nodiscard]] auto inverse(int const n) const -> std::int_fast64_t
  {
    return _inverse[n];
  }

  [[nodiscard]] auto factorial(int const n) const -> std::int_fast64_t
  {
    assert(n >= 0);
    assert(n <= _upper_bound);
    return _factorial[n];
  }

  [[nodiscard]] auto prefix_inverse(int const n) const -> std::int_fast64_t
  {
    assert(n >= 0);
    assert(n <= _upper_bound);
    return _prefix_inverse[n];
  }

  auto combination(int const n, int const m) -> std::int_fast64_t
  {
    assert(n >= 0);
    assert(n <= _upper_bound);
    if (n < m) {
      return 0;
    }
    return _factorial[n] * _prefix_inverse[m] % _mod * _prefix_inverse[n - m] %
           _mod;
  }

private:
  std::vector<std::int_fast64_t> _inverse;
  std::vector<std::int_fast64_t> _factorial;
  std::vector<std::int_fast64_t> _prefix_inverse;
  std::int_fast64_t _upper_bound;
  std::int_fast64_t _mod;
};

} // namespace math
void solve_case() noexcept
{
  int n, m;
  std::cin >> n >> m;
  std::vector<int> a(n);
  for (auto &e : a) {
    std::cin >> e;
  }
  math::Combinatorics comb(3000, mod998244353);
  std::cout << comb.combination(n + m - sum_of(a), n) << '\n';
}
} // namespace
