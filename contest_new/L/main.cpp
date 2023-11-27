#include <algorithm>
#include <array>
#include <cmath>
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
bool eq(double a, double b)
{
  return std::abs(a - b) < 0.0001;
}
double f(double a, double b, double c, double d)
{
  return a * 0.6 + b * 0.15 + c * 0.15 + d * 0.1;
}
bool test(double all, size_t p, double r)
{
  return p <= std::ceil(all * r);
}
void solve_case()
{
  size_t a, b, c, d;
  std::cin >> a >> b >> c >> d;
  std::vector<double> scores;
  auto n{read<size_t>()};
  size_t i, j, k, l;
  for (size_t i{}; i != n; ++i) {
    std::cin >> i >> j >> k >> l;
    scores.push_back(f(i, j, k, l));
  }
  auto my_score{f(a, b, c, d)};
  scores.push_back(my_score);
  std::ranges::sort(scores);
  auto p{std::ranges::find_if(
             scores, [my_score](double const t) { return eq(my_score, t); })
         - scores.begin()};
  char eee{};
  char fff{'Y'};
  if (test(n, p + 1, 0.05)) {
    eee = '1';
  }
  else if (test(n, p + 1, 0.15)) {
    eee = '2';
  }
  else if (test(n, p + 1, 0.3)) {
    eee = '3';
  }
  else {
    eee = 'N';
  }
  std::cout << eee << fff;
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
