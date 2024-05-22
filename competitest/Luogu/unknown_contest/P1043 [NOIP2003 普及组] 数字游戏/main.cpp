// Problem: P1043 [NOIP2003 普及组] 数字游戏
// Contest: unknown_contest
// Judge: Luogu
// URL: https://www.luogu.com.cn/problem/P1043
// Memory Limit: 125
// Time Limit: 1000
// Start: Tue 14 May 2024 10:33:20 PM CST
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
using vb = std::vector<bool>;
using vvb = std::vector<vb>;
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
template <typename T>
[[maybe_unused]] constexpr T mod{static_cast<T>(998244353)};
[[maybe_unused]] constexpr std::int_fast64_t mod1e9{1000'000'009};
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
                      std::convertible_to<std::remove_cvref_t<T>, char const*>;
template <typename> struct is_tuple_t : std::false_type {};
template <typename... T>
struct is_tuple_t<std::tuple<T...>> : std::true_type {};
template <typename... T>
concept tuple = is_tuple_t<T...>::value;
} // namespace impl

template <std::int_fast64_t p> struct modint {
  modint() = default;
  modint(int const value) : value(value) {}
  modint(std::int_fast64_t const value) : value(value) {}
  modint(modint&&) = default;
  modint& operator=(const modint&) = default;
  modint& operator=(modint&&) = default;
  modint(modint const&) = default;
  ~modint() = default;
  operator std::int_fast64_t() { return value; }
  modint& operator+=(modint const other)
  {
    (value += other.value) %= p;
    return *this;
  }
  modint operator+(modint const other) const { return modint{*this} += other; }
  modint& operator-=(modint const other)
  {
    (((value -= other.value) %= p) += p) %= p;
    return *this;
  }
  modint operator-(modint const other) const { return modint{*this} -= other; }
  modint& operator*=(modint const other)
  {
    (value *= other.value) %= p;
    return *this;
  }
  modint operator*(modint const other) const { return modint{*this} *= other; }

  std::int_fast64_t value{};
};
using modint998244353 = modint<mod<int>>;
using modint1e9 = modint<mod1e9>;
template <std::int_fast64_t p>
std::istream& operator>>(std::istream& is, modint<p>& x)
{
  is >> x.value;
  return is;
}
template <std::int_fast64_t p>
std::ostream& operator<<(std::ostream& os, modint<p> x)
{
  os << x.value;
  return os;
}
constexpr std::istream& operator>>(std::istream& istream, auto&& t)
{
  using T = std::remove_cvref_t<decltype(t)>;
#ifdef __cpp_lib_ranges
  if constexpr (std::ranges::range<T>) {
    for (auto& ele : t) {
      istream >> ele;
    }
  }
#endif
  else if constexpr (impl::pair<T>) {
    istream >> t.first >> t.second;
  }
  else if constexpr (impl::tuple<T>) {
    static_assert(!impl::tuple<T>, "[operator>>] tuple: not implemented yet.");
  }
  else {
    istream >> t;
  }
  return istream;
}
constexpr void print(auto const& t, int const depth = 0)
{
  using T = std::remove_cvref_t<decltype(t)>;
  if constexpr (impl::string_like<T>) {
    std::cout << t;
  }
#ifdef __cpp_lib_ranges
  else if constexpr (std::ranges::range<T>) {
    for (auto const& ele : t) {
      print(ele, depth + 1);
    }
    if (depth != 0) {
      std::cout << '\n';
    }
  }
#endif
  else if constexpr (impl::pair<T>) {
    std::cout << "{ " << t.first << ", ";
    print(t.second, depth + 1);
    std::cout << " } ";
  }
  else if constexpr (impl::tuple<T>) {
    static_assert(!impl::tuple<T>, "[print] tuple: not implemented yet.\n");
  }
  else {
    std::cout << t << ' ';
  }

  if (depth == 0) {
    std::cout << '\n';
  }
}
constexpr void debug([[maybe_unused]] std::string_view s,
                     [[maybe_unused]] auto const& t)
{
#ifndef ONLINE_JUDGE
  std::cout << "[debug] " << s << ": ";
  if constexpr (std::ranges::range<decltype(t)>) {
    std::cout << '\n';
  }
  print(t);
  std::cout.flush();
#endif
}
constexpr bool check_max(auto& value, auto const& other)
#else
template <typename T> constexpr bool check_max(T& value, T const& other)
#endif
{
  if (value < other) {
    value = other;
    return true;
  }
  return false;
}
#ifdef __cpp_concepts
constexpr bool check_min(auto& value, auto const& other)
#else
template <typename T> constexpr bool check_min(T& value, T const& other)
#endif
{
  if (value > other) {
    value = other;
    return true;
  }
  return false;
}
#ifdef __cpp_concepts
constexpr auto sum_of(auto const& coll) noexcept
#else
template <typename Range> constexpr auto sum(Range const& coll) noexcept
#endif
{
  return std::accumulate(coll.begin(), coll.end(), std::int_fast64_t{});
}
#ifdef __cpp_concepts
constexpr auto pow(auto a, std::int_fast64_t b,
                   std::int_fast64_t const p) noexcept
