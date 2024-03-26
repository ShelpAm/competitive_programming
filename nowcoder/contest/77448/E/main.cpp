#include <algorithm>
#include <climits>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using vi = vector<i64>;
using vvi = vector<vi>;
using pii = pair<i64, i64>;
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
    u64 n;
    cin >> n;
    vi color(n);
    vvi adj(n);
    for (auto& e: color) {
        cin >> e;
    }
    for (u64 i = 1; i != n; ++i) {
        u64 fa;
        cin >> fa;
        adj[fa - 1].push_back(i);
    }

    u64 ans = 0;
    vector<set<u64>> stars(n);
    vector<int_fast32_t> ugly(n);
    vi size(n);
    auto dfs = [&](auto self, u64 u) -> void {
        size[u] = 1;
        stars[u].insert(color[u]);
        for (auto v: adj[u]) {
            self(self, v);
            size[u] += size[v];
            if (ugly[v]) {
                ugly[u] = true;
            }
            if (ugly[u]) {
                continue;
            }
            if (stars[u].size() < stars[v].size()) {
                stars[u].swap(stars[v]);
            }
            stars[u].merge(stars[v]);
            if (stars[u].size() != size[u]) {
                ugly[u] = true;
            }
        }
        // cout << u << " ++\n";
        if (!ugly[u]) {
            ++ans;
        }
    };
    dfs(dfs, 0);
    cout << ans;
}
