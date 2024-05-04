// Problem: U420201 「QFOI R2」树色尤含残雨
// Contest: unknown_contest
// Judge: Luogu
// URL: https://www.luogu.com.cn/problem/U420201?contestId=166040
// Memory Limit: 512
// Time Limit: 1000
// Start: Sat 04 May 2024 02:21:52 PM CST
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
template <typename T>
[[maybe_unused]] constexpr T inf{std::numeric_limits<T>::max() / 2};
[[maybe_unused]] constexpr double eps{1e-8};

namespace impl {
// Concepts.
#ifdef __cpp_concepts
using ::std::remove_cvref_t;

template <typename T>
concept pair = requires(T t) {
  t.first;
  t.second;
};

template <typename> struct is_tuple_t : std::false_type {};
template <typename... T>
struct is_tuple_t<std::tuple<T...>> : std::true_type {};
template <typename... T>
concept tuple = is_tuple_t<T...>::value;

template <typename T>
concept c_str = std::same_as<char const *, remove_cvref_t<T>>;
template <typename T>
concept string = std::same_as<std::string, remove_cvref_t<T>>;
template <typename T>
concept string_view = std::same_as<std::string_view, remove_cvref_t<T>>;
template <typename T>
concept string_like = string<T> || string_view<T> || c_str<T>;
#else
template <class T>
using remove_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;
#endif

} // namespace impl

#ifdef __cpp_concepts
auto &operator>>(auto &istream, auto &&t) {
  using T = ::std::remove_cvref_t<decltype(t)>;
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
/// @warning Do not put string literals in this function, because we hasn't
/// (can't) inplement checking-string-literals functions.
void print(auto const &t, u64 const depth = 0) {
  using T = ::std::remove_cvref_t<decltype(t)>;
  if constexpr (impl::string_like<T>) {
    std::cout << t;
  } else if constexpr (::std::is_convertible_v<T, char const *>) {
    std::cout << static_cast<char const *>(t);
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
    std::cout << "{ " << t.first << ", " << t.second << " } ";
  } else if constexpr (impl::tuple<T>) {
    static_assert(!impl::tuple<T>, "[print] tuple: not implemented yet.\n");
  } else {
    std::cout << t << ' ';
  }

  if (depth == 0) {
    std::cout << '\n';
  }
}
void debug([[maybe_unused]] std::string_view s,
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
template <typename T>
constexpr bool check_max(T &value, T const &other)
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
template <typename T>
constexpr bool check_min(T &value, T const &other)
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
  using value_type = impl::remove_cvref_t<decltype(coll.front())>;
  return std::accumulate(coll.begin(), coll.end(), value_type{});
}
#ifdef __cpp_concepts
constexpr auto pow(auto a, u64 b, u64 const p) noexcept
#else
template <typename T>
constexpr auto pow(T a, u64 b, u64 const p) noexcept
#endif
{
  u64 res{1};
  while (b != 0) {
    if ((b & 1) == 1) {
      res = res * a % p;
    }
    a = a * a % p;
    b >>= 1;
  }
  return res;
}
[[maybe_unused]] constexpr std::int_fast64_t lsb(std::int_fast64_t const i) {
  return i & (-i);
}
// i mustn't be 0
[[maybe_unused]] constexpr std::size_t msb(std::uint_fast64_t const i) {
  assert(i != 0);
  return sizeof(u64) * CHAR_BIT - 1 - __builtin_clzll(i);
}
#ifdef __cpp_concepts
void solve_all_cases(auto solve_case)
#else
template <typename F>
void solve_all_cases(F solve_case)
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
    } else if constexpr (
#ifdef __cpp_concepts
        std::same_as<return_type, bool>
#else
        std::is_same_v<return_type, bool>
#endif
    ) {
      print(solve_case() ? "YES" : "NO");
    } else {
      print(solve_case());
    }
  }
}
} // namespace

struct sieve {
  sieve(size_t const upper_bound) : min_factor(upper_bound + 1, 0) {
    for (size_t i = 2; i != min_factor.size(); ++i) {
      if (min_factor[i] == 0) {
        primes.push_back(i);
        min_factor[i] = i;
      }
      for (auto const p : primes) {
        if (i * p > upper_bound || p > min_factor[i]) {
          break;
        }
        min_factor[i * p] = p;
      }
    }
  }

  [[nodiscard]] std::map<u64, u64> factorize(u64 x) const {
    std::map<u64, u64> res;
    assert(x <= (min_factor.size() - 1) * (min_factor.size() - 1));
    for (auto const p : primes) {
      if (p > x) {
        break;
      }
      while (x % p == 0) {
        x /= p;
        ++res[p];
      }
    }
    if (x >= min_factor.size()) {
      ++res[x];
    }
    return res;
  }

  vu primes;
  vu min_factor;
};
auto solve_case() {
#define int long long
  using namespace std;
  int x;
  cin >> x;
  // for (int x{2}; x != 11; ++x) {
  sieve sieve(sqrt(x) + 1);
  auto const factors{sieve.factorize(x)};
  int num_factors{}, max_num{};
  for (auto const [k, v] : factors) {
    num_factors += v;
    check_max(max_num, v);
  }
  if (factors.size() == 1) {
    cout << x;
  } else if (max_num >= 2 || num_factors % 2 == 0) {
    cout << 1;
  } else {
    cout << factors.begin()->first;
  }
  cout << '\n';
  // }
#undef int
}

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
  solve_all_cases(solve_case);
  return 0;
}
