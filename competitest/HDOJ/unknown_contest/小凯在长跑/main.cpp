#pragma once

// Problem: 小凯在长跑
// Contest: unknown_contest
// Judge: HDOJ
// URL: https://acm.hdu.edu.cn/contest/problem?cid=1154&pid=1006
// Start: Fri 04 Apr 2025 08:36:54 PM CST
// Author: ShelpAm

// #include <bits/stdc++.h>
#include <algorithm>
#include <bit>
#include <bitset>
#include <cassert>
#include <chrono>
#include <climits>
#include <concepts>
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
#include <ranges>
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

void solve_case();
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    constexpr auto my_precision{0};
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
using i64 = std::int_least64_t;
using i128 = __int128_t;
using u64 = std::uint_least64_t;
using u128 = __uint128_t;
constexpr auto pow(i64 a, auto b, i64 p)
{
    i64 r = 1;
    while (b) {
        if (b & 1) {
            r *= a;
            r %= p;
        }
        a *= a;
        a %= p;
        b >>= 1;
    }
    return r;
}
constexpr auto mod = 998244353;
constexpr auto inv(auto x)
{
    return pow(x, mod - 2, mod);
}
template <typename T> struct Fraction {
    T nume;
    T denu;
    Fraction() : nume(0), denu(1) {}
    Fraction(T t) : nume(t), denu(1) {}
    Fraction(T nume, T denu) : nume(nume), denu(denu) {}
    constexpr void normalize()
    {
        auto gcd = std::gcd(nume, denu);
        if (gcd != 0) {
            nume /= gcd;
            denu /= gcd;
        }
        else {
            assert(nume == 0);
            denu = 1;
        }
    }
    constexpr bool operator<(Fraction rhs) const
    {
        return nume * rhs.denu < rhs.nume * denu;
    }
    constexpr Fraction &operator+=(Fraction rhs)
    {
        nume = nume * rhs.denu + denu * rhs.nume;
        denu = denu * rhs.denu;
        return *this;
    }
};
void solve_case()
{
    i64 n;
    int m;
    std::cin >> n >> m;

    std::vector<i64> o(m);
    for (int i{}; i != o.size(); ++i) {
        o[i] = n / m + (i <= n % m);
    }
    o[0] -= 1; // remove 0

    std::vector<i64> f(m);
    f[0] = 1;
    for (int i{}; i != m; ++i) {
        std::vector<i64> ws;
        for (i64 k{1}; k <= o[i]; k *= 2) {
            o[i] -= k;
            ws.push_back(k);
        }
        if (o[i] != 0) {
            ws.push_back(o[i]);
        }
        for (auto w : ws) {
            auto g = f;
            for (int j{}; j != f.size(); ++j) {
                g[j] += f[(j - (w * i % m) + m) % m] * w;
                g[j] %= mod;
            }
            f = g;
        }
    }

    std::cout << (f[0] - 1 + mod) % mod << '\n';
}
