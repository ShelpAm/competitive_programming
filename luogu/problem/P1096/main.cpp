#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <deque>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#ifdef __cpp_concepts
#include <ranges>
#endif

// configs
using ::std::cin;
using ::std::cout;
using ::std::size_t;
using ::std::string;
using ::std::string_view;
using ::std::operator""sv;
using ::std::greater;
using ::std::less;
using ::std::map;
using ::std::numeric_limits;
using ::std::pair;
using ::std::priority_queue;
using ::std::queue;
using ::std::set;
using ::std::stack;
using ::std::unordered_map;
using ::std::unordered_set;
#ifdef __cpp_lib_ranges
using ::std::ranges::max;
using ::std::ranges::min;
using ::std::ranges::sort;
using ::std::ranges::swap;
using ::std::ranges::views::drop;
using ::std::ranges::views::iota;
using ::std::ranges::views::reverse;
using ::std::ranges::views::split;
using ::std::ranges::views::take;
#else
// TODO: Defines my own sort, etc.
#endif
[[maybe_unused]] constexpr auto endl{'\n'};
template<typename T> [[maybe_unused]] constexpr T mod{static_cast<T>(998244353ULL)};
template<typename T> [[maybe_unused]] constexpr T inf{numeric_limits<T>::max() >> 16};
namespace impl {
  template<typename value_type> using vec2_placeholder = std::vector<std::vector<value_type>>;
  template<typename value_type, size_t size> using arr1 = ::std::array<value_type, size>;
  template<size_t i, size_t j, typename value_type> using arr2
      = std::array<std::array<value_type, j>, i>;
  template<typename value_type> using vec1 = ::std::vector<value_type>;
  template<typename value_type> class vec2 : public vec2_placeholder<value_type> {
  public:
    constexpr vec2(size_t const i, size_t const j, value_type const& value = {})
        : vec2_placeholder<value_type>(i, std::vector<value_type>(j, value))
    {}
  };

#ifdef __cpp_concepts
  template<typename T> concept pair = requires(T t) {
    t.first;
    t.second;
  };

  template<typename> struct is_tuple_t : std::false_type {};
  template<typename... T> struct is_tuple_t<std::tuple<T...>> : std::true_type {};
  template<typename... T> concept tuple = is_tuple_t<T...>::value;

