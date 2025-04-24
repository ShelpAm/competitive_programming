#include <bits/stdc++.h>
using i64 = std::int_least64_t;
void solve();
int main()
{
    int t{1};
    // std::cin >> t;
    for (int i{}; i != t; ++i) {
        solve();
    }
}
void solve()
{
    i64 n;
    std::cin >> n;
    std::vector<int> a(n);
    for (auto &e : a) {
        std::cin >> e;
    }

    i64 ans{};
    i64 s{};
    for (int i{}; i != n; ++i) {
        s += (i + 1) * a[i];
        ans += s;
    }
    std::cout << ans << '\n';
}
