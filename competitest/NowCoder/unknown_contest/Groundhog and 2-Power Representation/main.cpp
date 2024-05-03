// Problem: Groundhog and 2-Power Representation
// Contest: unknown_contest
// Judge: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/80998/A
// Memory Limit: 524288
// Time Limit: 2000
// Start: Thu 02 May 2024 12:15:33 PM CST
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

using ::std::size_t;
class number_container_t;
number_container_t operator*(number_container_t const &lhs,
                             number_container_t const &rhs);

class number_container_t {
  friend auto &operator>>(auto &istream, number_container_t &number_container) {
    std::string tmp;
    istream >> tmp;
    number_container = tmp;
    return istream;
  }
  friend auto &operator<<(auto &ostream,
                          number_container_t const &number_container) {
    return ostream << number_container.to_string();
  }

public:
  number_container_t() = default;
  number_container_t(std::integral auto const num)
      : number_container_t(std::to_string(num)) {}
  number_container_t(std::string const &s) { *this = s; }
  number_container_t &operator=(std::string s) {
    if (s.empty()) {
      return *this;
    }
    std::ranges::reverse(s);
    if (s.back() == '-') {
      s.pop_back();
      sign_ = -1;
    }
    digits_.clear();
    digits_.reserve(s.size());
    for (auto const c : s) {
      digits_.emplace_back(to_number(c));
    }
    trim();
    return *this;
  }
  auto operator<=>(number_container_t const &rhs) const {
    auto size_order{size() <=> rhs.size()};
    if (size_order == std::strong_ordering::equal) {
      for (size_t i{size() - 1}; i != -1UZ; --i) {
        if (auto digit_order{digits_[i] <=> rhs[i]};
            digit_order != std::strong_ordering::equal) {
          return digit_order;
        }
      }
      return std::strong_ordering::equal;
    }
    return size_order;
  }
  number_container_t &operator+=(number_container_t const &rhs) {
    // Todo: fix this
    if (rhs.sign_ == -1 || sign_ == -1) {
      throw "Negetive number isn't supported.";
    }
    size_t new_size{std::ranges::max(size(), rhs.size())};
    digits_.resize(new_size);
    size_t tmp{};
    for (size_t i{}; i != new_size; ++i) {
      if (i < size()) {
        tmp += digits_[i];
      }
      if (i < rhs.size()) {
        tmp += rhs[i];
      }
      digits_[i] = tmp % base;
      tmp /= base;
    }
    if (tmp != 0) {
      digits_.emplace_back(tmp);
    }
    return *this;
  }
  number_container_t &operator-=(number_container_t const &rhs) {
    // Todo: fix this
    if (rhs.sign_ == -1 || sign_ == -1 || rhs > *this) {
      throw "Negetive number isn't supported.";
    }

    long long tmp{};
    for (size_t i{}; i != size(); ++i) {
      if (i < size()) {
        tmp += digits_[i];
      }
      if (i < rhs.size()) {
        tmp -= rhs[i];
      }
      if (tmp < 0) {
        tmp += base;
        digits_[i] = tmp % base;
        tmp = -1;
      } else {
        digits_[i] = tmp % base;
        tmp /= base;
      }
    }
    trim();
    return *this;
  }
  number_container_t &operator*=(number_container_t const &rhs) {
    auto new_size{size() * rhs.size()};
    // First calculate the result without pushing digits.
    std::vector<size_t> buf(new_size);
    for (size_t i{}; i != size(); ++i) {
      for (size_t j{}; j != rhs.size(); ++j) {
        buf[i + j] += digits_[i] * rhs[j];
      }
    }
    // Then we push digits.
    size_t tmp{};
    for (size_t i{}; i != new_size; ++i) {
      tmp += buf[i];
      buf[i] = tmp % base;
      tmp /= base;
    }
    if (tmp != 0) {
      buf.emplace_back(tmp);
    }
    digits_ = buf;
    sign_ *= rhs.sign_;
    trim();
    return *this;
  }
  number_container_t &operator/=(size_t const rhs) {
    if (*this < rhs) {
      return *this = "0";
    }

    std::vector<size_t> buf;
    size_t r{}; // remainder
    for (auto const i : digits_ | std::ranges::views::reverse) {
      r = r * 10 + i;
      buf.emplace_back(r / rhs);
      r %= rhs;
    }
    std::ranges::reverse(buf);

    digits_ = buf;
    trim();
    return *this;
  }
  [[deprecated]] number_container_t &operator/=(number_container_t const &rhs) {
    if (*this < rhs) {
      return *this = "0";
    }

    std::vector<size_t> buf;
    number_container_t r; // remainder
    size_t tmp{};
    for (size_t i{}; i != size(); ++i) {
      r.digits_.emplace_back(0);
      // r += number_container_t{digits_[i]};
      // buf.push_back(r / b);
      // r %= b;
    }

    trim();
    return *this;
  }
  size_t &operator[](size_t const index) { return digits_[index]; }
  size_t operator[](size_t const index) const {
    return (*const_cast<number_container_t *>(this))[index];
  }
  [[nodiscard]] size_t size() const { return digits_.size(); }
  [[nodiscard]] std::vector<char> to_vector() const {
    std::vector<char> s;
    s.reserve(digits_.size());
    for (auto const digit : digits_) {
      s.emplace_back(to_char(digit));
    }
    if (sign_ == -1) {
      s.emplace_back('-');
    }
    std::ranges::reverse(s);
    return s;
  }
  [[nodiscard]] std::string to_string() const {
    std::string s;
    for (auto const c : to_vector()) {
      s += c;
    }
    return s;
  }

private:
  // [[nodiscard]] char sign_char() const { return sign == 1 ? '\0' : '-'; }
  void adjust_sign() {
    if (digits_.size() == 1 && digits_[0] == 0 && sign_ == -1) {
      sign_ = 1;
    }
  }
  void trim() {
    while (digits_.size() != 1 && digits_.back() == 0) {
      digits_.pop_back();
    }
    adjust_sign();
  }

