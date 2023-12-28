#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <ranges>
#include <string_view>
#include <vector>

// configs
using ::std::size_t;
void debug(std::string_view const& sv, auto&& t)
{
#ifdef DEBUG
  std::cout << sv << ": " << t << '\n';
#endif
}
void solve_case()
{
  size_t n{};
  size_t t{};
  std::cin >> n >> t;
  std::vector<size_t> a(n);
  std::vector<bool> affordable(n, true);
  for (auto&& e: a) {
    std::cin >> e;
  }
  size_t sum{std::accumulate(a.begin(), a.end(), 0UZ)};

  size_t num{};
  while (true) {
    debug("sum", sum);
    if (t >= sum) {
      num += t / sum * n;
      t %= sum;
    }
    else {
      for (size_t i{}; auto&& e: a) {
        if (t >= e) {
          t -= e;
          ++num;
        }
        else {
          if (affordable[i]) {
            affordable[i] = false;
            sum -= e;
            --n;
          }
        }
        ++i;
      }
      if (sum == 0) {
        break;
      }
    }
  }
  std::cout << num;
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
