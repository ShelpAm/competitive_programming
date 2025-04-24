#pragma once

// Problem: 抹茶
// Contest: unknown_contest
// Judge: HDOJ
// URL: https://acm.hdu.edu.cn/contest/problem?cid=1155&pid=1003
// Start: Fri 11 Apr 2025 06:51:00 PM CST
// Author: ShelpAm

// #include <bits/stdc++.h>
#include <algorithm>
#include <bit>
#include <bitset>
#include <cassert>
#include <chrono>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numbers>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace {
[[maybe_unused]] constexpr std::uint_least64_t mod998244353{998'244'353ULL};
[[maybe_unused]] constexpr std::uint_least64_t mod1e9p7{1'000'000'007ULL};
[[maybe_unused]] constexpr double eps{1e-10};
template <typename T> constexpr T inf{std::numeric_limits<T>::max() / 4};
template <typename T> constexpr T max{std::numeric_limits<T>::max()};

#ifndef ONLINE_JUDGE
#else
#define debug(...)
#endif
void YesNo(bool yes)
{
    std::cout << (yes ? "Yes\n" : "No\n");
}
bool chmax(auto &value, auto const &other) noexcept
{
    if (value < other) {
        value = other;
        return true;
    }
    return false;
}
bool chmin(auto &value, auto const &other) noexcept
{
    if (value > other) {
        value = other;
        return true;
    }
    return false;
}
constexpr auto pow(auto base, auto exp, std::uint_least64_t p)
{
    static_assert(sizeof(base) > sizeof(int), "Use of `int`s is bug-prone.");
    if (exp < 0) {
        throw std::invalid_argument{"Exponent should be non-negative"};
    }
    decltype(base) res{1};
    while (exp != 0) {
        if ((exp & 1) == 1) {
            res = res * base % p;
        }
        base = base * base % p;
        exp >>= 1;
    }
    return res;
}
// [[maybe_unused]] auto gen_rand() noexcept
// {
//     static std::mt19937_64 rng(
//         std::chrono::steady_clock::now().time_since_epoch().count());
//     return rng();
// }
void solve_case();
} // namespace
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    constexpr auto my_precision{10};
    std::cout << std::fixed << std::setprecision(my_precision);
    int t{1};
    std::cin >> t;
    for (int i{}; i != t; ++i) {
#ifndef ONLINE_JUDGE
        std::cerr << "Test case " << i << '\n';
#endif
        solve_case();
    }
    return 0;
}
namespace {
using i64 = std::int_least64_t;
using i128 = __int128_t;
using u64 = std::uint_least64_t;
using u128 = __uint128_t;
void solve_case()
{
    auto binary_search = [](auto check, i64 ok, i64 ng) {
        while (std::abs(ok - ng) > 1) {
            auto mid = ok + ng >> 1;
            (check(mid) ? ok : ng) = mid;
        }
        return ok;
    };

    int n;
    i64 x;
    std::cin >> n >> x;
    std::vector<int> a(n);
    for (auto &e : a) {
        std::cin >> e;
    }

    std::vector<i64> s(n);
    for (int i{1}; i != n; ++i) {
        s[i] = s[i - 1] + a[i] - a[i - 1];
    }

    auto ans = binary_search(
        [&](auto l) {
            i64 ans{max<i64>};
            for (int i{}; i + l - 1 != n; ++i) {
                auto j = i + l - 1;
                // chmin(ans, s[n] - s[j + 1] + );
            }
            return ans <= x;
        },
        n, -1);
    std::cout << ans << '\n';
}
} // namespace
