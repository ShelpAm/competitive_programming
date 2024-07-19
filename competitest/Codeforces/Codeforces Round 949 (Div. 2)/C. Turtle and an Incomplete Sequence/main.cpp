// Problem: C. Turtle and an Incomplete Sequence
// Contest: Codeforces Round 949 (Div. 2)
// Judge: Codeforces
// URL: https://codeforces.com/contest/1981/problem/C
// Memory Limit: 256
// Time Limit: 2000
// Start: Fri 31 May 2024 06:05:16 PM CST
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
                      std::convertible_to<std::remove_cvref_t<T>, char const *>;
template <typename> struct is_tuple_t : std::false_type {};
template <typename... T>
struct is_tuple_t<std::tuple<T...>> : std::true_type {};
template <typename... T>
concept tuple = is_tuple_t<T...>::value;
} // namespace impl

constexpr auto &operator>>(auto &istream, auto &&t)
{
  using T = std::remove_cvref_t<decltype(t)>;
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
  else if constexpr (impl::tuple<T>) {
    static_assert(!impl::tuple<T>, "[operator>>] tuple: not implemented yet.");
  }
  else {
    istream >> t;
  }
  return istream;
}
constexpr void print(auto const &t, int const depth = 0)
{
  using T = std::remove_cvref_t<decltype(t)>;
  if constexpr (impl::string_like<T>) {
    std::cout << t;
  }
#ifdef __cpp_lib_ranges
  else if constexpr (std::ranges::range<T>) {
    for (auto const &ele : t) {
      print(ele, depth + 1);
    }
    if (depth != 0) {
      std::cout << '\n';
    }
  }
#endif
  else if constexpr (impl::pair<T>) {
    std::cout << "{ ";
    print(t.first, depth + 1);
    std::cout << ", ";
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
                     [[maybe_unused]] auto const &t)
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
constexpr bool check_max(auto &value, auto const &other)
#else
template <typename T, typename S>
constexpr bool check_max(T &value, S const &other)
#endif
{
  if (value < other) {
    value = other;
    return true;
  }
  return false;
}
#ifdef __cpp_concepts
constexpr bool check_min(auto &value, auto const &other)
#else
template <typename T, typename S>
constexpr bool check_min(T &value, S const &other)
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
template <typename Range> constexpr auto sum(Range const &coll) noexcept
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
[[maybe_unused]] constexpr int msb(std::uint_fast64_t const i)
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
  std::cin >> t;
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
  int n;
  cin >> n;
  vector<int> a(n);
  cin >> a;
  if (a == vector<int>(n, -1)) {
    for (int i{}; i != n; ++i) {
      cout << 1 * (i % 2 == 1 ? 1 : 2) << ' ';
    }
    cout << '\n';
    return;
  }
  vector<pair<int, int>> list;
  int fl{inf<int>}, fr{};
  for (int i{}; i != n; ++i) {
    if (a[i] != -1) {
      list.push_back({i, a[i]});
      check_min(fl, i);
      check_max(fr, i);
    }
  }
  auto check{
      [&](int i) { return a[i + 1] / 2 == a[i] || a[i] / 2 == a[i + 1]; }};
  auto process{[&](auto l, auto r) {
    while (l + 1 < r) {
      ++l, --r;
      if (a[l - 1] != 1) {
        a[l] = a[l - 1] / 2;
      }
      else {
        a[l] = a[l - 1] * 2;
      }
      if (a[r + 1] != 1) {
        a[r] = a[r + 1] / 2;
      }
      else {
        a[r] = a[r + 1] * 2;
      }
    }
  }};
  for (int i{}; i != list.size() - 1; ++i) {
    auto [l, le]{list[i]};
    auto [r, re]{list[i + 1]};
    debug("l r", pair{l, r});
    auto const d{abs(msb(re) - msb(le))};
    debug("d", d);
    if (r - l < d || d % 2 != (r - l) % 2) {
      debug("odd-even bad", "");
      cout << -1 << '\n';
      return;
    }
    if (le < re) {
      for (int x{1}; x != d + 1; ++x) {
        a[r - x] = a[r - x + 1] / 2;
      }
      debug("before process", a);
      auto const neo_r{r - d};
      debug("neor", neo_r);
      process(l, neo_r);
      debug("process ok", "");
      if (!check(l + neo_r >> 1) || !check(l + neo_r + 1 >> 1)) {
        debug("result wrong", a);
        cout << -1 << '\n';
        return;
      }
    }
    else {
      for (int x{1}; x != d + 1; ++x) {
        debug("after x=", x);
        a[l + x] = a[l + x - 1] / 2;
        debug("a", a);
      }
      auto const neo_l{l + d};
      debug("neol", neo_l);
      process(neo_l, r);
      if (!check(neo_l + r >> 1) || !check((neo_l + r + 1 >> 1))) {
        debug("result wrong", a);
        cout << -1 << '\n';
        return;
      }
    }
  }
  a[fl % 2] = a[fl];
  process(fl % 2, fl);
  if (a[0] == -1) {
    a[0] = a[1] * 2;
  }
  auto t{fr + (n - fr) / 2 * 2};
  a[t] = a[fr];
  process(fr, t);
  if (a[n - 1] == -1) {
    a[n - 1] = a[n - 2] * 2;
  }
  print(a);
}

int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve_all_cases(solve_case);
  return 0;
}
