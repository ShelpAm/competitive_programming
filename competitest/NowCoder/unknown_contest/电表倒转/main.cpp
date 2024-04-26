// Problem: 电表倒转
// Contest: unknown_contest
// Judge: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/81414/J
// Memory Limit: 524288
// Time Limit: 2000
// Start: Tue 23 Apr 2024 03:22:29 PM CST
// Author: ShelpAm

#include <bits/stdc++.h>
using namespace std;

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
template<typename T>
[[maybe_unused]] constexpr T mod{static_cast<T>(998244353)};
template<typename T>
[[maybe_unused]] constexpr T inf{std::numeric_limits<T>::max() / 2};
[[maybe_unused]] constexpr double eps{1e-8};

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
[[maybe_unused]] constexpr std::size_t msb(u64 const i)
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
  string s;
  cin >> s;
  int cntf{};
  deque<tuple<char, int, bool>> q;
  u64 ans{};

  function<void()> get;
  function<void(char)> push{[&](char ch) {
    // static int cur{};
    if (q.size() == 6) {
      auto [ch, day, used]{q.front()};
      if (ch == 'F') {
        --cntf;
      }
      q.pop_front();
      ans += 1;
      // cout << ch << " sold, earning $1\n";
    }

    // cout << "Placing " << ++cur << " th: " << ch << '\n';
    if (ch == 'A') {
      q.push_back({ch, 2, false});
    }
    else if (ch == 'B') {
      q.push_back({ch, 3, false});
    }
    else if (ch == 'C') {
      q.push_back({ch, 1, false});
    }
    else if (ch == 'D') {
      q.push_back({ch, 2, false});
    }
    else if (ch == 'E') {
      q.push_back({ch, 1, false});
    }
    else if (ch == 'F') {
      q.push_back({ch, -1, true});
      ++cntf;
    }
    else if (ch == 'G') {
      q.push_back({ch, -1, true});
      for (auto& [ch, day, used]: q) {
        day = 0;
        get();
      }
    }

    if (ch != 'F' && ch != 'G') {
      for (auto& [ch, day, used]: q) {
        day -= cntf;
      }
    }
  }};

  get = [&]() {
    for (auto& [ch, day, used]: q) {
      if (day <= 0 && !used) {
        used = true;
        if (ch == 'A') {
          ans += 1;
          // cout << "A's time up, earning $1\n";
        }
        else if (ch == 'B') {
          ans += 2;
          // cout << "B's time up, earning $2\n";
        }
        else if (ch == 'C') {
          s += "AB";
          // push('A');
          // push('B');
        }
        else if (ch == 'D') {
          set<char> s;
          for (auto const [ch, day, used]: q) {
            s.insert(ch);
          }
          ans += s.size();
          // cout << "D's time up, earning $" << s.size() << "\n";
        }
        else if (ch == 'E') {
          s += 'F';
          // push('F');
        }
      }
    }
  };

  for (int i{}; i != s.size(); ++i) {
    auto const ch{s[i]};
    push(ch);
    get();
    // cout << "REPORTING: money: " << ans << "\n     used\n";
    // for (auto& [ch, day, used]: q) {
    //   cout << '\t' << ch << ' ' << day << ' ' << used << '\n';
    // }
    // cout << "IN HAND: " << s << '\n';
    // cout << '\n';
  }
  cout << ans;
}

int main()
{
  impl::io_accelerator accelerator;
  solve_all_cases(solve_case, std::cin);
  return 0;
}
