#include <bits/stdc++.h>
using i64 = std::int_least64_t;
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
    constexpr i64 p = 1e9 + 7;

    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (auto &e : a) {
        std::cin >> e;
    }

    std::unordered_map<int, int> o;
    i64 ans{};
    std::unordered_map<int, i64> s;
    for (auto const e : a) {
        std::vector<int> fac, caf;
        for (int i{1}; i * i <= e; ++i) {
            if (e % i == 0) {
                fac.push_back(i);
                caf.push_back(e / i);
            }
        }
        if (caf.back() == fac.back()) {
            caf.pop_back();
        }
        std::ranges::reverse(caf);
        std::ranges::copy(caf, std::back_inserter(fac));

        i64 cur{};
        for (auto const f : fac) {
            cur += o[f];
            cur %= p;
            cur += s[f];
            cur %= p;
        }
        ans += cur;
        ans %= p;
        s[e] += cur;
        s[e] %= p;
        ++o[e];
    }
    std::cout << ans << '\n';
}
