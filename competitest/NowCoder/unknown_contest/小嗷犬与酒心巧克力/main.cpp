#include <bits/stdc++.h>
using i64 = std::int_least64_t;
bool chmin(auto &x, auto y)
{
    if (x > y) {
        x = y;
        return true;
    }
    return false;
}
void solve();
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t{1};
    // std::cin >> t;
    for (int i{}; i != t; ++i) {
        solve();
    }
}
void solve()
{
    int n, m, k, c;
    std::cin >> n >> m >> k >> c;
    int u{1000000}, v{1000000};
    for (int i{}; i != c; ++i) {
        int x, y;
        std::cin >> x >> y;
        ++x;
        ++y;
        chmin(u, x);
        chmin(v, y);
    }

    std::vector f(n + 1, std::vector(m + 1, 0));
    for (int i{u - 1}; i != -1; --i) {
        for (int j{v - 1}; j != -1; --j) {
            if (i == u - 1 && j == v - 1) {
                continue; // 0
            }
            std::set<int> s;
            for (int p{1}; p != k + 1; ++p) {
                if (i + p < u) {
                    s.insert(f[i + p][j]);
                }
                if (j + p < v) {
                    s.insert(f[i][j + p]);
                }
            }
            int mex{};
            for (auto const e : s) {
                if (mex == e) {
                    ++mex;
                }
            }
            f[i][j] = mex;
        }
    }
    for (auto const &e : f) {
        for (auto const d : e) {
            std::cerr << d << ' ';
        }
        std::cerr << '\n';
    }
    std::cout << (f[0][0] != 0 ? "开吃" : "别急") << '\n';
}
