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
template<typename value_t> class vec2 : public impl::vec2<value_t> {
public:
  vec2(size_t const i, size_t const j): vec2<value_t>(i, std::vector<value_t>(j)) {}
};
using vec2uz = vec2<size_t>;
using vec2ll = vec2<long long>;
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
void debug(std::string_view const& sv, auto&& t)
{
#ifdef DEBUG
  std::cout << sv << ": " << t << '\n';
#endif
}
void solve_case()
{
  size_t m{};
  size_t n{};
  std::cin >> m >> n;
  std::vector<size_t> school(m);
  std::vector<size_t> evaluated(n);
  std::cin >> school >> evaluated;

  if (m == 1) {
    size_t res{};
    for (auto const student: evaluated) {
      res += student > school[0] ? student - school[0] : school[0] - student;
    }
    std::cout << res;
    return;
  }

  std::ranges::sort(school);

  size_t sum{};
  for (auto const student: evaluated) {
    size_t l{};
    size_t r{school.size() - 1};
    while (l < r) {
      size_t m{(l + r + 1) / 2};
      if (school[m] < student) {
        l = m;
      }
      else if (school[m] > student) {
        r = m - 1;
      }
      else {
        l = r = m;
      }
    }
    sum += std::ranges::min(
        std::abs(static_cast<long long>(school[l]) - static_cast<long long>(student)),
        std::abs(static_cast<long long>(school[l + 1]) - static_cast<long long>(student)));
    // std::cout << school[l] << ' ' << school[l + 1] << ' ' << student << '\n';
  }
  std::cout << sum;
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
