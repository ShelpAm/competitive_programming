#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>
using ::std::size_t;
void solve_case()
{
  size_t n{};
  std::cin >> n;
  std::vector<size_t> a(n);
  std::vector<size_t> b(n);
  for (size_t i{}; i != n; ++i) {
    std::cin >> a[i];
  }
  for (size_t i{}; i != n; ++i) {
    std::cin >> b[i];
  }
  std::vector<size_t> x(n + 1);
  std::vector<size_t> num_off(n);
  for (size_t i{}; i != n; ++i) {
    x[b[i]] = i;
  }
  for (size_t i{}; i != n; ++i) {
    ++num_off[(i - x[a[i]] + n) % n];
  }

  size_t ans{};
  for (size_t i{}; i != n; ++i) {
    ans = std::max(ans, num_off[i]);
  }
  std::cout << ans;
}
int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve_case();
  return 0;
}
