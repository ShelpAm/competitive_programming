#include <bits/stdc++.h>
void solve()
{
    int n;
    std::cin >> n;
    std::vector<std::unordered_set<int>> g(n);
    for (int i{}; i != n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u;
        --v;
        g[u].insert(v);
        g[v].insert(u);
    }

    std::vector<int> is_leaf(n);
    for (int i{}; i != n; ++i) {
        is_leaf[i] = g[i].size() == 1;
    }

    for (int i{}; i != n; ++i) {
        if (is_leaf[i]) {
            for (auto const j : g[i]) {
                g[j].erase(i);
            }
        }
    }

    std::cout << (std::ranges::all_of(std::views::iota(0, n),
                                      [&](auto i) { return g[i].size() <= 2; })
                      ? "YES\n"
                      : "NO\n");
}
int main()
{
    int t{1};
    std::cin >> t;
    for (int i{}; i != t; ++i) {
        solve();
    }
}
