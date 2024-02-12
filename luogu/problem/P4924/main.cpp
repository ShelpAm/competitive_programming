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
      : vec2_impl<value_t>(i, std::vector<value_t>(j))
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
auto&& operator>>(auto&& is, auto&& t)
{
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      is >> ele;
    }
  }
  else if constexpr (is_pair<decltype(t)>) {
    is >> t.first >> t.second;
  }
  else {
    is >> t;
  }
  return is;
}
void rotate_f(auto&& v, size_t x, size_t y, long long r)
{
  --x, --y;
  vec2uz const copy{v};
  for (long long i = -r; i != r + 1; ++i) {
    for (long long j = -r; j != r + 1; ++j) {
      v[x + i][y + j] = copy[x - j][y + i];
    }
  }
}
void rotate_f__(auto&& v, size_t x, size_t y, long long r)
{
  --x, --y;
  vec2uz const copy{v};
  for (long long i = -r; i != r + 1; ++i) {
    for (long long j = -r; j != r + 1; ++j) {
      v[x + i][y + j] = copy[x + j][y - i];
    }
  }
}
void solve_case()
{
  size_t n{};
  size_t m{};
  std::cin >> n >> m;
  std::vector<std::array<size_t, 4>> op(m);
  std::cin >> op;

  vec2uz v(n, n);
  for (size_t i{}; i != n; ++i) {
    for (size_t j{}; j != n; ++j) {
      v[i][j] = n * i + j + 1;
    }
  }

  for (auto const& e: op) {
    if (e[3] == 1) {
      rotate_f__(v, e[0], e[1], e[2]);
      // rotate(e[0], e[1], e[2]);
      // rotate(e[0], e[1], e[2]);
    }
    else {
      rotate_f(v, e[0], e[1], e[2]);
    }
  }
  // print(new_mat);
  print(v);
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
