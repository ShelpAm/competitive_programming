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

template<size_t i, size_t j, typename value_type> using arr2
    = std::array<std::array<value_type, j>, i>;
template<size_t i, size_t j> using arr2uz = arr2<i, j, size_t>;
template<size_t i, size_t j> using arr2ll = arr2<i, j, long long>;
template<typename value_type> using vec2_impl = std::vector<std::vector<value_type>>;
template<typename value_t> class vec2 : public vec2_impl<value_t> {
public:
  vec2(size_t const i, size_t const j): vec2_impl<value_t>(i, std::vector<value_t>(j)) {}
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
size_t f(auto&& s, size_t const n, long long const i, long long const j)
{
  if (i < 0 && j < 0) {
    return s[i][j];
  }

  return s[i][j];
}
void solve_case()
{
  size_t n{};
  size_t q{};
  std::cin >> n >> q;
  vec2<char> p(n, n);
  std::cin >> p;

  vec2<size_t> s(n, n);
  for (size_t i{}; i != n; ++i) {
    for (size_t j{}; j != n; ++j) {
      s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
      if (p[i][j] == 'B') {
        ++s[i][j];
      }
    }
  }

  for (size_t i{}; i != q; ++i) {
    size_t a{};
    size_t b{};
    size_t c{};
    size_t d{};
    std::cin >> a >> b >> c >> d;
    // mapping 0 - n-1 to 1 - n
    std::cout << f(s, n, c, d) - f(s, n, a, b) << '\n';
  }
}
int main()
{
  debug("FUCK", "");
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // std::cout.tie(nullptr);

  size_t n{1};
  // std::cin >> n;
  for (size_t i{}; i != n; ++i) {
    solve_case();
  }
  return 0;
}
