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
  std::vector<std::pair<long long, long long>> seg(n);
  std::cin >> seg;

  auto check{[&](long long const k) {
    long long ll{0};
    long long rr{0};
    for (auto const& [l, r]: seg) {
      ll = std::ranges::max(ll - k, l);
      rr = std::ranges::min(rr + k, r);
      // std::cout << "l, r: " << l << ' ' << r << ' ' << ll << ' ' << rr << '\n';
      if (ll > rr) {
        return false;
      }
    }
    return true;
  }};

  size_t l{0};
  size_t r{static_cast<size_t>(1e9)};
  while (l < r) {
    auto mid{(l + r) >> 1};
    if (check(mid)) {
      r = mid;
    }
    else {
      l = mid + 1;
    }
  }
  std::cout << l << '\n';
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
