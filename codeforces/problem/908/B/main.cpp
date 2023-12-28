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
  std::cout << sv << ": " << t << '\n';
#endif
}
void solve_case()
{
  long long n{};
  long long m{};
  std::cin >> n >> m;
  vec2<char> map(n, m);
  std::cin >> map;
  long long x_{};
  long long y_{};
  for (long long i{}; i != n; ++i) {
    for (long long j{}; j != m; ++j) {
      if (map[i][j] == 'S') {
        x_ = i;
        y_ = j;
        break;
      }
    }
  }
  std::string instructions;
  std::cin >> instructions;
  std::unordered_map<char, std::pair<long long, long long>> mapping;
  std::array<std::pair<long long, long long>, 4> dirs{std::make_pair(-1, 0), std::make_pair(1, 0),
                                                      std::make_pair(0, -1), std::make_pair(0, 1)};
  std::string_view const original{"0123"};
  std::string current{original};
  size_t ans{};
  do {
    long long x{x_};
    long long y{y_};
    for (size_t i{}; i != dirs.size(); ++i) {
      mapping[current[i]] = dirs[i];
    }
    for (auto const c: instructions) {
      x += mapping[c].first;
      y += mapping[c].second;
      if (x == -1 || x == n || y == -1 || y == m || map[x][y] == '#') {
        break;
      }
      if (map[x][y] == 'E') {
        ++ans;
        break;
      }
    }

    std::ranges::next_permutation(current);
  }
  while (current != original);
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
