#include <bits/stdc++.h>
void solve()
{
    int a, b, c;
    std::cin >> a >> b >> c;
    auto check{[](std::vector<int> a) {
        std::ranges::sort(a);
        return a[0] + a[1] > a[2];
    }};
    std::vector<int> t{a, b, c};
    std::set<std::vector<int>> s;
    for (int i{}; i != 27; ++i) {
        auto k{i};
        std::vector<int> v;
        for (int j{}; j != 3; ++j) {
            v.push_back(t[k % 3]);
            k /= 3;
        }
        if (check(v)) {
            std::ranges::sort(v);
            s.insert(v);
        }
    }
    std::cout << s.size() << '\n';
}
int main()
{
    int t{1};
    std::cin >> t;
    for (int i{}; i != t; ++i) {
        solve();
    }
}
