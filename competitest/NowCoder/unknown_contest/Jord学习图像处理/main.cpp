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
    std::cin >> t;
    for (int i{}; i != t; ++i) {
        solve();
    }
}
void solve()
{
    int n, m;
    std::pair<int, int> a, b;
    std::cin >> n >> m >> a.first >> b.first;
    a.second = b.second = 100;
    std::vector<std::string> mat(n);
    for (auto &e : mat) {
        std::cin >> e;
    }
    {
        auto const d{std::gcd(a.first, a.second)};
        a.first /= d;
        a.second /= d;
    }
    {
        auto const d{std::gcd(b.first, b.second)};
        b.first /= d;
        b.second /= d;
    }

    if (n % a.second != 0 || m % b.second != 0) {
        std::cout << "error\n";
        return;
    }

    std::vector<std::string> out(n * a.first / a.second,
                                 std::string(m * b.first / b.second, 0));
    for (int i{}; i != n; i += a.second) {
        for (int j{}; j != m; j += b.second) {
            std::set<char> colors;
            for (int u{}; u != a.second; ++u) {
                for (int v{}; v != b.second; ++v) {
                    colors.insert(mat[i + u][j + v]);
                }
            }
            if (colors.size() > 1) {
                std::cout << "error\n";
                return;
            }
            auto const x{i / a.second * a.first};
            auto const y{j / b.second * b.first};
            for (int u{}; u != a.first; ++u) {
                for (int v{}; v != b.first; ++v) {
                    out[x + u][y + v] = mat[i][j];
                }
            }
        }
    }

    for (auto const &r : out) {
        for (auto const c : r) {
            std::cout << c;
        }
        std::cout << '\n';
    }
}
