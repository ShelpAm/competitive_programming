#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <set>
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
void t(size_t& i)
{
  i = i == 0 ? 1 : 0;
}
void solve_case()
{
  auto n{read<size_t>()};
  auto m{read<size_t>()};
  std::vector<size_t> v(n);
  std::set<size_t> operated{};
  for (size_t i{}; i != n; ++i) {
    std::cin >> v[i];
  }
  size_t x{};
  for (size_t i{}; i != m; ++i) {
    std::cin >> x;
    if (x != 0) {
      for (size_t j{1}; j < n; ++j) {
        auto should_t{x * j};
        if (!operated.contains(should_t)) {
          t(v[should_t]);
          operated.emplace(should_t);
        }
      }
    }
    else {
      if (!operated.contains(x)) {
        t(v[x]);
        operated.emplace(0);
      }
    }
  }
  std::cout << std::ranges::count(v, 1);
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
