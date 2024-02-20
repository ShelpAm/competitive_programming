#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cstddef>
#include <deque>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#ifdef __cpp_concepts
#include <ranges>
#endif

using namespace std;
int main()
{
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  vector<vector<char>> a(n, vector<char>(m));
  for (auto& e: a) {
    for (auto& w: e) {
      cin >> w;
    }
  }

  std::vector<map<int, int>> lines(n);
  for (int i = 0; i != n; ++i) {
    int l{}, r{};
    while (l != m && r != m) {
      while (l != m && a[i][l] == '.') {
        ++l;
      }
      if (l == m) {
        break;
      }
      r = l;
      while (r != m && a[i][r] == '*') {
        ++r;
      }
      lines[i].insert({l, r - 1});
      // check(i, l, r - 1);
      l = r;
    }
  }

  // for (auto& line: lines) {
  //   for (auto& [l, r]: line) {
  //     cout << l << ' ' << r << '\n';
  //   }
  // }

  size_t cnt{};
  auto check{[&](int i, int j) {
    for (int d{1}; d + i < n; ++d) {
      if (i + d == -1 || j + d == -1 || j - d == -1 || a[i + d][j + d] != '*'
          || a[i + d][j - d] != '*') {
        return;
      }
      auto it{prev(lines[i + d].upper_bound(j - d))};
      if (it != lines[i + d].end() && it->second >= j + d) {
        ++cnt;
      }
    }
  }};

  for (int i{}; i != n; ++i) {
    for (int j{}; j != m; ++j) {
      if (a[i][j] == '*') {
        check(i, j);
      }
    }
  }

  cout << cnt;
}
