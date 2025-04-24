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
std::vector<int> min_factor(2e5 + 1, 1);
std::vector<int> primes;
void solve()
{
    i64 x, y;
    std::cin >> x >> y;

    // std::mt19937_64 gen(
    //     std::chrono::high_resolution_clock::now().time_since_epoch().count());
    // x = gen() % 201;
    // y = gen() % 2001;
    //
    // i64 t{1};
    // for (int i{1}; i != 1000000; ++i) {
    //     if (std::gcd(i, x) != 1 && std::gcd(i, y) != 1) {
    //         t = i;
    //         break;
    //     }
    // }
    // if (t == 1) {
    //     t = -1;
    // }

    auto factorize{[](auto x) {
        std::set<int> factors;
        for (auto const p : primes) {
            if (p * p > x) {
                break;
            }
            while (x % p == 0) {
                x /= p;
                factors.insert(p);
            }
        }
        if (x != 1) {
            factors.insert(x);
        }
        return factors;
    }};

    if (x == 1 || y == 1) {
        std::cout << -1 << '\n';
        return;
    }

    i64 ans = 1e18;

    i64 const p{min_factor[x]};
    i64 const q{min_factor[y]};
    if (p != q) {
        chmin(ans, p * q);
    }
    else {
        chmin(ans, p);
    }

    std::vector<int> common;
    std::ranges::set_intersection(factorize(x), factorize(y),
                                  std::back_inserter(common));
    if (!common.empty()) {
        chmin(ans, common.front());
    }

    // if (ans != t) {
    //     std::cerr << "FUCK\n"
    //               << x << ' ' << y << ' ' << t << ' ' << ans << '\n';
    // }

    std::cout << ans << '\n';
}
int main()
{
    for (int i{2}; i != min_factor.size(); ++i) {
        if (min_factor[i] == 1) {
            min_factor[i] = i;
            primes.push_back(i);
        }
        for (auto const p : primes) {
            if (i * p >= min_factor.size()) {
                break;
            }
            min_factor[i * p] = p;
        }
    }

    int t{1};
    std::cin >> t;
    for (int i{}; i != t; ++i) {
        solve();
    }
}
