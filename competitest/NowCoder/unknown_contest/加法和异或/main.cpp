#include <bits/stdc++.h>
using i64 = std::int_least64_t;
auto chmin(auto &x, auto y)
{
    if (x > y) {
        x = y;
        return true;
    }
    return false;
}
constexpr i64 pow(i64 a, i64 b, i64 p)
{
    i64 ans{1};
    while (b != 0) {
        if (b & 1) {
            (ans *= a) %= p;
        }
        (a *= a) %= p;
        b /= 2;
    }
    return ans;
}
constexpr i64 p = 1e9 + 7;
void solve()
{
    int k, m;
    std::cin >> k >> m;
    std::string s;
    std::cin >> s;

    if (!s.contains('1')) {
        i64 ans{1};
        for (int i{1}; i != k + 1; ++i) {
            (ans *= i) %= p;
        }
        for (int i{1}; i != m + 1; ++i) {
            (ans *= pow(i, p - 2, p)) %= p;
        }
        for (int i{1}; i != k - m + 1; ++i) {
            (ans *= pow(i, p - 2, p)) %= p;
        }
        std::cout << ans << '\n';
        return;
    }

    int v{};
    for (auto const e : s) {
        v = v * 2 + e - '0';
    }

    std::ranges::reverse(s);
    while (s.size() < k) {
        s.push_back('0');
    }
    s.insert(s.begin(), '\0');

    std::vector f(k + 1, std::vector(m + 1, std::vector<i64>(2, 0)));
    f[0][0][0] = 1;
    for (int i{1}; i != k + 1; ++i) {
        for (int j{}; j != m + 1; ++j) {
            if (s[i] == '1') {
                f[i][j][1] = f[i - 1][j][1] * 2;
                f[i][j][0] = j - 1 >= 0 ? f[i - 1][j - 1][0] * 2 : 0;
            }
            else if (s[i] == '0') {
                f[i][j][1] =
                    f[i - 1][j][0] + (j - 1 >= 0 ? f[i - 1][j - 1][1] : 0);
                f[i][j][0] =
                    (j - 1 >= 0 ? f[i - 1][j - 1][1] : 0) + f[i - 1][j][0];
            }
            f[i][j][1] %= p;
            f[i][j][0] %= p;
        }
    }
    // for (auto const &r : f) {
    //     for (auto const &c : r) {
    //         for (auto const e : c) {
    //             std::cout << e << ' ';
    //         }
    //         std::cout << '|';
    //     }
    //     std::cout << '\n';
    // }
    static_assert(pow(3, 5, p) == 243);
    auto const ans{(f[k][m][0] + f[k][m - 1][1]) % p * pow(2, p - 2, p) % p};
    std::cout << ans << '\n';

    // std::set<std::pair<int, int>> set;
    // for (unsigned i{}; i != 1 << k; ++i) {
    //     for (unsigned j{i}; j != 1 << k; ++j) {
    //         if ((i ^ j) == v && std::popcount(i + j) == m) {
    //             set.insert({i, j});
    //         }
    //     }
    // }
    // for (auto const &[p, q] : set) {
    //     std::cerr << p << ' ' << q << '\n';
    // }
    // assert(ans == set.size());
}
int main()
{
    int t{1};
    // std::cin >> t;
    for (int i{}; i != t; ++i) {
        solve();
    }
}
