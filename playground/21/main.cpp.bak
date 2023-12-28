#include <array>
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
  freopen("/home/shelpam/template/build/input", "r", stdin);
  cin >> n >> m >> k;
  vector<vector<bool>> map_broken(n, vector<bool>(m));
  vector<bool> row_broken(n);
  vector<bool> column_broken(m);
  for (size_t i{}; i != k; ++i) {
    size_t x, y;
    cin >> x >> y;
    row_broken[--x] = true;
    column_broken[--y] = true;
  }
  for (size_t i{}; i != n; ++i) {
    for (size_t j{}; j != m; ++j) {
      map_broken[i][j] = row_broken[i] || column_broken[j];
    }
  }

  size_t cnt{};
  for (size_t i{}; i != n; ++i) {
    for (size_t j{}; j != m; ++j) {
      if (!map_broken[i][j]) {
        ++cnt;
        dfs(map_broken, i, j);
      }
    }
  }
  cout << cnt;
  return 0;
}
