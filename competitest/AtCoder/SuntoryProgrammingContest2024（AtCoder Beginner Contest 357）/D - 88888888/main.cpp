// Problem: D - 88888888
// Contest: SuntoryProgrammingContest2024（AtCoder Beginner Contest 357）
// Judge: AtCoder
// URL: https://atcoder.jp/contests/abc357/tasks/abc357_d
// Memory Limit: 1024
// Time Limit: 2000
// Start: Sat 08 Jun 2024 08:01:47 PM CST
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
template <std::size_t N> class matrix {
  friend matrix operator*(matrix const &lhs, matrix const &rhs);

public:
  matrix(std::array<std::array<std::int_fast64_t, 2>, 2> const &data)
      : _data(data) {}
  matrix(std::int_fast64_t e) {
    for (int i{}; i != 2; ++i) {
      _data[i][i] = e;
    }
  }
  matrix &operator%=(std::int_fast64_t mod) {
    for (auto &line : _data) {
      for (auto &ele : line) {
        ele %= mod;
      }
    }
    return *this;
  }
  [[nodiscard]] std::array<std::array<std::int_fast64_t, 2>, 2> const &
  data() const {
    return _data;
  }

private:
  std::array<std::array<std::int_fast64_t, N>, N> _data{};
};
/*cross production*/
template <std::size_t N>
matrix<N> operator*(matrix<N> const &lhs, matrix<N> const &rhs) {
  auto n{static_cast<int>(lhs._data.size())};
  matrix<N> res{0};
  for (int i{}; i != n; ++i) {
    for (int j{}; j != n; ++j) {
      for (int k{}; k != n; ++k) {
        (res._data[i][j] += lhs._data[i][k] * rhs._data[k][j]);
      }
    }
  }
  return res;
}
template <std::size_t N>
matrix<N> operator%(matrix<N> lhs, std::int_fast64_t mod) {
  return lhs %= mod;
}
void solve_case() {
  using namespace std;
  u64 n;
  cin >> n;
  auto k{to_string(n).size()};
  auto p{pow(10LL, k, mod<u64>)};
  auto q{1};
  matrix<2> base{
      array<array<i64, 2>, 2>{array<i64, 2>{1, 1}, array<i64, 2>{0, 0}}};
  matrix<2> b{
      array<array<i64, 2>, 2>{array<i64, 2>{p, 0}, array<i64, 2>{q, 1}}};
  auto s{(base * pow(b, n - 1, mod<u64>)).data()[0][0]};
  auto res{n % mod<u64> * s % mod<u64>};
  cout << res;
}
