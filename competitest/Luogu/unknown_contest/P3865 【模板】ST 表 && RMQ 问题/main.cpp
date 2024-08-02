/*Problem: P3865 【模板】ST 表 && RMQ 问题*/
/*Contest: unknown_contest*/
/*Judge: Luogu*/
/*URL: https://www.luogu.com.cn/problem/P3865*/
/*Start: Thu 01 Aug 2024 03:28:04 PM CST*/
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
  assert(i != 0);
  // To do: add cpp17 support
  /*return static_cast<int>(sizeof(T) * CHAR_BIT - 1 - std::countl_zero(i));*/
  int num_leading_zeros{};
  if constexpr (std::is_same_v<T, unsigned long long>) {
    num_leading_zeros = __builtin_clzll(i);
  }
  if constexpr (std::is_same_v<T, unsigned long>) {
    num_leading_zeros = __builtin_clzl(i);
  }
  else if constexpr (std::is_same_v<T, unsigned int>) {
    num_leading_zeros = __builtin_clz(i);
  }
  else {
    static_assert(false, "Unsupported type");
    static_assert(!std::is_signed_v<T>,
                  "msb is implemented based on unsigned integers");
  }
  return static_cast<int>(sizeof(T) * CHAR_BIT - 1 - num_leading_zeros);
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
namespace sparse_table {
// Note: 0-indexed
template <typename T, typename F> class Sparse_table {
public:
  Sparse_table(std::vector<T> table)
      : _table(msb(table.size()) + 1, std::move(table))
  {
    for (std::size_t i{1}; i != _table.size(); ++i) {
      for (std::size_t j{}; j != table.size(); ++j) {
        _table[i][j] = _f(_table[i - 1][j], _table[i - 1][j + (1 << (i - 1))]);
      }
    }
  }

  [[nodiscard]] auto query(unsigned const l, unsigned const r) const -> int
  {
    assert(r >= l);
    auto const k{msb(r - l + 1)};
    return _f(_table[k][l], _table[k][r - (1 << k) + 1]);
  }

private:
  std::vector<std::vector<T>> _table;
  F _f;
};

namespace details {
template <typename T> struct Min {
  constexpr auto operator()(T const &lhs, T const &rhs) const -> T const &
  {
    return std::min(lhs, rhs);
  }
};
template <typename T> struct Max {
  constexpr auto operator()(T const &lhs, T const &rhs) const -> T const &
  {
    return std::max(lhs, rhs);
  }
};
} // namespace details

template <typename T> class Min_st : public Sparse_table<T, details::Min<T>> {
public:
  using Sparse_table<T, details::Min<T>>::Sparse_table;
};
template <typename T> Min_st(std::vector<T>) -> Min_st<T>;
template <typename T> class Max_st : public Sparse_table<T, details::Max<T>> {
public:
  using Sparse_table<T, details::Max<T>>::Sparse_table;
};
template <typename T> Max_st(std::vector<T>) -> Max_st<T>;
} // namespace sparse_table
void solve_case()
{
  int n, m;
  std::cin >> n >> m;
  std::vector<int> a(n);
  std::cin >> a;
  sparse_table::Max_st st(a);
  for (int i{}; i != m; ++i) {
    int l, r;
    std::cin >> l >> r;
    --l, --r;
    std::cout << st.query(l, r) << '\n';
  }
}
} // namespace
