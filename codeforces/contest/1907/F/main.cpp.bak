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
  size_t n;
  std::cin >> n;
  std::vector<size_t> a(n);
  std::cin >> a;
  std::vector<size_t> increasing;
  std::vector<size_t> decreasing;
  for (size_t i{}; i + 1 != n; ++i) {
    if (a[i + 1] > a[i]) {
      increasing.emplace_back(i);
    }
    if (a[i + 1] < a[i]) {
      decreasing.emplace_back(i);
    }
  }

  if (increasing.size() > 1 && decreasing.size() > 1) {
    std::cout << -1 << '\n';
    return;
  }

  if ((decreasing.size() == 0 && a.front() < a.back())
      || (increasing.size() == 0 && a.front() > a.back())) {
    std::cout << -1 << '\n';
    return;
  }

  if (decreasing.size() == 0) {
    std::cout << 0 << '\n';
    return;
  }
  if (increasing.size() == 0) {
    std::cout << decreasing.size() << '\n';
    return;
  }

  if (decreasing.size() == 1) {
    auto i{decreasing.front()};
    std::cout << std::ranges::min(n - 1 - i, i + 1) << '\n';
  }
  else {
    auto i{increasing.front()};
    std::cout << std::ranges::min(n - 1 - i, i + 1) + 1 << '\n';
  }
}
int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // std::cout.tie(nullptr);

  size_t t{1};
  std::cin >> t;
  for (size_t i{}; i != t; ++i) {
    solve_case();
  }
  return 0;
}
