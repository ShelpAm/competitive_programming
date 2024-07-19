// Problem: 图腾
// Contest: unknown_contest
// Judge: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/82758/C
// Memory Limit: 524288
// Time Limit: 4000
// Start: Sat 08 Jun 2024 01:12:14 PM CST
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

constexpr auto &operator>>(auto &istream, auto &&t) {
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
  } else if constexpr (impl::tuple<T>) {
    static_assert(!impl::tuple<T>, "[operator>>] tuple: not implemented yet.");
  } else {
    istream >> t;
  }
  return istream;
}
constexpr void print(auto const &t, int const depth = 0) {
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
  } else if constexpr (impl::tuple<T>) {
    static_assert(!impl::tuple<T>, "[print] tuple: not implemented yet.\n");
  } else {
    std::cout << t << ' ';
  }

  if (depth == 0) {
    std::cout << '\n';
  }
}
constexpr void debug([[maybe_unused]] std::string_view s,
                     [[maybe_unused]] auto const &t) {
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
template <typename Range>
constexpr auto sum(Range const &coll) noexcept
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
[[maybe_unused]] constexpr std::int_fast64_t lsb(std::int_fast64_t i) {
  return i & (-i);
}
// i mustn't be 0
[[maybe_unused]] constexpr int msb(std::uint_fast64_t i) {
  assert(i != 0);
  return static_cast<int>(sizeof(decltype(i)) * CHAR_BIT - 1 -
                          __builtin_clzll(i));
}
#ifdef __cpp_concepts
void solve_all_cases(auto solve_case)
#else
template <typename F>
void solve_all_cases(F solve_case)
#endif
{
  constexpr auto my_precision{10};
  std::cout.precision(my_precision);
  std::cout << std::fixed;
  int t{1};
  // std::cin >> t;
  for (int i = 0; i != t; ++i) {
    solve_case();
  }
}
} // namespace
void solve_case();
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve_all_cases(solve_case);
  return 0;
}
template <class Info, class Tag> struct LazySegmentTree {
  const int n;
  std::vector<Info> info;
  std::vector<Tag> tag;
  LazySegmentTree(int n)
      : n(n), info(4 << std::__lg(n)), tag(4 << std::__lg(n)) {}
  LazySegmentTree(std::vector<Info> init) : LazySegmentTree(init.size()) {
    std::function<void(int, int, int)> build = [&](int p, int l, int r) {
      if (r - l == 1) {
        info[p] = init[l];
        return;
      }
      int m = (l + r) / 2;
      build(2 * p, l, m);
      build(2 * p + 1, m, r);
      pull(p);
    };
    build(1, 0, n);
  }
  void pull(int p) { info[p] = info[2 * p] + info[2 * p + 1]; }
  void apply(int p, const Tag &v) {
    info[p].apply(v);
    tag[p].apply(v);
  }
  void push(int p) {
    apply(2 * p, tag[p]);
    apply(2 * p + 1, tag[p]);
    tag[p] = Tag();
  }
  void modify(int p, int l, int r, int x, const Info &v) {
    if (r - l == 1) {
      info[p] = v;
      return;
    }
    int m = (l + r) / 2;
    push(p);
    if (x < m) {
      modify(2 * p, l, m, x, v);
    } else {
      modify(2 * p + 1, m, r, x, v);
    }
    pull(p);
  }
  void modify(int p, const Info &v) { modify(1, 0, n, p, v); }
  Info rangeQuery(int p, int l, int r, int x, int y) {
    if (l >= y || r <= x) {
      return Info();
    }
    if (l >= x && r <= y) {
      return info[p];
    }
    int m = (l + r) / 2;
    push(p);
    return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
  }
  Info rangeQuery(int l, int r) { return rangeQuery(1, 0, n, l, r); }
  void rangeApply(int p, int l, int r, int x, int y, const Tag &v) {
    if (l >= y || r <= x) {
      return;
    }
    if (l >= x && r <= y) {
      apply(p, v);
      return;
    }
    int m = (l + r) / 2;
    push(p);
    rangeApply(2 * p, l, m, x, y, v);
    rangeApply(2 * p + 1, m, r, x, y, v);
    pull(p);
  }
  void rangeApply(int l, int r, const Tag &v) {
    return rangeApply(1, 0, n, l, r, v);
  }
  void half(int p, int l, int r) {
    if (info[p].act == 0) {
      return;
    }
    if ((info[p].min + 1) / 2 == (info[p].max + 1) / 2) {
      apply(p, {-(info[p].min + 1) / 2});
      return;
    }
    int m = (l + r) / 2;
    push(p);
    half(2 * p, l, m);
    half(2 * p + 1, m, r);
    pull(p);
  }
  void half() { half(1, 0, n); }
};

struct Tag {
  i64 add = 0;

  void apply(Tag t) { add += t.add; }
};

struct Info {
  i64 min = inf<i64>;
  i64 max = -inf<i64>;
  i64 sum = 0;
  i64 act = 0;

  void apply(Tag t) {
    min += t.add;
    max += t.add;
    sum += act * t.add;
  }
};

Info operator+(Info a, Info b) {
  Info c;
  c.min = std::min(a.min, b.min);
  c.max = std::max(a.max, b.max);
  c.sum = a.sum + b.sum;
  c.act = a.act + b.act;
  return c;
}
void solve_case() {
  using namespace std;
  int n, m, q;
  cin >> n >> m >> q;
  vector<int> x(m);
  vector<int> v(m);
  for (auto &e : x) {
    cin >> e;
  }
  for (auto &e : v) {
    cin >> e;
  }
  map<int, i64> val;
  for (int i{}; i != n; ++i) {
    val[x[i]] = v[i];
  }
  LazySegmentTree<Info, Tag> seg(n + 2);
  auto change{[&](int l, int r, i64 v) {
    seg.rangeApply(l, r + 1, Tag{});
    seg.modify();
  }};
  auto query{[&](int l, int r) { return seg.rangeQuery(l, r).sum; }};
  for (auto it{val.begin()}; next(it) != val.end(); ++it) {
    auto [p, x]{*it};
    auto [q, y]{*next(it)};
    change(p, q, x * y);
  }
  for (int i{}; i != q; ++i) {
    int op, x, y;
    cin >> op >> x >> y;
    if (op == 1) {
      val[x] = y;
      auto [a, b]{*prev(val.lower_bound(x))};
      auto [c, d]{*val.upper_bound(x)};
      change(a, x, b * y);
      change(x + 1, c, y * d);
    } else if (op == 2) {
      cout << query(x, y + 1) << '\n';
    }
  }
}