  template<typename T> concept c_str = std::same_as<char const*, std::remove_cvref_t<T>>;
  template<typename T> concept string = std::same_as<string, std::remove_cvref_t<T>>;
  template<typename T> concept string_view = std::same_as<string_view, std::remove_cvref_t<T>>;
  template<typename T> concept string_like = string<T> || string_view<T> || c_str<T>;
#endif
  class io_accelerator {
  public:
    io_accelerator()
    {
      std::ios::sync_with_stdio(false);
      std::cin.tie(nullptr);
      // The following line needn't to be executed because the above line actually had done this.
      // std::cout.tie(nullptr);
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
using puz = pair<size_t, size_t>;
using pll = pair<long long, long long>;
template<size_t i, size_t j> using arr2uz = impl::arr2<i, j, size_t>;
template<size_t i, size_t j> using arr2ll = impl::arr2<i, j, long long>;
template<size_t i, size_t j> using arr2b = impl::arr2<i, j, bool>;
using vec1uz = impl::vec1<size_t>;
using vec1ll = impl::vec1<long long>;
using vec1b = impl::vec1<bool>;
using vec2uz = impl::vec2<size_t>;
using vec2ll = impl::vec2<long long>;
using vec2b = impl::vec2<bool>;
[[maybe_unused]] static inline constexpr bool check_max(auto&& value, auto&& other)
{
  if (value < other) {
    value = other;
    return true;
  }
  return false;
}
[[maybe_unused]] static inline constexpr bool check_min(auto&& value, auto&& other)
{
  if (value > other) {
    value = other;
    return true;
  }
  return false;
}
static inline constexpr auto&& operator>>(auto&& is, auto&& t)
{
  using T = std::remove_cvref_t<decltype(t)>;
#ifdef __cpp_lib_ranges
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      is >> ele;
    }
    return is;
  }
#endif
#ifdef __cpp_concepts
  if constexpr (impl::pair<decltype(t)>) {
    return is >> t.first >> t.second;
  }
  else if constexpr (impl::tuple<T>) {
    std::cout
        << "[operator>>] TODO: This is a tuple whose output method hasn't been implemented.\n";
  }
#endif
  return is >> t;
}
static inline constexpr void print(auto const& t)
{
  using T = std::remove_cvref_t<decltype(t)>;
  if constexpr (impl::string_like<T>) {
    cout << t;
  }
  else if constexpr (std::is_convertible_v<T, char const*>) {
    cout << static_cast<char const*>(t);
  }
#ifdef __cpp_lib_ranges
  else if constexpr (std::ranges::range<T>) {
    for (auto&& ele: t) {
      print(ele);
    }
    std::cout << endl;
  }
#endif
#ifdef __cpp_concepts
  else if constexpr (impl::pair<T>) {
    std::cout << t.first << ": " << t.second << ", ";
  }
  else if constexpr (impl::tuple<T>) {
    std::cout << "[print] TODO: This is a tuple whose output method hasn't been implemented.\n";
  }
#endif
  else {
    std::cout << t << ' ';
  }
}
static inline constexpr void debug([[maybe_unused]] std::string_view s, [[maybe_unused]] auto&& t)
{
#ifdef DEBUG
  std::cout << "[debug] " << s << ": ";
  print(t);
  std::cout << endl;
#endif
}
class high_accuracy_number;
high_accuracy_number trim(high_accuracy_number const& n);
class high_accuracy_number {
  friend std::istream& operator>>(std::istream& istream, high_accuracy_number& number);
  friend std::ostream& operator<<(std::ostream& ostream, high_accuracy_number const& number);
public:
  high_accuracy_number(): number_("0") {}
  high_accuracy_number(size_t const i): number_(std::to_string(i)) {}
  high_accuracy_number(std::string_view const& number): number_(number) {}
  high_accuracy_number(high_accuracy_number const&) = default;
  high_accuracy_number& operator=(high_accuracy_number const&) = default;
  ~high_accuracy_number() = default;
  high_accuracy_number operator+(high_accuracy_number const& other) const;
  high_accuracy_number operator-(high_accuracy_number const& other) const;
  high_accuracy_number operator*(high_accuracy_number const& other) const;
  high_accuracy_number operator/(high_accuracy_number const& other) const;
  auto operator<=>(high_accuracy_number const& other) const
  {
    auto ordering{number_.size() <=> other.number_.size()};
    if (ordering == std::strong_ordering::equal) {
      return number_ <=> other.number_;
    }
    return ordering;
  }

