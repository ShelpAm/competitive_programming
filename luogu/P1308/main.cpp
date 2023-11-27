#include <algorithm>
#include <array>
#include <cctype>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <string>
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
void to_lower(char& c)
{
  c = std::tolower(c);
}
void solve_case()
{
  std::string pattern;
  std::string src;
  std::cin >> pattern;
  std::cin.ignore(100, '\n');
  // std::getline(std::cin, pattern);
  std::getline(std::cin, src);
  src = ' ' + src;
  src += ' ';
  std::ranges::for_each(pattern, to_lower);
  std::ranges::for_each(src, to_lower);

  size_t first_pos{0x3f3f3f3f};
  size_t num_of_words{};
  for (size_t i{1}; i != src.size() - pattern.size(); ++i) {
    if (src[i - 1] == ' ' && src.substr(i, pattern.size()) == pattern
        && src[i + pattern.size()] == ' ') {
      if (first_pos == 0x3f3f3f3f) {
        first_pos = i - 1;
      }
      ++num_of_words;
    }
  }

  if (num_of_words == 0) {
    std::cout << -1LL;
  }
  else {
    std::cout << num_of_words << ' ' << first_pos;
  }
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
