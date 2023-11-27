#include <array>
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
long long find_first(std::string_view const& s, std::string_view const& p)
{
  auto i{s.find(p)};
  return i == std::string::npos ? -1LL : static_cast<long long>(i);
}
long long find_last(std::string_view const& s, std::string_view const& p)
{
  auto i{s.rfind(p)};
  return i == std::string::npos ? -1LL : static_cast<long long>(i);
  // auto i{s.find(p)};
  // decltype(i) last_pos{i};
  // while (i != std::string::npos) {
  //   last_pos = i;
  //   i = s.find(p, i + p.size());
  // }
  // return last_pos == std::string::npos ? -1LL
  //                                      : static_cast<long long>(last_pos);
}
void solve_case()
{
  std::string s;
  std::string s1;
  std::string s2;
  std::getline(std::cin, s, ',');
  std::getline(std::cin, s1, ',');
  std::getline(std::cin, s2);

  auto i{find_first(s, s1)};
  auto j{find_last(s, s2)};
  if (i != -1 && j != -1) {
    i += static_cast<long long>(s1.size()) - 1;
    if (i < j) {
      std::cout << j - i - 1;
    }
    else {
      std::cout << -1LL;
    }
  }
  else {
    std::cout << -1LL;
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
