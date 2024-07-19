#include <bits/stdc++.h>
using namespace std;
#define int long long
constexpr int inf{static_cast<int>(1e17 + 7)};
bool chmin(int &a, int b)
{
  if (a > b) {
    a = b;
    return true;
  }
  return false;
}
bool chmax(int &a, int b)
{
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}
vector<int> dijkstra(int src, vector<vector<pair<int, int>>> const &adj)
{
  vector<int> dist(adj.size(), inf);
  vector<int> vis(adj.size());
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
  q.push({dist[src] = 0, src});
  while (!q.empty()) {
    auto [w, u]{q.top()};
    q.pop();
    if (vis[u]) {
      continue;
    }
    vis[u] = 1;
    for (auto [w, v] : adj[u]) {
      if (auto alt{dist[u] + w}; !vis[v] && chmin(dist[v], alt)) {
        q.push({alt, v});
      }
    }
  }
  return dist;
}
signed main()
{
  int a, b, c;
  cin >> a >> b >> c;
  int s1, s2, n, m;
  cin >> s1 >> s2 >> n >> m;
  --s1, --s2;
  vector<vector<pair<int, int>>> adj(n);
  for (int i{}; i != m; ++i) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    adj[u].push_back({1, v});
    adj[v].push_back({1, u});
  }
  auto d1{dijkstra(s1, adj)};
  auto d2{dijkstra(s2, adj)};
  auto dd{dijkstra(n - 1, adj)};
  int ans{inf};
  for (int i{}; i != n; ++i) {
    chmin(ans, dd[i] * (a + b - c) + d1[i] * a + d2[i] * b);
  }
  cout << (ans == inf ? -1 : ans);
}
#undef int
