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
void solve_case()
{
  size_t r{};
  size_t c{};
  size_t k{};
  std::cin >> r >> c >> k;
  vec2<char> v(r, c);
  std::cin >> v;
  size_t cnt{};

  if (k == 1) {
    for (size_t i{}; i != r; ++i) {
      for (size_t j{}; j != c; ++j) {
        if (v[i][j] == '.') {
          ++cnt;
        }
      }
    }
    std::cout << cnt;
    return;
  }

  for (size_t i{}; i != r; ++i) {
    for (size_t j{}; j != c; ++j) {
      // Row-test
      bool row_test{[&]() {
        for (size_t t{}; t != k; ++t) {
          if (i + t >= r || v[i + t][j] == '#') {
            return false;
          }
        }
        return true;
      }()};
      if (row_test) {
        ++cnt;
      }
      // Column-test
      bool col_test{[&]() {
        for (size_t t{}; t != k; ++t) {
          if (j + t >= c || v[i][j + t] == '#') {
            return false;
          }
        }
        return true;
      }()};
      if (col_test) {
        ++cnt;
      }
    }
  }
  std::cout << cnt;
}
int main()
{
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
