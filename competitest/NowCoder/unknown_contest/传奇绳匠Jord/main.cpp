#include <bits/stdc++.h>
using i64 = std::int_least64_t;
void solve();
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t{1};
    std::cin >> t;
    for (int i{}; i != t; ++i) {
        solve();
    }
}
void solve()
{
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> g(n);
    for (int i{}; i != m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int k;
    std::cin >> k;
    std::vector<int> a(k);
    for (auto &e : a) {
        std::cin >> e;
        --e;
    }

    std::vector<int> in(n);
    std::queue<int> q;
    q.push(a[0]);
    while (!q.empty()) {
        auto const u{q.front()};
        q.pop();
        in[u] = 1;
        for (auto const v : g[u]) {
            if (!in[v]) {
                q.push(v);
            }
        }
    }

    std::cout << (std::ranges::all_of(a, [&in](auto u) { return in[u]; })
                      ? "YES"
                      : "NO")
              << '\n';
}
