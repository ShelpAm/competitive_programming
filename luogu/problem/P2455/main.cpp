#include <bits/stdc++.h>
using ::std::abs;
using ::std::cin;
using ::std::cout;
using ::std::deque;
using ::std::greater;
using ::std::less;
using ::std::map;
using ::std::multimap;
using ::std::multiset;
using ::std::numeric_limits;
using ::std::pair;
using ::std::priority_queue;
using ::std::queue;
using ::std::set;
using ::std::stack;
using ::std::string;
using ::std::string_view;
using ::std::unordered_map;
using ::std::unordered_set;
using ::std::vector;

#ifdef __cpp_lib_ranges
#include <ranges>
using ::std::ranges::binary_search;
using ::std::ranges::count;
using ::std::ranges::find;
using ::std::ranges::lower_bound;
using ::std::ranges::max;
using ::std::ranges::min;
using ::std::ranges::reverse;
using ::std::ranges::reverse_view;
using ::std::ranges::sort;
using ::std::ranges::swap;
using ::std::ranges::upper_bound;
using ::std::ranges::views::drop;
using ::std::ranges::views::iota;
using ::std::ranges::views::split;
using ::std::ranges::views::take;
#else
using ::std::binary_search;
using ::std::count;
using ::std::find;
using ::std::lower_bound;
using ::std::max;
using ::std::min;
using ::std::reverse;
using ::std::sort;
using ::std::swap;
using ::std::upper_bound;
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
template<typename T>
[[maybe_unused]] constexpr T mod{static_cast<T>(998244353)};
template<typename T>
[[maybe_unused]] constexpr T inf{std::numeric_limits<T>::max() / 2};
[[maybe_unused]] constexpr double eps{1e-6};

namespace impl {
// Concepts.
#ifdef __cpp_concepts
using ::std::remove_cvref_t;

template<typename T> concept pair = requires(T t) {
  t.first;
  t.second;
};

template<typename> struct is_tuple_t : std::false_type {};
template<typename... T> struct is_tuple_t<std::tuple<T...>> : std::true_type {};
template<typename... T> concept tuple = is_tuple_t<T...>::value;

template<typename T> concept c_str
    = std::same_as<char const*, remove_cvref_t<T>>;
template<typename T> concept string = std::same_as<string, remove_cvref_t<T>>;
template<typename T> concept string_view
    = std::same_as<string_view, remove_cvref_t<T>>;
template<typename T> concept string_like
    = string<T> || string_view<T> || c_str<T>;
#else
template<class T> using remove_cvref_t
    = std::remove_cv_t<std::remove_reference_t<T>>;
#endif

/// @brief Turns off synchronization with stdio.
class io_accelerator {
 public:
  io_accelerator()
  {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    // The following line needn't to be executed because the above line actually
    // had done this. std::cout.tie(nullptr);
  }
  io_accelerator(const io_accelerator&) = delete;
  io_accelerator(io_accelerator&&) = delete;
  io_accelerator& operator=(const io_accelerator&) = delete;
  io_accelerator& operator=(io_accelerator&&) = delete;
  ~io_accelerator()
  {
    std::ios::sync_with_stdio(true);
    std::cin.tie(&std::cout);
  }
};
} // namespace impl

