#include <bits/stdc++.h>
void A();
void D();
void J();
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t{1};
    // std::cin >> t;
    for (int i{}; i != t; ++i) {
        // A();
        D();
        // J();
    }
}

#define int long long
constexpr int inf = 1e18;
bool chmin(auto &x, auto y)
{
    if (x > y) {
        x = y;
        return true;
    }
    return false;
}
using PII = std::pair<int, int>;
void A()
{
    int n;
    std::cin >> n;
    std::vector<std::string> a(n);
    for (auto &e : a) {
        std::cin >> e;
    }
    std::vector<int> r(n), c(n);
    for (auto &e : r) {
        std::cin >> e;
    }
    for (auto &e : c) {
        std::cin >> e;
    }

    std::vector<std::vector<char>> ans(n, std::vector<char>(n, '0'));
    for (int i{}; i != n; ++i) {
        for (int j{}; j != n; ++j) {
            if (a[i][j] == '-') {
                ++r[i];
                ++c[j];
                ans[i][j] ^= 1;
            }
        }
    }

    if (std::accumulate(r.begin(), r.end(), 0LL) !=
        std::accumulate(c.begin(), c.end(), 0LL)) {
        std::cout << "No\n";
        return;
    }

    for (int i{}; auto e : r) {
        std::vector<int> idx(n);
        std::iota(idx.begin(), idx.end(), 0);
        std::sort(idx.begin(), idx.end(),
                  [&](auto i, auto j) { return c[i] > c[j]; });
        for (int j{}; j != e; ++j) {
            ans[i][idx[j]] ^= 1;
            if (c[idx[j]] == 0) {
                std::cout << "No\n";
                return;
            }
            --c[idx[j]];
        }
        ++i;
    }

    std::cout << "Yes\n";
    for (auto const &b : ans) {
        for (auto e : b) {
            std::cout << e;
        }
        std::cout << '\n';
    }
}
void D()
{
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<PII>> g(n);
    for (int i{}; i != m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        --u, --v;
        g[u].push_back({w, v});
        g[v].push_back({w, u});
    }

    std::set<std::vector<int>> s;
    std::vector<int> vis(n);
    std::vector<int> in;

    std::unordered_set<int> check_vis;
    auto check = [&](auto check, int u, int color) -> bool {
        // std::cout << "VISITING " << u << '\n';
        check_vis.insert(u);
        if (check_vis.size() == in.size()) {
            return true;
        }
        for (auto [w, v] : g[u]) {
            if (!check_vis.contains(v) && w == color && vis[v]) {
                if (check(check, v, color)) {
                    return true;
                }
            }
        }
        return false;
    };
    // vis[0] = vis[1] = vis[2] = vis[3] = 1;
    // in = {0, 1, 2, 3};
    // std::cout << check(check, in[0], 0) << '\n';
    // check_vis.clear();
    // std::cout << check(check, in[0], 1) << '\n';
    // check_vis.clear();
    // return;
    for (int i{}; i != n; ++i) {
        auto dfs = [&](auto dfs, int u) -> void {
            int t{};
            vis[u] = 1;
            in.push_back(u);

            // std::cout << "TEST\n";
            // for (auto e : in) {
            //     std::cout << e << ' ';
            // }
            // std::cout << '\n';
            // for (auto e : vis) {
            //     std::cout << e << ' ';
            // }
            // std::cout << '\n';

            t += check(check, in[0], 0);
            check_vis.clear();
            t += check(check, in[0], 1);
            check_vis.clear();
            if (t == 2) {
                auto tmp = in;
                std::ranges::sort(tmp);
                s.insert(tmp);
            }

            if (in.size() <= 3) {
                for (auto [w, v] : g[u]) {
                    // std::cout << u << "->" << v << " vis[v]? ";
                    // std::cout << vis[v] << '\n';
                    if (!vis[v]) {
                        dfs(dfs, v);
                    }
                }
            }
            vis[u] = 0;
            in.pop_back();
        };
        dfs(dfs, i);
    }
    // for (auto const &e : s) {
    //     for (auto k : e) {
    //         std::cout << k << ' ';
    //     }
    //     std::cout << '\n';
    // }
    std::cout << s.size() << '\n';
}
void J()
{
    int n, x;
    std::cin >> n >> x;
    std::vector<int> a(n);
    for (auto &e : a) {
        std::cin >> e;
    }

    std::vector<std::vector<PII>> g(2 * n);
    for (int i{}; i != n; ++i) {
        g[i].push_back({1, (i + a[i]) % n + n});
        g[i + n].push_back({1, ((i + 1) % n) + n});
        if (i != 0) {
            g[i + n].push_back({1, (i + a[i]) % n + n});
        }
    }

    // if (a[0] == 0) {
    //     g[0].push_back({2, 1});
    // }

    std::vector<int> dist(2 * n, inf);
    dist[0] = 0;
    std::priority_queue<PII, std::vector<PII>, std::greater<>> q; // dist, u
    q.push({0, 0});
    while (!q.empty()) {
        auto [_, u] = q.top();
        q.pop();
        for (auto [w, v] : g[u]) {
            if (chmin(dist[v], dist[u] + w)) {
                q.push({dist[v], v});
            }
        }
    }
    // for (auto e : dist) {
    //     std::cerr << e << ' ';
    // }
    std::cout << dist[x + n] << '\n';
}
