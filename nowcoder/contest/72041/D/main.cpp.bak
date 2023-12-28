#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <string_view>
#include <unordered_map>
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
  std::cout << sv << ": " << t << std::endl;
#endif
}
constexpr size_t mod{998244353};
constexpr size_t factorial(size_t const x)
{
  size_t res{1};
  for (size_t i{1}; i != x; ++i) {
    res *= i;
  }
  return res;
}
constexpr size_t C(size_t const n, size_t const m, size_t const mod)
{
  return factorial(n) / factorial(m) / factorial(n - m);
}
void solve_case()
{
  size_t n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  std::unordered_map<char, std::vector<size_t>> pos;
  for (size_t i{}; i != s.size(); ++i) {
    pos[s[i]].emplace_back(i);
  }
  size_t m;
  std::cin >> m;
  size_t ans{};
  while (m--) {
    debug("m", m);
    char c1, c2;
    size_t len;
    std::cin >> c1 >> c2 >> len;
    for (auto const i: pos[c1]) {
      for (auto const j: pos[c2]) {
        if (j >= i + len) {
          ans = (ans + C(len - 2, j - i - 1, mod)) % mod;
        }
      }
    }
  }
  std::cout << ans;
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
