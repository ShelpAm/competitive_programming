// Problem: E. Magic Subsequence
// Contest: 2024 (ICPC) Jiangxi Provincial Contest -- Official Contest
// Judge: Codeforces
// URL: https://codeforces.com/gym/105231/problem/E
// Memory Limit: 1024
// Time Limit: 8000
// Start: Wed 19 Jun 2024 04:41:17 PM CST
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
[[maybe_unused]] constexpr std::int_fast64_t mod1e9{1000'000'007};
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
    std::cout << " } \n";
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
[[maybe_unused]] constexpr std::int_fast64_t lsb(std::int_fast64_t i)
{
  return i & (-i);
}
// i mustn't be 0
[[maybe_unused]] constexpr int msb(std::uint_fast64_t i)
{
  assert(i != 0);
  return static_cast<int>(sizeof(decltype(i)) * CHAR_BIT - 1 -
                          __builtin_clzll(i));
}
#ifdef __cpp_concepts
void solve_all_cases(auto solve_case)
#else
template <typename F> void solve_all_cases(F solve_case)
#endif
{
  constexpr auto my_precision{10};
  std::cout.precision(my_precision);
  std::cout << std::fixed;
  int t{1};
  std::cin >> t;
  for (int i = 0; i != t; ++i) {
    solve_case();
  }
}
} // namespace
void solve_case();
int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve_all_cases(solve_case);
  return 0;
}
void solve_case()
{
  using namespace std;
  int n;
  cin >> n;
  vector<int> a(n);
  cin >> a;
  check_min(n, 30);
  vector<u64> pw3(31, 1);
  for (int i{1}; i != pw3.size(); ++i) {
    pw3[i] = pw3[i - 1] * 3;
  }
  auto break_down{[&](auto s, vector<int> &p, vector<int> &q) {
    for (int i{}; i != n; ++i) {
      auto state{s % 3};
      s /= 3;
      if (state == 1) {
        p.push_back(i + 1);
      }
      else if (state == 2) {
        q.push_back(i + 1);
      }
    }
  }};
  vector<pair<i64, u64>> res1, res2;
  auto search{[&](int l, int r, auto &p) {
    vector<pair<i64, u64>> v{{0, 0}};
    v.reserve(pw3[r - l + 1]);
    for (int i{l}; i != r + 1; ++i) {
      auto m{v.size()};
      for (int j{}; j != m; ++j) {
        auto &[diff, set]{v[j]};
        v.emplace_back(diff + a[i], set + 1 * pw3[i]);
      }
      for (int j{}; j != m; ++j) {
        auto &[diff, set]{v[j]};
        v.emplace_back(diff - a[i], set + 2 * pw3[i]);
      }
      inplace_merge(v.begin(), v.begin() + m, v.begin() + 2 * m);
      inplace_merge(v.begin(), v.begin() + 2 * m, v.begin() + 3 * m);
      v.resize(unique(v.begin(), v.end(),
                      [](auto &l, auto &r) { return l.first == r.first; }) -
               v.begin());
    }
    p = std::move(v);
  }};
  auto mid{n / 2};
  search(0, mid - 1, res1);
  search(mid, n - 1, res2);
  auto find{[](vector<pair<i64, u64>> const &r, auto const &k) {
    int lo{}, hi = r.size();
    while (lo < hi) {
      auto mid{lo + hi >> 1};
      if (r[mid].first >= k) {
        hi = mid;
      }
      else {
        lo = mid + 1;
      }
    }
    return lo;
  }};
  for (auto [k, s1] : res1) {
    if (k == 0) {
      continue;
    }
    if (auto idx{find(res2, -k)}; idx != res2.size() && res2[idx].first == -k) {
      auto s2{res2[idx].second};
      vector<int> p, q;
      break_down(s1, p, q);
      break_down(s2, p, q);
      cout << p.size() << ' ';
      print(p);
      cout << q.size() << ' ';
      print(q);
      return;
    }
  }
  cout << -1 << '\n';
}
