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
double c_n_2(i64 n)
{
    return n * (n - 1) * 0.5;
}
void solve()
{
    int n;
    std::cin >> n;
    std::vector<double> a(n + 1);
    for (auto &e : a) {
        std::cin >> e;
    }
    if (std::abs(a[0] - 1) < 1e-7) {
        std::printf("%.3lf", 0);
        return;
    }

    double p{};
    for (int i{1}; i != n + 1; ++i) {
        p += c_n_2(n - i) * a[i];
    }
    p /= c_n_2(n);
    auto const ans{p / (p + a[0])};
    std::printf("%.3lf", ans);
}
