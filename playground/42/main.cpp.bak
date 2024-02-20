#include <bits/stdc++.h>
using namespace std;
int main()
{
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  vector<vector<char>> a(n, vector<char>(m));
  for (auto& e: a)
    for (auto& w: e)
      cin >> w;

  size_t cnt{};
  auto check{[&](int i, int l, int r) {
    for (int len = 3; len <= r - l + 1; len += 2) {
      if (len / 2 > i) {
        break;
      }
      for (int j = l; j + len - 1 != r + 1; ++j) {
        auto const mid{(2 * j + len - 1) / 2};
        //         cout<<i<<' '<<mid<<'\n';
        bool ok{true};
        for (int width = 0; width <= len / 2; ++width) {
          if (a[i - len / 2 + width][mid + width] == '.'
              || a[i - len / 2 + width][mid - width] == '.') {
            ok = false;
            break;
          }
        }
        if (ok) {
          ++cnt;
        }
      }
    }
  }};

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
      check(i, l, r - 1);
      l = r;
    }
  }

  cout << cnt;
}
