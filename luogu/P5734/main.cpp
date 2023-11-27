#include <array>
#include <cstddef>
#include <cstdio>
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
void solve_case()
{
  size_t q{};
  std::string s;
  std::cin >> q >> s;
  for (size_t i{}; i != q; ++i) {
    size_t option{};
    std::cin >> option;
    if (option == 1) {
      std::string str{};
      std::cin >> str;
      s += str;
      std::cout << s << '\n';
    }
    else if (option == 2) {
      size_t a{};
      size_t b{};
      std::cin >> a >> b;
      s = s.substr(a, b);
      std::cout << s << '\n';
    }
    else if (option == 3) {
      size_t a{};
      std::string str;
      std::cin >> a >> str;
      s.insert(a, str);
      std::cout << s << '\n';
    }
    else if (option == 4) {
      std::string str;
      std::cin >> str;
      auto pos{s.find(str)};
      std::cout << (pos != std::string::npos ? static_cast<long long>(pos)
                                             : -1LL)
                << '\n';
    }
  }
}
int main()
{
  // freopen64("output.txt", "w", stdout);
  auto n{1UZ};
  // n = read<size_t>();
  for (size_t i{}; i != n; ++i) {
    solve_case();
  }
  return 0;
}
