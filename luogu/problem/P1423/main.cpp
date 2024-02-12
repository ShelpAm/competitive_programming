#include <array>
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
auto my_pow(double a, std::size_t n)
{
  if (n == 0) {
    return 1.0;
  }
  decltype(a) extra = 1.0;
  while (n != 1) {
    if ((n & 1) == 1) {
      extra *= a;
      n -= 1;
    }
    else {
      a *= a;
      n /= 2;
    }
  }
  return a * extra;
}
void solve_case()
{
  input_value<double> s;
  constexpr auto a1{2};
  constexpr auto q{0.98};
  for (auto&& i: std::ranges::views::iota(0, 10000)) {
    auto sn{(1 - my_pow(q, i)) / (1 - q) * a1};
    if (sn > s.value()) {
      std::cout << i;
      break;
    }
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