#else
template <typename T> constexpr auto pow(T a, u64 b, u64 const p) noexcept
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
[[maybe_unused]] constexpr std::int_fast64_t lsb(std::int_fast64_t const i)
{
  return i & (-i);
}
// i mustn't be 0
[[maybe_unused]] constexpr std::size_t msb(std::uint_fast64_t const i)
{
  assert(i != 0);
  return sizeof(u64) * CHAR_BIT - 1 - __builtin_clzll(i);
}
#ifdef __cpp_concepts
void solve_all_cases(auto solve_case)
#else
template <typename F> void solve_all_cases(F solve_case)
#endif
{
  constexpr auto my_precision{10};
  [[maybe_unused]] auto const default_precision{
      std::cout.precision(my_precision)};
  std::cout << std::fixed;

  int t{1};
  // std::cin >> t;
  using return_type = decltype(solve_case());
  for (int i = 0; i != t; ++i) {
    if constexpr (
#ifdef __cpp_concepts
        std::same_as<return_type, void>
#else
        std::is_same_v<return_type, void>
#endif
    ) {
      solve_case();
    }
    else if constexpr (
#ifdef __cpp_concepts
        std::same_as<return_type, bool>
#else
        std::is_same_v<return_type, bool>
#endif
    ) {
      print(solve_case() ? "YES" : "NO");
    }
    else {
      print(solve_case());
    }
  }
}
} // namespace

auto solve_case()
{
  using namespace std;
  int n, m;
  cin >> n >> m;
  vector<modint<10>> s(n);
  s.insert(s.begin(), 0);
  cin >> s;
  for (int i{1}; i != n + 1; ++i) {
    s.push_back(s[i]);
  }
  for (int i{1}; i != s.size(); ++i) {
    s[i] += s[i - 1];
  }
  vector<vector<vector<int>>> f(
      2 * n + 1, vector<vector<int>>(2 * n + 1, vector<int>(m + 1)));
  vector<vector<vector<int>>> g(
      2 * n + 1, vector<vector<int>>(2 * n + 1, vector<int>(m + 1, inf<int>)));
  for (int i{1}; i != 2 * n + 1; ++i) {
    g[i][i][1] = f[i][i][1] = s[i] - s[i - 1];
  }
  for (int k{2}; k <= m; ++k) {                 // segments
    for (int l{1}; l <= n; ++l) {               // start point
      for (int r{l + k - 1}; r != l + n; ++r) { // end point
        for (int i{l + 1}; i <= r; ++i) {       // break point
          check_max(f[l][r][k], f[l][i - 1][k - 1] * (s[r] - s[i - 1]));
          check_min(g[l][r][k], g[l][i - 1][k - 1] * (s[r] - s[i - 1]));
          debug("k l r i, for g[l][i - 1][k - 1]",
                vector{k - 1, l, r, i - 1, g[l][i - 1][k - 1]});
        }
      }
    }
  }
  debug("f", f);
  debug("g", g);
  int ansmin{inf<int>}, ansmax{};
  for (int i{1}; i != n + 1; ++i) {
    check_min(ansmin, g[i][i + n - 1][m]);
    check_max(ansmax, f[i][i + n - 1][m]);
  }
  cout << ansmin << '\n' << ansmax;
}

int main()
{
  std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
  solve_all_cases(solve_case);
  return 0;
}
