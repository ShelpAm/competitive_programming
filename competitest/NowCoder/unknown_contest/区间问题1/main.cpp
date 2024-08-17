/*Problem: 区间问题1*/
/*Contest: unknown_contest*/
/*Judge: NowCoder*/
/*URL: https://ac.nowcoder.com/acm/contest/88527/D*/
/*Start: Wed 14 Aug 2024 01:10:03 PM CST*/
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
class Segment_tree {
  struct Lazy_tag {
    auto operator+=(Lazy_tag const &rhs) -> Lazy_tag &
    {
      addition += rhs.addition;
      return *this;
    }

    std::int_fast64_t addition{};
  };

  struct Node {
    int left_end{};
    int right_end{};
  };

  struct Info {
    auto operator+=(Info const &rhs) -> Info &
    {
      sum += rhs.sum;
      return *this;
    }

    void apply(Lazy_tag const &lazy_tag, int const segment_length)
    {
      sum += lazy_tag.addition * segment_length;
    }

    std::int_fast64_t sum{};
  };

public:
  explicit Segment_tree(int const l, int const r)
      : _nodes(4 * (r - l + 1) + 1), _info(4 * (r - l + 1) + 1),
        _lazy_tags(4 * (r - l + 1) + 1)
  {
    build_tree(l, r, 1);
  }

  void apply(int const l, int const r, Lazy_tag const &tag)
  {
    apply_impl(l, r, 1, tag);
  }

  auto query(int const l, int const r) -> Info
  {
    return query_impl(l, r, 1);
  }

private:
  // Sets up segments that nodes manage.
  void build_tree(int const l, int const r, int const u)
  {
    _nodes[u].left_end = l;
    _nodes[u].right_end = r;

    if (l != r) {
      auto const m{(l + r) / 2};
      build_tree(l, m, u * 2);
      build_tree(m + 1, r, u * 2 + 1);
    }
  }

  void do_lazy_propagation(std::size_t const u)
  {
    if (!is_leaf(u)) {
      _lazy_tags[u * 2] += _lazy_tags[u];
      _lazy_tags[u * 2 + 1] += _lazy_tags[u];
      _info[u * 2].apply(_lazy_tags[u],
                         _nodes[u * 2].right_end - _nodes[u * 2].left_end + 1);
      _info[u * 2 + 1].apply(_lazy_tags[u], _nodes[u * 2 + 1].right_end -
                                                _nodes[u * 2 + 1].left_end + 1);
    }

    _lazy_tags[u] = {};
  }

  void apply_impl(int const l, int const r, std::size_t const u,
                  Lazy_tag const &tag)
  {
    _info[u].apply(tag, r - l + 1);

    if (l <= _nodes[u].left_end && _nodes[u].right_end <= r) {
      _lazy_tags[u] += tag;
      return;
    }

    if (_nodes[u * 2].right_end >= l) {
      apply_impl(l, std::min(r, _nodes[u * 2].right_end), u * 2, tag);
    }
    if (_nodes[u * 2 + 1].left_end <= r) {
      apply_impl(std::max(_nodes[u * 2 + 1].left_end, l), r, u * 2 + 1, tag);
    }
  }

  // We assume that [l, r] contains [_nodes[u].left_end, _nodes[u].right_end].
  [[nodiscard]] auto query_impl(int const l, int const r,
                                std::size_t const u) -> Info
  {
    // If [l, r] nests node u, the segment node doesn't have to be divided
    // anymore. So we direct return the info of this node.
    if (l <= _nodes[u].left_end && _nodes[u].right_end <= r) {
      return _info[u];
    }

    do_lazy_propagation(u);

    Info res;
    if (_nodes[u * 2].right_end >= l) {
      res += query_impl(l, r, u * 2);
    }
    if (_nodes[u * 2 + 1].left_end <= r) {
      res += query_impl(l, r, u * 2 + 1);
    }
    return res;
  }

  [[nodiscard]] auto is_leaf(std::size_t const u) const -> bool
  {
    return _nodes[u].left_end == _nodes[u].right_end;
  }

  std::vector<Node> _nodes;
  std::vector<Info> _info;
  std::vector<Lazy_tag> _lazy_tags;
};
void solve_case() noexcept
{
  int n;
  std::cin >> n;
  Segment_tree seg(1, n);
  for (int i{1}; i != n + 1; ++i) {
    int x;
    std::cin >> x;
    seg.apply(i, i, {.addition = x});
  }
  int q;
  std::cin >> q;
  for (int i{}; i != q; ++i) {
    int op;
    std::cin >> op;
    if (op == 1) {
      int l, r, d;
      std::cin >> l >> r >> d;
      seg.apply(l, r, {.addition = d});
    }
    else if (op == 2) {
      int x;
      std::cin >> x;
      std::cout << seg.query(x, x).sum << '\n';
    }
  }
}
} // namespace
