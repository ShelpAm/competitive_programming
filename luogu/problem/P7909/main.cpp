#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <vector>

using ::std::size_t;

// constexpr bool debug{false};

template<typename T> T read()
{
  T tmp;
  std::cin >> tmp;
  return tmp;
}
template<typename T> class input_value {
public:
  input_value(): value_(read<T>()) {}
  input_value(T const& initial_value): value_(initial_value + read<T>()) {}
  operator T&() { return value(); }
  T& value() { return value_; }
private:
  T value_;
};
template<size_t i, size_t j, typename value_type> using arr2
    = std::array<std::array<value_type, j>, i>;
template<size_t i, size_t j> using arr2uz = arr2<i, j, size_t>;
template<size_t i, size_t j> using arr2ll = arr2<i, j, long long>;
template<typename value_type> using vec2_type
    = std::vector<std::vector<value_type>>;
template<typename value_type> class vec2 {
public:
  vec2(size_t const i, size_t const j): vec2_(i, std::vector<value_type>(j, {}))
  {}
  vec2_type<value_type> vec2_;
};
using vec2uz = vec2<size_t>;
using vec2ll = vec2<long long>;
void print(auto&& t)
{
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      print(ele);
    }
    std::cout << '\n';
  }
  else {
    std::cout << t << ' ';
  }
}
void solve_case()
{
  input_value<size_t> n;
  input_value<size_t> l;
  input_value<size_t> r;
  if (l / n != r / n) {
    std::cout << n - 1;
  }
  else {
    std::cout << r % n;
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