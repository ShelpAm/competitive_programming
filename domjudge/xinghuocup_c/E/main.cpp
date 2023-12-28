#include <array>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
constexpr array<pair<long long, long long>, 4> dirs{make_pair(-1, 0), {0, -1}, {1, 0}, {0, 1}};
long long n, m;
size_t k;
void dfs(vector<vector<bool>>& map_broken, long long const i, long long const j)
{
  map_broken[i][j] = true;
  for (auto const& [x, y]: dirs) {
    if (i + x == -1 || j + y == -1 || i + x == n || j + y == m) {
      continue;
    }
    if (map_broken[i + x][j + y]) {
      continue;
    }
    dfs(map_broken, i + x, j + y);
  }
}
int main()
{
  // freopen("/home/shelpam/template/build/input", "w", stdout);
  std::ios::sync_with_stdio(false);
  cin.tie(nullptr);
  size_t n{static_cast<size_t>(1e5)};
  size_t m{static_cast<size_t>(1e5)};
  size_t k{static_cast<size_t>(1e5 / 2 - 2)};
  cout << n << ' ' << m << ' ' << k << '\n';
  for (size_t i{1}; i != k + 1; ++i) {
    cout << 2 * i << ' ' << 2 * i << '\n';
  }
  return 0;
}
