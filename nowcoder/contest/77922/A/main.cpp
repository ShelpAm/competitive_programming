#include <algorithm>
#include <cassert>
#include <climits>
#include <cstddef>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using vi = vector<i64>;
using vvi = vector<vi>;
using pii = pair<i64, i64>;
using triplei = tuple<i64, i64, i64>;
constexpr i64 inf = 1e18;
void solve();
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i64 t = 1;
    // cin >> t;
    for (i64 tc = 0; tc != t; ++tc) {
        solve();
    }
}
void solve()
{
    u64 n, m;
    cin >> n >> m;
    vvi adj(n);
    for (u64 i = 0; i != m; ++i) {
        i64 u, v;
        cin >> u >> v;
        --u, --v;
        adj[v].push_back(u);
    }

    vi f(n);
    auto dfs = [&](auto self, u64 u, i64 p) -> void {
        if (f[u] != 0) {
            return;
        }
        for (auto v: adj[u]) {
            if (v != p) {
                self(self, v, u);
                f[u] = max(f[v] + 1, f[u]);
            }
        }
    };
    for (u64 i = 0; i != n; ++i) {
        dfs(dfs, i, -1);
    }
    for (auto e: f) {
        cout << e + 1 << '\n';
    }
}
