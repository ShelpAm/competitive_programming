// Problem: P5431 【模板】模意义下的乘法逆元 2
// Contest: unknown_contest
// Judge: Luogu
// URL: https://www.luogu.com.cn/problem/P5431
// Memory Limit: 128
// Time Limit: 550000
// Start: Fri 19 Jul 2024 04:14:32 PM CST
// Author: ShelpAm

#include <bits/stdc++.h>

#ifdef __cpp_lib_ranges
#include <ranges>
#endif

using i64 = std::int_fast64_t;
using u64 = std::uint_fast64_t;
using vi = std::vector<i64>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;
using vvvvi = std::vector<vvvi>;
using vu = std::vector<u64>;
using vvu = std::vector<vu>;
using vvvu = std::vector<vvu>;
using vvvvu = std::vector<vvvu>;
using vc = std::vector<char>;
using vvc = std::vector<vc>;
using vd = std::vector<double>;
using vvd = std::vector<vd>;
using pii = std::pair<i64, i64>;
using puu = std::pair<u64, u64>;
using triplei = std::tuple<i64, i64, i64>;
using tripleu = std::tuple<u64, u64, u64>;
using quadratici = std::tuple<i64, i64, i64, i64>;
using quadraticu = std::tuple<u64, u64, u64, u64>;

namespace {
[[maybe_unused]] constexpr std::int_fast64_t mod998244353{998'244'353LL};
[[maybe_unused]] constexpr std::int_fast64_t mod1e9p7{1'000'000'007LL};
template <typename T>
[[maybe_unused]] constexpr T inf{std::numeric_limits<T>::max() / 2};
[[maybe_unused]] constexpr double eps{1e-8};

#ifdef __cpp_concepts
namespace impl {
// Concepts.
template <typename T>
concept pair = requires(T t) {
  t.first;
  t.second;
};
template <typename T>
concept string_like = std::same_as<std::string, std::remove_cvref_t<T>> ||
                      std::same_as<std::string_view, std::remove_cvref_t<T>> ||
                      std::convertible_to<std::remove_cvref_t<T>, char const *>;
template <typename> struct is_tuple_t : std::false_type {};
template <typename... T>
struct is_tuple_t<std::tuple<T...>> : std::true_type {};
template <typename... T>
concept tuple = is_tuple_t<T...>::value;
} // namespace impl

constexpr auto operator>>(auto &istream, auto &&t) -> auto &
{
  using T = std::remove_cvref_t<decltype(t)>;
  static_assert(!impl::tuple<T>, "[print] tuple: not implemented yet.\n");
#ifdef __cpp_lib_ranges
  if constexpr (std::ranges::range<T>) {
    for (auto &ele : t) {
      istream >> ele;
    }
  }
#endif
  else if constexpr (impl::pair<T>) {
    istream >> t.first >> t.second;
  }
  else {
    istream >> t;
  }
  return istream;
}
constexpr auto print(auto &&t, int depth = 0, auto &out = std::cout) -> void
{
  using T = std::remove_cvref_t<decltype(t)>;
  static_assert(!impl::tuple<T>, "[print] tuple: not implemented yet.\n");
  if constexpr (impl::string_like<T>) {
    out << t;
  }
#ifdef __cpp_lib_ranges
  else if constexpr (std::ranges::range<T>) {
    for (auto const &ele : t) {
      print(ele, depth + 1, out);
    }
    if (depth != 0) {
      out << '\n';
    }
  }
#endif
  else if constexpr (impl::pair<T>) {
    out << "{ ";
    print(t.first, depth + 1, out);
    out << ", ";
    print(t.second, depth + 1, out);
    out << " }, ";
  }
  else {
    out << t << ' ';
  }

  if (depth == 0) {
    out << '\n';
  }
}
#endif
#ifndef ONLINE_JUDGE
constexpr auto debug(std::string_view s, auto &&t) -> void
{
  std::cerr << "[debug] " << s << ": ";
  if constexpr (std::ranges::range<decltype(t)>) {
    std::cerr << '\n';
  }
  print(t, 0, std::cerr);
  std::cerr.flush();
}
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
void solve_all_cases()
{
  constexpr auto my_precision{10};
  std::cout << std::fixed << std::setprecision(my_precision);
  int t{1};
  /*std::cin >> t;*/
  for (int i{}; i != t; ++i) {
    solve_case();
  }
}
} // namespace
auto main() -> int
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve_all_cases();
  return 0;
}
namespace {

// The following are function-like-objects classes.

/// Time complexity:
/// - initialization: O(upper_bound)
/// - query:          O(1)
class Inverse {
public:
  /// @param
  /// upper_bound maximal number whose inverse can be queried.
  Inverse(int upper_bound, std::int_fast64_t const mod)
      : _inverse(upper_bound + 1), _factorial(upper_bound + 1),
        _prefix_inverse(upper_bound + 1), _upper_bound(upper_bound)
  {
    _inverse[0] = _inverse[1] = _factorial[0] = _factorial[1] =
        _prefix_inverse[0] = _prefix_inverse[1] = 1;
    for (std::int_fast64_t i{2}; i != upper_bound + 1; ++i) {
      _inverse[i] = (mod - mod / i) * _inverse[mod % i] % mod;
      _factorial[i] = _factorial[i - 1] * i % mod;
      _prefix_inverse[i] = _prefix_inverse[i - 1] * _inverse[i] % mod;
    }
  }
  auto operator()(int const n) const -> std::int_fast64_t
  {
    assert(n >= 0);
    assert(n <= _upper_bound);
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
  [[nodiscard]] auto upper_bound() const -> std::int_fast64_t
  {
    return _upper_bound;
  }

private:
  std::vector<std::int_fast64_t> _inverse;
  std::vector<std::int_fast64_t> _factorial;
  std::vector<std::int_fast64_t> _prefix_inverse;
  std::int_fast64_t _upper_bound;
};

class Combination {
  friend class Arrangement;

public:
  /// @param
  /// upper_bound max(n, m) in `c(n, m)`
  Combination(int const upper_bound, int const mod)
      : _inverse(upper_bound, mod), _mod(mod)
  {
  }
  auto operator()(int const n, int const m) -> std::int_fast64_t
  {
    assert(n >= 0);
    assert(n <= _inverse.upper_bound());
    if (n < m) {
      return 0;
    }
    return _inverse.factorial(n) * _inverse.prefix_inverse(m) % _mod *
           _inverse.prefix_inverse(n - m) % _mod;
  }

private:
  Inverse _inverse;
  std::int_fast64_t _mod;
};

class Arrangement {
public:
  /// @param
  /// upper_bound max(n, m) in `a(n, m)`
  Arrangement(int const upper_bound, int const mod)
      : _combination(upper_bound, mod)
  {
  }
  auto operator()(int const n, int const m) -> std::int_fast64_t
  {
    if (n < m) {
      return 0;
    }
    return _combination(n, m) * _combination._inverse.factorial(n - m);
  }

private:
  Combination _combination;
};
void solve_case()
{
  using namespace std;
  i64 n, p, k;
  cin >> n >> p >> k;
  auto inv{[&](i64 n) { return pow(n, p - 2, p); }};
  i64 ans{};
  for (i64 i{1}; i != n + 1; ++i) {
    int a;
    cin >> a;
    ans += pow(k, i, p) * inv(a) % p;
    ans %= p;
  }
  cout << ans;
}
} // namespace
