#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;
int main()
{
    int n, q;
    cin >> n >> q;
    vector<int> c(n - 1);
    for (auto& e: c)
        cin >> e;

    int _len = log(n);
    vector<vector<int>> f(n - 1, vector<int>(_len));
    for (int i = 0; i != n - 1; ++i) {
        f[i][0] = c[i];
    }
    for (int l = 1; l <= _len; ++l) {
        for (int i = 0; i + (1 << l) < n; ++i) {
            f[i][l] = min(f[i][l - 1], f[i + (1 << (l - 1))][l - 1]);
        }
    }

    vector<vector<pair<int, int>>> adj(n - 1);
    for (int i = 0; i != q; ++i) {
        int u, v;
        cin >> u >> v;
        --v;
        int x = u, y = v;
        if (x > y) {
            swap(x, y);
        }
        int len = log(y - x + 1);
        adj[v].push_back({min(f[x][len], f[y - (1 << len)][len]), u});
    }

    vector<int> g(n);
    vector<bool> vis(n);
    for (int i = 0; i != n; ++i) {
        auto dfs = [&](auto self, int u) -> void {
            if (vis[u]) {
                return;
            }
            vis[u] = true;
            for (auto [w, v]: adj[u]) {
                self(self, v);
                g[u] = max(g[u], g[v] + w);
            }
        };
        dfs(dfs, i);
    }
    int ans = 0;
    for (auto e: g) {
        ans = max(ans, e);
        cout << e << '\n';
    }
    cout << ans;
}
