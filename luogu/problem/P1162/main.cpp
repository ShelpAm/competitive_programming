#include <bits/stdc++.h>
namespace impl {
  template<typename value_t> using vec2 = std::vector<std::vector<value_t>>;
} // namespace impl
template<size_t i, size_t j, typename value_t> using arr2 = std::array<std::array<value_t, j>, i>;
template<size_t i, size_t j> using arr2uz = arr2<i, j, size_t>;
template<typename value_t> class vec2 : public impl::vec2<value_t> {
public:
  vec2(size_t const i, size_t const j): impl::vec2<value_t>(i, std::vector<value_t>(j)) {}
};
using vec2uz = vec2<size_t>;
auto&& operator>>(auto&& is, auto&& t)
{
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      is >> ele;
    }
  }
  else {
    is >> t;
  }
  return is;
}
size_t n{};
void dfs(auto&& v, size_t const i, size_t const j)
{
  if (i == -1UZ || i == n || j == -1UZ || j == n) {
    return;
  }
  if (v[i][j] == 1 || v[i][j] == 3) {
    return;
  }

  v[i][j] = 3;

  dfs(v, i + 1, j);
  dfs(v, i - 1, j);
  dfs(v, i, j + 1);
  dfs(v, i, j - 1);
}
void solve_case()
{
  std::cin >> n;
  vec2uz v(n, n);
  std::cin >> v;

  for (size_t i{}; i != n; ++i) {
    dfs(v, 0, i);
    dfs(v, n - 1, i);
  }
  for (size_t i{}; i != n; ++i) {
    dfs(v, i, 0);
    dfs(v, i, n - 1);
  }

  // for (auto&& row: v) {
  //   for (auto&& e: row) {
  //     std::cout << e << ' ';
  //   }
  //   std::cout << '\n';
  // }

  for (auto&& row: v) {
    for (auto&& e: row) {
      if (e == 0) {
        std::cout << "2 ";
      }
      else if (e == 1) {
        std::cout << "1 ";
      }
      else if (e == 3) {
        std::cout << 0 << ' ';
      }
    }
    std::cout << '\n';
  }
}
int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve_case();
  return 0;
}
