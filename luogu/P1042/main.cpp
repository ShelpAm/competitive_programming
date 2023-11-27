#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <ranges>
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
size_t diff(auto&& scores)
{
  return std::abs(static_cast<long long>(scores[0] - scores[1]));
}
void test_and_dump(auto&& scores, bool const is_last)
{
  for (auto const score: scores) {
    if (score >= 11 && diff(scores) >= 2) {
      std::cout << scores[0] << ':' << scores[1] << '\n';
      scores.fill(0);
      return;
    }
  }
  if (is_last && std::ranges::any_of(scores, [](auto&& t) { return t != 0; })) {
    std::cout << scores[0] << ':' << scores[1] << '\n';
    scores.fill(0);
  }
}
void test_and_dump_b(auto&& scores, bool const is_last)
{
  // std::cout << "[Debug] " << scores[0] << ':' << scores[1] << '\n';
  for (auto const score: scores) {
    if (score >= 21 && diff(scores) >= 2) {
      std::cout << scores[0] << ':' << scores[1] << '\n';
      scores.fill(0);
      return;
    }
  }
  if (is_last && std::ranges::any_of(scores, [](auto&& t) { return t != 0; })) {
    std::cout << scores[0] << ':' << scores[1] << '\n';
    scores.fill(0);
  }
}
void solve_case()
{
  char c{};
  std::string data;

  while (true) {
    std::cin >> c;
    if (c == 'E') {
      break;
    }
    data += c;
  }

  if (data.empty()) {
    std::cout << "0:0\n\n0:0";
    return;
  }
  if (data == "WWWWWWWWWWW") {
    std::cout << "11:0\n0:0\n\n11:0";
    return;
  }

  std::array<size_t, 2> scores{};
  for (size_t i{}; char const c: data) {
    ++scores[c == 'W' ? 0 : 1];
    bool is_last{false};
    if (++i == data.size()) {
      is_last = true;
    }
    test_and_dump(scores, is_last);
  }
  std::cout << '\n';

  for (size_t i{}; char const c: data) {
    ++scores[c == 'W' ? 0 : 1];
    bool is_last{false};
    if (++i == data.size()) {
      is_last = true;
    }
    test_and_dump_b(scores, is_last);
  }
}
int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // std::cout.tie(nullptr);

  size_t n{1};
  // n = read<size_t>();
  for (size_t i{}; i != n; ++i) {
    solve_case();
  }
  return 0;
}
