#include <array>
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
bool is_substr_of(std::string_view const sub, std::string_view const src)
{
  size_t i{};
  size_t j{};
  size_t count{};
  while (j != src.size()) {
    if (sub[i] == src[j]) {
      ++i;
      if (i == sub.size()) {
        return true;
      }
    }
    else {
      ++count;
      if (count == 2) {
        return false;
      }
    }
    ++j;
  }
  return false;
}
bool is_different_by_one_char(std::string_view const lhs,
                              std::string_view const rhs)
{
  if (lhs.size() != rhs.size()) {
    return false;
  }
  size_t i{};
  size_t j{};
  size_t count{};
  while (j != rhs.size()) {
    if (lhs[i] != rhs[j]) {
      ++count;
    }
    ++i;
    ++j;
  }
  return count <= 1;
}
void solve_case()
{
  size_t n{};
  std::string t;
  std::cin >> n >> t;
  std::vector<size_t> v;
  for (size_t i{}; i != n; ++i) {
    std::string s;
    std::cin >> s;
    bool a{s == t};
    bool b{is_substr_of(s, t)};
    bool c{is_substr_of(t, s)};
    bool d{is_different_by_one_char(s, t)};
    if (s == t || is_substr_of(s, t) || is_substr_of(t, s)
        || is_different_by_one_char(s, t)) {
      v.push_back(i + 1);
    }
  }
  std::cout << v.size() << '\n';
  print(v);
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