  static char to_char(size_t const i) {
    return static_cast<char>(i + (i > 9 ? 'A' - 10 : '0'));
  }

  static size_t to_number(char const c) {
    return static_cast<size_t>(c - (c >= 'A' ? 'A' - 10 : '0'));
  }

  long long base{10};
  long long sign_{1};
  std::vector<size_t> digits_{0};
};

number_container_t operator+(number_container_t const &lhs,
                             number_container_t const &rhs) {
  return number_container_t{lhs} += rhs;
}

number_container_t operator-(number_container_t const &lhs,
                             number_container_t const &rhs) {
  return number_container_t{lhs} -= rhs;
}
number_container_t operator-(number_container_t const &rhs) {
  return number_container_t{-1} * number_container_t{rhs};
}
number_container_t operator*(number_container_t const &lhs,
                             number_container_t const &rhs) {
  return number_container_t{lhs} *= rhs;
}
number_container_t operator/(number_container_t const &lhs, size_t const rhs) {
  return number_container_t{lhs} /= rhs;
}
number_container_t operator/(number_container_t const &lhs,
                             number_container_t const &rhs) {
  return number_container_t{lhs} /= rhs;
}
number_container_t pow(number_container_t const &lhs,
                       number_container_t const &rhs) {}

auto solve_case() {
  using namespace std;
  string s;
  cin >> s;
  stack<number_container_t> stk;
  stack<number_container_t> sum;
  for (auto const ch : s) {
    if (ch == '(') {
      stk.push(1);
      sum.push(0);
    } else if (ch == ')') {
      auto const exp{sum.top()};
      auto const base{stk.top()};
      sum.pop();
      stk.pop();
      sum.top() += base * *exp;
    } else if (ch == '+') {
      // stk.pop();
    } else {
      sum.push(ch - '0');
    }
  }
  cout << sum.top();
}

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
  solve_all_cases(solve_case);
  return 0;
}
