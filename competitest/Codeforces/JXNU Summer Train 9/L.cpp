#include <bits/stdc++.h>
using i64 = std::int_fast64_t;
auto main() -> int
{
  int n;
  std::cin >> n;
  std::vector<i64> x(n);
  std::vector<i64> y(n);
  for (int i{}; i != n; ++i) {
    std::cin >> x[i] >> y[i];
  }

  for (int i{}; i != n; ++i) {
    for (int j{i + 1}; j != n; ++j) {
      auto const dx{x[i] - x[j]}, dy{y[i] - y[j]};
      std::unordered_map<i64, >;
      for (int k{}; k != n; ++k) {
        if (k == i || k == j) {
          continue;
        }
        if () {
        }
      }
    }
  }
}
