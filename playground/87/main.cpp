#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> PII;

void solve()
{
  ll n, q;
  cin >> n >> q;
  vector<ll> a(n + 1), b(n + 1);
  vector<vector<ll>> f(n + 1, vector<ll>(21)), sf(n + 1, vector<ll>(22));
  vector<ll> adj[n + 1];
  for (ll i = 1; i <= n; i++) {
    cin >> a[i] >> b[i];
  }
  stack<PII> s;
  for (ll i = n; i >= 1; i--) {
    while (!s.empty() && s.top().first <= a[i]) {
      s.pop();
    }
    if (s.empty())
      adj[0].push_back(i);
    else
      adj[s.top().second].push_back(i);
    s.push({a[i], i});
  }

  auto dfs = [&](auto self, ll x, ll fa) -> int {
    f[x][0] = x, f[x][1] = fa;
    sf[x][0] = b[x], sf[x][1] = b[x] + b[fa];
    for (ll i = 2; i <= 21; i++) {
      f[x][i] = f[f[x][i - 1]][i - 1];
      sf[x][i] = sf[x][i - 1] + sf[f[x][i - 1]][i - 1];
    }
    for (auto i : adj[x]) {
      self(self, i, x);
    }
  };

  auto ask = [&](ll x, ll sum) {
    for (int i = 21; i >= 0; i--) {
      if (sum - sf[x][i] > 0) {
        sum -= sf[x][i];
        x = f[f[x][i]][1];
      }
    }
    return x;
  };

  b[0] = 2e9;
  dfs(dfs, 0, 0);

  while (q--) {
    ll x, sum;
    cin >> x >> sum;
    cout << ask(x, sum) << '\n';
  }
}

signed main()
{
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  ll T = 1;
  // cin >> T;
  while (T--)
    solve();
  return 0;
}
