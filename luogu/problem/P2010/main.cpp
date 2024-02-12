#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <set>
#include <string_view>
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
bool is_leap_year(size_t const& year)
{
  return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}
// bool is_leap_year(std::string const& year)
// {
//   return is_leap_year(std::stoi(year));
// }
struct my_time_t {
  explicit my_time_t(std::string const& s)
      : year(std::stoi(s.substr(0, 4))), month(std::stoi(s.substr(4, 2))),
        day(std::stoi(s.substr(6, 2)))
  {}
  size_t year;
  size_t month;
  size_t day;
};
bool is_valid_date(std::string const& s)
{
  std::set<size_t> _31{1, 3, 5, 7, 8, 10, 12};
  my_time_t time(s);
  if (time.month > 12 || time.month == 0 || time.day > 31 || time.day == 0) {
    return false;
  }
  if (_31.contains(time.month)) {
    return time.day <= 31;
  }
  if (time.month == 2) {
    if (is_leap_year(time.year)) {
      return time.day <= 29;
    }
    return time.day <= 28;
  }
  return time.day <= 30;
}
bool is_palindrome(size_t const n)
{
  auto s{std::to_string(n)};
  for (size_t i{}; i != (s.size() + 1) / 2; ++i) {
    if (s[i] != s[s.size() - i - 1]) {
      return false;
    }
  }
  return true;
}
std::string construct_palindrome(std::string_view const& s)
{
  std::string result(s.size() * 2, '\0');
  std::ranges::copy(s, result.begin());
  std::ranges::reverse_copy(s, result.begin() + s.size());
  // result.reserve(s.size() * 2);
  // for (size_t i{}; i != s.size(); ++i) {
  //   result[result.size() - i - 1] = s[i];
  // }
  return result;
}
void solve_case()
{
  size_t begin{};
  size_t end{};
  std::cin >> begin >> end;
  size_t count{};
  // for (size_t const i: std::ranges::views::iota(begin, end + 1)) {
  for (size_t const year:
       std::ranges::views::iota(my_time_t(std::to_string(begin)).year,
                                my_time_t(std::to_string(end)).year + 1)) {
    // if (is_palindrome(i)) {
    // }
    auto date = construct_palindrome(std::to_string(year));
    if (date > std::to_string(end)) {
      continue;
    }
    if (is_valid_date(date)) {
      // std::cout << date << '\n';
      ++count;
    }
  }
  std::cout << count;
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
