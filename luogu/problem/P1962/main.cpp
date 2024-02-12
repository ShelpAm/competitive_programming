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
namespace an {
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
} // namespace an
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
struct vec2 {
  size_t& operator[](size_t const idx) { return eles[idx]; }
  std::array<size_t, 2> eles{};
};
vec2 operator+(vec2 v1, vec2 v2)
{
  return vec2{v1[0] + v2[0], v1[1] + v2[1]};
}
vec2 operator*(vec2 v1, size_t const i)
{
  return vec2{v1[0] * i, v1[1] * i};
}
vec2 operator*(size_t const i, vec2 v1)
{
  return vec2{v1[0] * i, v1[1] * i};
}
struct mat2 {
  vec2& operator[](size_t const idx) { return rows[idx]; }
  std::array<vec2, 2> rows{};
};
mat2 operator*(mat2& lhs, mat2& rhs)
{
  mat2 m{};
  for (size_t i{}; i != 2; ++i) {
    for (size_t j{}; j != 2; ++j) {
      m[i] = m[i] + lhs[i][j] * rhs[j];
    }
  }
  return m;
}
mat2 operator%(mat2 lhs, size_t const mod)
{
  for (size_t i{}; i != 2; ++i) {
    for (size_t j{}; j != 2; ++j) {
      lhs[i][j] %= mod;
    }
  }
  return lhs;
}
std::ostream& operator<<(std::ostream& os, mat2 const& m)
{
  for (auto&& row: m.rows) {
    for (auto&& ele: row.eles) {
      std::cout << ele << ' ';
    }
    os << '\n';
  }
  return os;
}
auto my_pow(auto a, std::size_t n, size_t const modulus) -> decltype(a)
{
  auto extra = mat2{vec2{1, 0}, {0, 1}};
  while (n > 1) {
    if ((n & 1) == 1) {
      extra = extra * a;
      extra = extra % modulus;
      n -= 1;
    }
    else {
      a = a * a;
      a = a % modulus;
      n /= 2;
    }
  }
  return (a * extra) % modulus;
}
void solve_case()
{
  mat2 a{vec2{1, 1}, {0, 0}};
  mat2 b{vec2{0, 1}, {1, 1}};

  size_t n{};
  std::cin >> n;
  if (n == 1) {
    std::cout << 1;
    return;
  }
  if (n == 2) {
    std::cout << 1;
    return;
  }
  auto res{my_pow(b, n - 2, 1e9 + 7)};
  res = a * res;
  res = res % (1e9 + 7);
  std::cout << res[0][1];
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
