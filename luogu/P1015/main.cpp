#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>
using ::std::size_t;

size_t n{};

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
void debug(std::string_view const& sv, auto&& t)
{
  std::cout << sv << ": ";
  print(t);
}
void input(auto&& t)
{
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      input(ele);
    }
  }
  else if constexpr (is_pair<decltype(t)>) {
    std::cin >> t.first >> t.second;
  }
  else {
    std::cin >> t;
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
  high_accuracy_number(std::string_view const& number, int): number_(number)
  {
    trim();
  }
  high_accuracy_number(std::string_view const& number)
  {
    for (auto const c: number) {
      if (std::isdigit(c) != 0) {
        number_.push_back(c);
      }
      else {
        number_.push_back('0' + 10 + c - 'A');
      }
    }
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
    return 0;
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
    if (sum >= n) {
      push = 1;
      sum -= n;
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
  return high_accuracy_number{s, 1};
}
high_accuracy_number
high_accuracy_number::operator+(high_accuracy_number const& other) const
{
  return high_accuracy_add(number_, other.number_);
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
bool is_palindrome(std::string_view const s)
{
  for (size_t i{}; i != (s.size() + 1) / 2; ++i) {
    if (s[i] != s[s.size() - i - 1]) {
      return false;
    }
  }
  return true;
}
void solve_case()
{
  std::string s;
  // n在最上面
  std::cin >> n >> s;
  high_accuracy_number num{s};
  size_t count{};
  while (!is_palindrome(num.number())) {
    auto reversed{num};
    std::ranges::reverse(reversed.str());
    num = num + reversed;
    ++count;
    if (count == 31) {
      break;
    }
  }
  if (count == 31) {
    std::cout << "Impossible!";
  }
  else {
    std::cout << "STEP=" << count;
  }
}

int main()
{
  auto n{1};
  // n = read<size_t>();
  for (size_t i{}; i != n; ++i) {
    solve_case();
  }
  return 0;
}
// 一坨屎
