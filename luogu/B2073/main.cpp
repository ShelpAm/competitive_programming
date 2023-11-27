#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

using ::std::size_t;

// constexpr bool debug{false};

template<typename T> T read()
{
  T tmp;
  std::cin >> tmp;
  return tmp;
}
template<typename value_t> class input_value {
public:
  input_value(): value_(read<value_t>()) {}
  input_value(const input_value&) = delete;
  input_value(input_value&&) = delete;
  input_value& operator=(const input_value&) = delete;
  input_value& operator=(input_value&&) = delete;
  ~input_value() = default;
  operator value_t&() { return value(); }
  value_t& value() { return value_; }
private:
  value_t value_;
};
template<size_t i, size_t j, typename value_type> using arr2
    = std::array<std::array<value_type, j>, i>;
template<size_t i, size_t j> using arr2uz = arr2<i, j, size_t>;
template<size_t i, size_t j> using arr2ll = arr2<i, j, long long>;
template<typename value_type> using vec2_impl
    = std::vector<std::vector<value_type>>;
template<typename value_t> class vec2 : public vec2_impl<value_t> {
public:
  vec2(size_t const i, size_t const j)
      : vec2_impl<value_t>(i, std::vector<value_t>(j, {}))
  {}
};
using vec2uz = vec2<size_t>;
using vec2ll = vec2<long long>;
template<typename T> concept is_pair = requires(T t) {
  t.first;
  t.second;
};
void print(auto&& t)
{
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      print(ele);
    }
    std::cout << '\n';
  }
  else if constexpr (is_pair<decltype(t)>) {
    std::cout << t.first << ": " << t.second << ", ";
  }
  else {
    std::cout << t << ' ';
  }
}
class high_accuracy_number;
high_accuracy_number trim(high_accuracy_number const& n);
class high_accuracy_number {
  friend std::istream& operator>>(std::istream& istream,
                                  high_accuracy_number& number);
  friend std::ostream& operator<<(std::ostream& ostream,
                                  high_accuracy_number const& number);
public:
  high_accuracy_number(): number_("0") {}
  high_accuracy_number(size_t const i): number_(std::to_string(i)) {}
  high_accuracy_number(std::string_view const& number): number_(number)
  {
    trim();
  }
  high_accuracy_number(high_accuracy_number const&) = default;
  high_accuracy_number& operator=(high_accuracy_number const&) = default;
  ~high_accuracy_number() = default;
  high_accuracy_number operator+(high_accuracy_number const& other) const;
  high_accuracy_number operator-(high_accuracy_number const& other) const;
  high_accuracy_number operator*(high_accuracy_number const& other) const;
  high_accuracy_number operator/(high_accuracy_number const& other) const;
  auto operator<=>(high_accuracy_number const& other) const
  {
    auto me{::trim(*this)};
    auto oth{::trim(other)};
    auto ordering{me.number().size() <=> oth.number().size()};
    if (ordering == std::strong_ordering::equal) {
      return me.number() <=> oth.number();
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
    long long sub{static_cast<long long>(get(a, i))
                  - static_cast<long long>(get(b, i)) - borrow};
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
  return std::accumulate(numbers.begin(), numbers.end(),
                         high_accuracy_number("0"));
}
// Does some small division.
size_t high_accuracy_divide(std::string const& a, std::string const& b,
                            int /* placeholder */)
{
  for (size_t i{1}; i != -1UZ; ++i) {
    if (high_accuracy_number{b} * high_accuracy_number{i}
        > high_accuracy_number{a}) {
      return i - 1;
    }
  }
  // Normally, the program never reaches here.
  return -1UZ;
}
high_accuracy_number high_accuracy_divide(std::string const& a,
                                          std::string const& b)
{
  if (a.size() < b.size()) {
    return high_accuracy_number{0};
  }

  std::string s;
  auto j{b.size() - 1};
  high_accuracy_number sub{a.substr(0, j)};
  for (;;) {
    // finds min value that can be divided by `b`.
    while (true) {
      if (j == a.size()) {
        high_accuracy_number result{s};
        result.trim();
        return result;
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
high_accuracy_number
high_accuracy_number::operator+(high_accuracy_number const& other) const
{
  return high_accuracy_add(number_, other.number_);
}
high_accuracy_number
high_accuracy_number::operator-(high_accuracy_number const& other) const
{
  return high_accuracy_subtract(number_, other.number_);
}
high_accuracy_number
high_accuracy_number::operator*(high_accuracy_number const& other) const
{
  return high_accuracy_multiply(number_, other.number_);
}
high_accuracy_number
high_accuracy_number::operator/(high_accuracy_number const& other) const
{
  return high_accuracy_divide(number_, other.number_);
}
std::istream& operator>>(std::istream& istream, high_accuracy_number& number)
{
  istream >> number.number_;
  return istream;
}
std::ostream& operator<<(std::ostream& ostream,
                         high_accuracy_number const& number)
{
  ostream << number.number_;
  return ostream;
}

void solve_case()
{
  input_value<size_t> a;
  input_value<size_t> b;
  input_value<size_t> n;
  a %= b;
  while (n-- != 0) {
    a %= b;
    a *= 10;
  }
  std::cout << a / b;
}
int main()
{
  auto n{1UZ};
  // n = read<size_t>();
  for (size_t i{}; i != n; ++i) {
    solve_case();
  }
  return 0;
}
