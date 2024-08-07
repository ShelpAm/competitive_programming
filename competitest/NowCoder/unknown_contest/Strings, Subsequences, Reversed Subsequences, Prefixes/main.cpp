/*Problem: Strings, Subsequences, Reversed Subsequences, Prefixes*/
/*Contest: unknown_contest*/
/*Judge: NowCoder*/
/*URL: https://ac.nowcoder.com/acm/contest/81602/K*/
/*Start: Tue 06 Aug 2024 01:30:38 PM CST*/
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
namespace hash {
// note: zero-indexed
template <std::size_t Base> class Hash {
public:
  template <typename R>
  constexpr Hash(R const &range)
      : _hash_value(range.size() + 1), _pow_base(range.size() + 1)
  {
    for (std::size_t i{1}; i != _hash_value.size(); ++i) {
      _hash_value[i] = _hash_value[i - 1] * Base + range[i - 1];
    }

    _pow_base[0] = 1;
    for (std::size_t i{1}; i != _pow_base.size(); ++i) {
      _pow_base[i] = _pow_base[i - 1] * Base;
    }
  }

  [[nodiscard]] auto query(std::size_t const l,
                           std::size_t const r) const -> std::size_t
  {
    return _hash_value[r + 1] - _hash_value[l] * _pow_base[r - l + 1];
  }

  std::vector<std::size_t> _hash_value;
  std::vector<std::size_t> _pow_base;
};
} // namespace hash
auto work(std::string t) -> std::vector<int>
{
  /*std::cerr << "Finding palindrome of " << t << '\n';*/
  hash::Hash<131> hash{t};
  std::reverse(t.begin(), t.end());
  hash::Hash<131> hashr{t};
  std::reverse(t.begin(), t.end());
  /*debug("hash", hash._hash_value);*/
  /*debug("hashr", hashr._hash_value);*/
  std::vector<int> pos;
  for (int i{}; i != t.size(); ++i) {
    /*std::cerr << i << ' ' << hashr.query(0, i) << ' '*/
    /*          << hash.query(t.size() - 1 - i, t.size() - 1) << '\n';*/
    if (hashr.query(0, i) == hash.query(t.size() - 1 - i, t.size() - 1)) {
      pos.push_back(t.size() - 1 - i);
    }
  }
  return pos;
}
auto get(int r, std::string s, std::string t) -> int
{
  int j = 0;
  for (int i = 0; i < r; i++) {
    if (s[i] == t[j]) {
      j++;
    }
  }
  return j;
}
void solve_case() noexcept
{
  auto find_prefix{[](std::string_view const s, std::string_view const t) {
    int i{}, j{};
    while (i != s.size() && j != t.size()) {
      if (t[j] == s[i]) {
        if (++j == t.size()) {
          return i;
        }
      }
      ++i;
    }
    return -1;
  }};

  auto count_subsequences{[](std::string_view const s) {
    /*std::cerr << "s: " << s << '\n';*/
    std::vector<i64> f(s.size() + 1);
    std::unordered_map<char, int> last;
    f[0] = 1;
    for (int i{}; i != s.size(); ++i) {
      f[i + 1] = f[i] * 2 % mod1e9p7;
      if (last.count(s[i])) {
        f[i + 1] -= f[last[s[i]]];
        f[i + 1] %= mod1e9p7;
        f[i + 1] += mod1e9p7;
        f[i + 1] %= mod1e9p7;
      }
      last[s[i]] = i;
    }
    return f[s.size()];
  }};

  int n, m;
  std::cin >> n >> m;
  std::string s, t;
  std::cin >> s >> t;

  auto const l{find_prefix(s, t)};
  std::reverse(s.begin(), s.end());
  auto const r{n - find_prefix(s, t) - 1};
  std::reverse(s.begin(), s.end());
  if (l == -1 || r == n) {
    std::cout << 0 << '\n';
    return;
  }

  auto const pos{work(t)};
  auto const num_available_left{get(r, s, t)};
  /*std::cerr << "r: " << r << '\n';*/
  /*for (auto const e : pos) {*/
  /*  std::cerr << e << ' ';*/
  /*}*/
  /*std::cerr << '\n' << num_available_left << '\n';*/
  i64 ans{std::count_if(pos.begin(), pos.end(), [&](auto const e) {
    return e <= num_available_left;
  })}; // overlapping
  if (l < r) {
    ans += count_subsequences(s.substr(l + 1, r - l - 1)); // Non-overlapping
    ans %= mod1e9p7;
  }
  ans = (ans % mod1e9p7 + mod1e9p7) % mod1e9p7;
  std::cout << ans << '\n';
}
} // namespace
