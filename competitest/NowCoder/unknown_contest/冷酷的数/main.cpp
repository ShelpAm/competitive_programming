#include <bits/stdc++.h>
void solve()
{
    int x, y;
    std::cin >> x >> y;

    auto const m{std::max(x, y)};
    for (int i{2}; i <= m; ++i) {
        if (i != x && i != y && std::gcd(i, x) == 1 && std::gcd(i, y) == 1) {
            std::cout << i << '\n';
            return;
        }
    }
    std::cout << -1 << '\n';
}
int main()
{
    int t{1};
    std::cin >> t;
    for (int i{}; i != t; ++i) {
        solve();
    }
}
