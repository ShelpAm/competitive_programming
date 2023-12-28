#include <bits/stdc++.h>
using namespace std;
int main()
{
  size_t N;
  cin >> N;
  while (N--) {
    size_t n;
    cin >> n;
    string s;
    cin >> s;
    vector<vector<size_t>> G(n);
    for (size_t i{}; i != n - 1; ++i) {
      size_t u, v;
      cin >> u >> v;
      --u, --v;
      G[u].emplace_back(v);
      G[v].emplace_back(u);
    }
    bool found{};
    for (size_t i{}; i != n; ++i) {
      size_t cnt{1};
      for (auto const next: G[i]) {
        if (s[next] == s[i]) {
          ++cnt;
        }
      }
      if (cnt >= 3) {
        found = true;
        break;
      }
    }
    cout << (!found ? "YES\n" : "NO\n");
  }
  return 0;
}
