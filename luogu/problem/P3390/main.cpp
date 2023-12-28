#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <string_view>
#include <vector>

// configs
using ::std::size_t;

namespace impl {
  template<typename value_t> using vec2 = std::vector<std::vector<value_t>>;
  template<typename T> concept is_pair = requires(T t) {
    t.first;
    t.second;
  };
} // namespace impl
template<size_t i, size_t j, typename value_t> using arr2 = std::array<std::array<value_t, j>, i>;
template<size_t i, size_t j> using arr2uz = arr2<i, j, size_t>;
template<size_t i, size_t j> using arr2ll = arr2<i, j, long long>;
namespace xxx {
  template<typename value_t> class vec2 : public impl::vec2<value_t> {
  public:
    vec2(size_t const i, size_t const j): impl::vec2<value_t>(i, std::vector<value_t>(j)) {}
  };
  using vec2uz = vec2<size_t>;
  using vec2ll = vec2<long long>;
} // namespace xxx
auto&& operator>>(auto&& is, auto&& t)
{
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      is >> ele;
    }
  }
  else if constexpr (impl::is_pair<decltype(t)>) {
    is >> t.first >> t.second;
  }
  else {
    is >> t;
  }
  return is;
}
auto&& operator<<(auto&& os, auto&& t)
{
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      os << ele << ' ';
    }
    os << '\n';
  }
  else if constexpr (impl::is_pair<decltype(t)>) {
    os << t.first << ": " << t.second << ", ";
  }
  else {
    os << t << ' ';
  }
  return os;
}
void debug([[maybe_unused]] std::string_view const& sv, [[maybe_unused]] auto&& t)
{
#ifdef DEBUG
  std::cout << sv << ": " << t << '\n';
#endif
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
  auto& operator[](size_t const idx) { return rows[idx]; }
  std::vector<vec2> rows{};
};
mat2 operator*(mat2& lhs, mat2& rhs)
{
  mat2 m{};
  for (size_t i{}; i != m.rows.size(); ++i) {
    for (size_t j{}; j != m.rows[0].eles.size(); ++j) {
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
  size_t n{};
  size_t k{};
  std::cin >> n >> k;
  mat2 m;
  for (size_t i{}; i != n; ++i) {
    for (size_t j{}; j != n; ++j) {
    }
  }
}
int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // std::cout.tie(nullptr);

  size_t t{1};
  // std::cin >> t;
  for (size_t i{}; i != t; ++i) {
    solve_case();
  }
  return 0;
}
