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
  vec2(size_t const i, size_t const j): impl::vec2<value_t>(i, std::vector<value_t>(j)) {}
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
void debug([[maybe_unused]] std::string_view const& sv, [[maybe_unused]] auto&& t)
{
#ifdef DEBUG
  std::cout << sv << ": " << t << '\n';
#endif
}
void solve_case()
{
  size_t n{};
  std::cin >> n;
  std::array<size_t, 3> a{1, 1, 1};
  for (size_t i{}; i != n - 1; ++i) {
    if (a[0] == a[1] && a[0] == a[2]) {
      a[1] = a[0] = 1;
      ++a[2];
    }
    else if (a[0] == a[1]) {
      a[0] = 1;
      ++a[1];
    }
    else {
      for (size_t j{}; j + 1 != 3; ++j) {
        if (a[j] < a[j + 1]) {
          ++a[j];
          break;
        }
      }
    }
  }

  std::array<size_t, 20> s{1, 1};
  for (size_t i{2}; i != s.size(); ++i) {
    s[i] = 10 * s[i - 1] + 1;
  }
  size_t res{};
  for (size_t i{}; i != a.size(); ++i) {
    res += s[a[i]];
  }
  std::cout << res;
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