#ifdef __cpp_concepts
auto& operator>>(auto& istream, auto&& t)
{
  using T = ::std::remove_cvref_t<decltype(t)>;
#ifdef __cpp_lib_ranges
  if constexpr (std::ranges::range<T>) {
    for (auto& ele: t) {
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
/// @warning Do not put string literals in this function, because we hasn't
/// (can't) inplement checking-string-literals functions.
void print(auto const& t, u64 const depth = 0)
{
  using T = ::std::remove_cvref_t<decltype(t)>;
  if constexpr (impl::string_like<T>) {
    cout << t;
  }
  else if constexpr (::std::is_convertible_v<T, char const*>) {
    cout << static_cast<char const*>(t);
  }
#ifdef __cpp_lib_ranges
  else if constexpr (std::ranges::range<T>) {
    for (auto const& ele: t) {
      print(ele, depth + 1);
    }
    if (depth != 0) {
      cout << '\n';
    }
  }
#endif
  else if constexpr (impl::pair<T>) {
    std::cout << "{ " << t.first << ", " << t.second << " } ";
  }
  else if constexpr (impl::tuple<T>) {
    static_assert(!impl::tuple<T>, "[print] tuple: not implemented yet.\n");
  }
  else {
    std::cout << t << ' ';
  }

  if (depth == 0) {
    cout << '\n';
  }
}
void debug([[maybe_unused]] std::string_view s, [[maybe_unused]] auto const& t)
{
#ifndef ONLINE_JUDGE
  std::cout << "[debug] " << s << ": ";
  if constexpr (std::ranges::range<decltype(t)>) {
    std::cout << '\n';
  }
  print(t);
  cout.flush();
#endif
}
constexpr bool check_max(auto& value, auto const& other)
#else
template<typename T> constexpr bool check_max(T& value, T const& other)
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
template<typename T> constexpr bool check_min(T& value, T const& other)
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
template<typename Range> constexpr auto sum(Range const& coll) noexcept
#endif
{
  using value_type = impl::remove_cvref_t<decltype(coll.front())>;
  return std::accumulate(coll.begin(), coll.end(), value_type{});
}
#ifdef __cpp_concepts
constexpr auto pow(auto a, u64 b, u64 const p) noexcept
#else
template<typename T> constexpr auto pow(T a, u64 b, u64 const p) noexcept
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
[[maybe_unused]] constexpr u64 gcd(u64 a, u64 b) noexcept
{
  while (b != 0) {
    auto t = b;
    b = a % b;
    a = t;
  }
  return a;
}
[[maybe_unused]] constexpr u64 lcm(u64 a, u64 b) noexcept
{
  return a * b / gcd(a, b);
}
[[maybe_unused]] constexpr i64 lsb(i64 const i)
{
  return i & (-i);
}
// i mustn't be 0
[[maybe_unused]] constexpr u64 msb(u64 const i)
{
  assert(i != 0);
  return sizeof(u64) * CHAR_BIT - 1 - __builtin_clzll(i | 1);
}
#ifdef __cpp_concepts
void solve_all_cases(auto solve_case, [[maybe_unused]] std::istream& is)
#else
template<typename F>
void solve_all_cases(F solve_case, [[maybe_unused]] std::istream& is)
#endif
{
  constexpr auto my_precision{10};
  [[maybe_unused]] auto const default_precision{
      std::cout.precision(my_precision)};
  std::cout << std::fixed;

  int t{1};
  // is >> t;
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
  int n;
  cin >> n;
  std::vector<std::vector<double>> a(n, std::vector<double>(n + 1));
  cin >> a;
  bool free{};
  for (int i{}; i != n; ++i) {
    if (std::abs(a[i][i]) < eps) {
      int row{-1};
      for (int k{i + 1}; k != n; ++k) {
        if (std::abs(a[k][i]) < eps) {
          row = k;
          break;
        }
      }
      if (row == -1) {
        free = true;
        continue;
      }
      swap(a[i], a[row]);
    }
    for (int j{n}; j != -1; --j) {
      a[i][j] /= a[i][i];
    }
    for (int k{i + 1}; k != n; ++k) {
      for (int j{n}; j != i - 1; --j) {
        a[k][j] -= a[i][j] * a[k][i];
      }
    }
  }
  for (int i{n - 1}; i != -1; --i) {
    for (int k{i - 1}; k != -1; --k) {
      a[k][n] -= a[i][n] * a[k][i];
      a[k][i] = 0;
    }
  }
  // debug("a", a);
  if (std::abs(a[n - 1][n - 1]) < eps && std::abs(a[n - 1][n]) >= eps) {
    cout << -1;
    return;
  }
  if (free) {
    cout << 0;
    return;
  }
  for (int i{}; i != n; ++i) {
    cout << "x" << i + 1 << "=" << a[i][n] << '\n';
  }
}

int main()
{
  impl::io_accelerator accelerator;
  solve_all_cases(solve_case, std::cin);
  return 0;
}
