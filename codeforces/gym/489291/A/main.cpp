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
  size_t n{};
  std::cin >> n;
  std::vector<size_t> l(n);
  std::vector<size_t> r(n);
  for (size_t i{}; i != n; ++i) {
    char c{};
    std::cin >> l[i] >> c >> r[i];
    auto m = (l[i] + r[i]) % 4;
    if (m == 1 || m == 2) {
      std::swap(l[i], r[i]);
    }
  }
  bool ends{};
  size_t ending{};
  size_t li{};
  size_t ri{};
  bool first{true};

  auto check{[&first, &ends, &ending, &l, &r](size_t i, size_t j, size_t li,
                                              size_t ri) {
    if (i == 11 && j == 11) {
      return false;
    }
    if (!first && (i < li || j < ri)) {
      return false;
    }
    if (ends) {
      return i == l[ending] && j == r[ending];
    }
    return true;
  }};

  for (size_t i{}; i != n; ++i) {
    if (!check(l[i], r[i], li, ri)) {
      std::cout << "error " << i + 1;
      return;
    }

    if (first) {
      first = false;
    }

    if (l[i] == 11 || r[i] == 11) {
      ends = true;
      ending = i;
    }

    li = l[i];
    ri = r[i];
  }

  std::cout << "ok";
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
