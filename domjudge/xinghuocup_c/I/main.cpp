#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <map>
#include <numeric>
#include <ranges>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// configs
using ::std::size_t;

auto solve_case()
{
  size_t n, h;
  std::cin >> n >> h;
  std::vector<std::pair<long, long>> a(n);
  for (auto&& [d, r]: a) {
    std::cin >> d >> r;
  }
  std::vector<size_t> res(n);
  std::iota(res.begin(), res.end(), 0);
  std::ranges::sort(res, [&](auto&& lhs, auto&& rhs) {
    auto dl{a[lhs].second - a[lhs].first};
    auto dr{a[rhs].second - a[rhs].first};
    if (dl > 0 && dr > 0) {
      if (a[lhs].first == a[rhs].first) {
        return dl == dr;
      }
      return a[lhs].first <= a[rhs].first;
    }
    return dl;
  });
  for (auto const i: res) {
    std::cout << i + 1 << ' ';
  }
}
int main()
{
  solve_case();
  return 0;
}