  [[nodiscard]] std::string const& number() const { return number_; }
  [[nodiscard]] std::string& str() { return number_; }
  void trim()
  {
    auto i{number_.find_first_not_of('0')};
    number_ = i == std::string::npos ? "0" : number_.substr(i);
  }
private:
  std::string number_;
};
high_accuracy_number trim(high_accuracy_number const& n)
{
  high_accuracy_number tmp{n};
  tmp.trim();
  return tmp;
}
size_t get(std::string_view const& s, size_t const i)
{
  if (i >= s.size()) {
    return 0UZ;
  }
  return s[i] - '0';
}
high_accuracy_number high_accuracy_add(std::string a, std::string b)
{
  std::ranges::reverse(a);
  std::ranges::reverse(b);
  auto size{std::ranges::max(a.size(), b.size())};
  std::string s(size, ' ');
  size_t push{0};
  for (size_t i{0}; i != size; ++i) {
    size_t sum{get(a, i) + get(b, i) + push};
    if (sum >= 10) {
      push = 1;
      sum -= 10;
    }
    else {
      push = 0;
    }
    s[i] = static_cast<char>(sum + '0');
  }
  if (push == 1) {
    s.push_back('1');
  }
  std::ranges::reverse(s);
  return high_accuracy_number{s};
}
high_accuracy_number high_accuracy_subtract(std::string a, std::string b)
{
  // a must greater than or equal to b!
  assert(high_accuracy_number{a} >= high_accuracy_number{b});

  if (a == b) {
    return high_accuracy_number{0};
  }

  std::ranges::reverse(a);
  std::ranges::reverse(b);
  std::string s(a.size(), ' ');
  long long borrow{0};
  for (size_t i{0}; i != a.size(); ++i) {
    long long sub{static_cast<long long>(get(a, i)) - static_cast<long long>(get(b, i)) - borrow};
    if (sub < 0) {
      borrow = 1;
      sub += 10;
    }
    else {
      borrow = 0;
    }
    s[i] = static_cast<char>(sub + '0');
  }
  // This is impossible if a strictly non-less than b.
  // if (borrow == 1) {
  //   s.push_back('1');
  // }
  high_accuracy_number result{s};
  result.trim();
  std::ranges::reverse(result.str());
  return result;
}
high_accuracy_number high_accuracy_multiply(std::string a, char const b)
{
  if (a == "0" || b == '0') {
    return high_accuracy_number{"0"};
  }
  std::ranges::reverse(a);
  std::string s(a.size(), ' ');
  size_t push{};
  for (size_t i{}; i != a.size(); ++i) {
    size_t sum{get(a, i) * (b - '0') + push};
    push = sum / 10;
    sum %= 10;
    s[i] = static_cast<char>(sum + '0');
  }
  if (push != 0) {
    s.push_back(static_cast<char>(push + '0'));
  }
  std::ranges::reverse(s);
  return high_accuracy_number{s};
}
high_accuracy_number high_accuracy_multiply(std::string const& a, std::string b)
{
  // Make b.size() less than or equal to a.size(), so that function is faster.
  if (a.size() < b.size()) {
    return high_accuracy_multiply(b, a);
  }

  std::ranges::reverse(b);
  std::vector<high_accuracy_number> numbers(b.size());
  for (size_t i{}; i != b.size(); ++i) {
    numbers[i] = high_accuracy_multiply(a + std::string(i, '0'), b[i]);
  }
  return std::accumulate(numbers.begin(), numbers.end(), high_accuracy_number("0"));
}
// Does some small division.
size_t high_accuracy_divide(std::string const& a, std::string const& b, int /* placeholder */)
{
  for (size_t i{1}; i != -1UZ; ++i) {
    if (high_accuracy_number{b} * high_accuracy_number{i} > high_accuracy_number{a}) {
      return i - 1;
    }
  }
  // Normally, the program never reaches here.
  return -1UZ;
}
high_accuracy_number high_accuracy_divide(std::string const& a, std::string const& b)
{
  if (a.size() < b.size()) {
    return high_accuracy_number{0};
  }

  std::string s;
  auto j{b.size() - 1};
  high_accuracy_number sub{a.substr(0, j)};
  for (;;) {
    while (true) {
      if (j == a.size()) {
        return high_accuracy_number{s};
      }
      sub.str() += a[j++];
      if (sub >= high_accuracy_number{b}) {
        break;
      }
      s.push_back('0');
    }

    auto t{high_accuracy_divide(sub.str(), b, 0)};
    s.push_back(static_cast<char>(t + '0'));
    sub = sub - (high_accuracy_number{t} * high_accuracy_number{b});
  }
}
high_accuracy_number high_accuracy_number::operator+(high_accuracy_number const& other) const
{
  return high_accuracy_add(number_, other.number_);
}
high_accuracy_number high_accuracy_number::operator-(high_accuracy_number const& other) const
{
  return high_accuracy_subtract(number_, other.number_);
}
high_accuracy_number high_accuracy_number::operator*(high_accuracy_number const& other) const
{
  return high_accuracy_multiply(number_, other.number_);
}
high_accuracy_number high_accuracy_number::operator/(high_accuracy_number const& other) const
{
  return high_accuracy_divide(number_, other.number_);
}
std::istream& operator>>(std::istream& istream, high_accuracy_number& number)
{
  istream >> number.number_;
  return istream;
}
std::ostream& operator<<(std::ostream& ostream, high_accuracy_number const& number)
{
  ostream << number.number_;
  return ostream;
}
auto calc(auto const a)
{
  if (a == 1) {
    return high_accuracy_number{2};
  }
  return calc(a - 1) * 2 + 2;
}
static inline auto solve_case()
{
  size_t a;
  cin >> a;
  return calc(a);
}
static inline constexpr void solve_all_cases(auto&& solve_case_f)
{
  size_t t{1};
  // std::cin >> t;
  for (size_t i{}; i != t; ++i) {
    if constexpr (std::is_void_v<decltype(solve_case_f())>) {
      solve_case_f();
    }
    else {
      print(solve_case_f());
      cout << endl;
    }
  }
}
int main()
{
  impl::io_accelerator accelerator;
  solve_all_cases(solve_case);
  return 0;
}
