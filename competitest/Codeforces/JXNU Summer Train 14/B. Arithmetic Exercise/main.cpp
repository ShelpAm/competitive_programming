/*Problem: B. Arithmetic Exercise*/
/*Contest: JXNU Summer Train 14*/
/*Judge: Codeforces*/
/*URL: https://codeforces.com/gym/543319/problem/B*/
/*Start: Fri 16 Aug 2024 01:41:39 PM CST*/
/*Author: ShelpAm*/

#include <bits/stdc++.h>

#ifdef __cpp_lib_ranges
#include <ranges>
#endif

namespace {
[[maybe_unused]] constexpr std::int_fast64_t mod998244853{998'244'353LL};
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
namespace multiprecision {
// Only supports positive numbers.
template <int Base> class Multiprecision {
  friend constexpr auto operator<(Multiprecision const &lhs,
                                  Multiprecision const &rhs) -> bool
  {
    if (lhs._bits.size() != rhs._bits.size()) {
      return lhs._bits.size() < rhs._bits.size();
    }
    for (auto i{lhs._bits.size()}; i != 0; --i) {
      if (lhs._bits[i - 1] != rhs._bits[i - 1]) {
        return lhs._bits[i - 1] < rhs._bits[i - 1];
      }
    }
    return false;
  }

  friend constexpr auto operator==(Multiprecision const &lhs,
                                   Multiprecision const &rhs) -> bool
  {
    return lhs._bits == rhs._bits;
  }

  friend constexpr auto operator<=(Multiprecision const &lhs,
                                   Multiprecision const &rhs) -> bool
  {
    return lhs < rhs || lhs == rhs;
  }

  static constexpr auto max_base_for_string{10};

public:
  Multiprecision() : _bits{0} {}

  constexpr Multiprecision(std::string_view const s) : _bits(s.begin(), s.end())
  {
    std::reverse(_bits.begin(), _bits.end());
    for (auto &e : _bits) {
      e -= '0';
    }
  }

  constexpr Multiprecision(std::int_fast64_t n)
  {
    while (n != 0) {
      _bits.push_back(n % Base);
      n /= Base;
    }
    if (_bits.empty()) {
      _bits.push_back(0);
    }
  }

  auto operator+=(Multiprecision const &rhs) -> Multiprecision &
  {
    _bits.resize(std::max(_bits.size(), rhs._bits.size()) + 1);
    for (std::size_t i{}; i != rhs.size(); ++i) {
      _bits[i] += rhs._bits[i];
    }
    push_up();
    normalize();
    return *this;
  }

  auto operator-=(Multiprecision const &rhs) -> Multiprecision &
  {
    assert(rhs <= *this);
    for (std::size_t i{}; i != rhs.size(); ++i) {
      _bits[i] -= rhs._bits[i];
    }
    push_down();
    normalize();
    return *this;
  }

  auto operator*=(Multiprecision const &rhs) -> Multiprecision &
  {
    std::vector<int> result(size() + rhs.size() + 1);

    for (std::size_t i{}; i != size(); ++i) {
      for (std::size_t j{}; j != rhs.size(); ++j) {
        result[i + j] += _bits[i] * rhs._bits[j];
      }
    }

    _bits = std::move(result);
    push_up();

    normalize();
    return *this;
  }

  auto operator/=(Multiprecision const &rhs) -> Multiprecision &
  {
    std::vector<int> quotient(size());
    Multiprecision current;

    for (std::size_t i{_bits.size()}; i != 0; --i) {
      current._bits.insert(current._bits.begin(), _bits[i - 1]);
      current.normalize();
      while (rhs <= current) {
        current -= rhs;
        ++quotient[i - 1];
      }
    }

    _bits = std::move(quotient);
    normalize();
    return *this;
  }

  auto operator%=(Multiprecision const &rhs) -> Multiprecision &
  {
    std::vector<int> quotient(_bits.size());
    Multiprecision current;

    for (std::size_t i{_bits.size()}; i != 0; --i) {
      current._bits.insert(current._bits.begin(), _bits[i - 1]);
      current.normalize();
      while (rhs <= current) {
        current -= rhs;
        ++quotient[i - 1];
      }
    }

    return *this = std::move(current);
  }

  [[nodiscard]] auto size() const -> std::size_t
  {
    return _bits.size();
  }

  [[nodiscard]] auto to_string() const -> std::string
  {
    static_assert(Base <= max_base_for_string, "Only for 10 and lower");
    std::string s{_bits.begin(), _bits.end()};
    std::reverse(s.begin(), s.end());
    for (auto &e : s) {
      e += '0';
    }
    return s;
  }

private:
  // Buffered constructor
  Multiprecision(std::size_t const size, int const _) : _bits(size) {}

  void normalize()
  {
    while (!_bits.empty() && _bits.back() == 0) {
      _bits.pop_back();
    }
    if (_bits.empty()) {
      _bits.push_back(0);
    }
  }

  void push_up()
  {
    for (std::size_t i{}; i != size() - 1; ++i) {
      _bits[i + 1] += _bits[i] / Base;
      _bits[i] %= Base;
    }
  }

  void push_down()
  {
    for (std::size_t i{}; i != size() - 1; ++i) {
      _bits[i + 1] += (_bits[i] - Base + 1) / Base;
      _bits[i] = (_bits[i] % Base + Base) % Base;
    }
  }

  std::vector<int> _bits; // Stored by little-endian.
};

template <int Base>
[[nodiscard]] constexpr auto
operator+(Multiprecision<Base> const &lhs,
          Multiprecision<Base> const &rhs) -> Multiprecision<Base>
{
  return Multiprecision{lhs} += rhs;
}

template <int Base>
[[nodiscard]] constexpr auto
operator-(Multiprecision<Base> const &lhs,
          Multiprecision<Base> const &rhs) -> Multiprecision<Base>
{
  return Multiprecision{lhs} -= rhs;
}

template <int Base>
[[nodiscard]] constexpr auto
operator*(Multiprecision<Base> const &lhs,
          Multiprecision<Base> const &rhs) -> Multiprecision<Base>
{
  return Multiprecision{lhs} *= rhs;
}

template <int Base>
[[nodiscard]] constexpr auto
operator/(Multiprecision<Base> const &lhs,
          Multiprecision<Base> const &rhs) -> Multiprecision<Base>
{
  return Multiprecision{lhs} /= rhs;
}

template <int Base>
[[nodiscard]] constexpr auto
operator%(Multiprecision<Base> const &lhs,
          Multiprecision<Base> const &rhs) -> Multiprecision<Base>
{
  return Multiprecision{lhs} %= rhs;
}

namespace details {
constexpr auto default_base{10};
}
using Int = Multiprecision<details::default_base>;
} // namespace multiprecision
void solve_case() noexcept
{
  int _a, _b, k;
  std::cin >> _a >> _b >> k;
  multiprecision::Int a{_a};
  a *= multiprecision::Int("1" + std::string(k + 1, '0'));
  a /= multiprecision::Int{_b};
  if (auto back{a.to_string().back() - '0'}; back >= 5) {
    a += multiprecision::Int{10 - back};
  }
  auto res{a.to_string()};
  res.pop_back();
  res.insert(res.begin() + res.size() - k, '.');
  if (res.front() == '.') {
    res.insert(res.begin(), '0');
  }
  std::cout << res;
}
} // namespace
