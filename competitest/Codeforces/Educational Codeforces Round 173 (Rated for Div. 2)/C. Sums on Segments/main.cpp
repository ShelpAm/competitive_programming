#pragma once

// Problem: C. Sums on Segments
// Contest: Educational Codeforces Round 173 (Rated for Div. 2)
// Judge: Codeforces
// URL: https://codeforces.com/contest/2043/problem/C
// Start: Tue 24 Dec 2024 10:59:12 PM CST
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

namespace {
[[maybe_unused]] constexpr std::uint_least64_t mod998244353{998'244'353ULL};
[[maybe_unused]] constexpr std::uint_least64_t mod1e9p7{1'000'000'007ULL};
[[maybe_unused]] constexpr double eps{1e-10};
template <typename T> constexpr T inf{std::numeric_limits<T>::max() / 4};
template <typename T> constexpr T max{std::numeric_limits<T>::max()};

// Concepts.
namespace shelpam::concepts {
template <typename> struct is_pair_t : std::false_type {};
template <typename T, typename U>
struct is_pair_t<std::pair<T, U>> : std::true_type {};
template <typename T>
concept pair = is_pair_t<T>::value;
template <typename> struct is_tuple_t : std::false_type {};
template <typename... Ts>
struct is_tuple_t<std::tuple<Ts...>> : std::true_type {};
template <typename... Ts>
concept tuple = is_tuple_t<Ts...>::value;
} // namespace shelpam::concepts

auto operator>>(auto &istream, auto &&t) -> decltype(istream)
{
    using T = std::remove_cvref_t<decltype(t)>;
    static_assert(!shelpam::concepts::tuple<T>,
                  "tuple: not implemented yet.\n");
    if constexpr (std::ranges::range<T>) {
        for (auto &ele : t) {
            istream >> ele;
        }
    }
    else if constexpr (shelpam::concepts::pair<T>) {
        istream >> t.first >> t.second;
    }
    else {
        istream >> t;
    }
    return istream;
}
#ifndef ONLINE_JUDGE
#include "/home/shelpam/Documents/projects/competitive-programming/libs/debug.h"
#else
#define debug(...)
#endif
auto chmax(auto &value, auto const &other) noexcept -> bool
{
    if (value < other) {
        value = other;
        return true;
    }
    return false;
}
auto chmin(auto &value, auto const &other) noexcept -> bool
{
    if (value > other) {
        value = other;
        return true;
    }
    return false;
}
constexpr auto sum_of(std::ranges::range auto const &coll) noexcept
{
    return std::accumulate(coll.begin(), coll.end(), std::int_least64_t{});
}
constexpr auto pow(auto base, std::int_least64_t exp, std::uint_least64_t p)
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
auto binary_search(std::invocable<std::int_least64_t> auto check,
                   std::int_least64_t ok, std::int_least64_t ng,
                   bool check_ok = true) -> std::int_least64_t
{
    if (check_ok && !check(ok)) {
        throw std::invalid_argument{"check isn't true on 'ok'."};
    }
    while (std::abs(ok - ng) > 1) {
        auto const x{(ok + ng) / 2};
        (check(x) ? ok : ng) = x;
    }
    return ok;
}
constexpr auto lsb(std::signed_integral auto i) noexcept -> decltype(i)
{
    return i & -i;
}
// i mustn't be 0
constexpr auto msb(std::unsigned_integral auto i) -> int
{
    if (i == 0) {
        throw std::invalid_argument{"i must be positive."};
    }
    return (sizeof(i) * CHAR_BIT) - 1 - std::countl_zero(i);
}
/*[[maybe_unused]] auto gen_rand() noexcept*/
/*{*/
/*  static std::mt19937_64 rng(*/
/*      std::chrono::steady_clock::now().time_since_epoch().count());*/
/*  return rng();*/
/*}*/
void solve_case();
} // namespace
auto main() -> int
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
using namespace shelpam;
namespace {
using i64 = std::int_least64_t;
using i128 = __int128_t;
using u64 = std::uint_least64_t;
using u128 = __uint128_t;
#define int long long
void solve_case()
{
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    std::cin >> a;

    std::set<int> o{0};

    auto simpler_calc{[&o](std::vector<int> s) {
        auto find_max_subarray{[](std::vector<int> const &a) {
            int ans{};
            for (int s{}; auto const e : a) {
                s += e;
                chmax(s, 0);
                chmax(ans, s);
            }
            return ans;
        }};
        auto const max{find_max_subarray(s)};
        auto const min{-find_max_subarray(
            s | std::views::transform([](auto e) { return -e; }) |
            std::ranges::to<std::vector<int>>())};

        for (int i{min}; i <= max; ++i) {
            o.insert(i);
        }
    }};

    auto calc{[&o](std::span<int> s) {
        if (s.empty()) {
            return;
        }

        std::multimap<int, int> ranges;

        std::vector smin(s.size(), 0), smax(s.size(), 0);
        std::vector pmin(s.size(), 0), pmax(s.size(), 0);
        for (int i{}, k{}; i != s.size(); ++i) {
            k += s[i];
            chmin(pmin[i], k);
            chmax(pmax[i], k);
            if (i > 0) {
                chmin(pmin[i], pmin[i - 1]);
                chmax(pmax[i], pmax[i - 1]);
            }
        }
        for (int i = s.size() - 1, k{}; i != -1; --i) {
            k += s[i];
            chmin(smin[i], k);
            chmax(smax[i], k);
            if (i < s.size() - 1) {
                chmin(smin[i], smin[i + 1]);
                chmax(smax[i], smax[i + 1]);
            }
        }

        int lsum{};
        int rsum{sum_of(s)};
        for (int i{}; i != s.size(); ++i) {
            ranges.insert(
                {(rsum - smax[i]) + (lsum - (i > 0 ? pmax[i - 1] : 0)),
                 (rsum - smin[i]) + (lsum - (i > 0 ? pmin[i - 1] : 0))});

            rsum -= s[i];
            lsum += s[i];
        }

        // Merges
        for (auto it{ranges.begin()}, end{ranges.end()}; it != end; ++it) {
            while (std::next(it) != end &&
                   std::next(it)->first <= it->second + 1) {
                chmax(it->second, std::next(it)->second);
                ranges.erase(std::next(it));
            }
        }

        for (auto const &[l, r] : ranges) {
            for (int i{l}; i <= r; ++i) {
                o.insert(i);
            }
        }
    }};

    auto const p{std::ranges::find_if_not(
        a, [](auto const e) { return std::abs(e) == 1; })};

    if (p != a.end()) {
        // x excluded
        simpler_calc({a.begin(), p});
        simpler_calc({std::next(p), a.end()});

        // x included
        auto const k{p - a.begin()};
        int lmin{};
        int lmax{};
        int lsum{};
        for (auto i{k - 1}; i != -1; --i) {
            lsum += a[i];
            chmin(lmin, lsum);
            chmax(lmax, lsum);
        }
        int rmin{};
        int rmax{};
        int rsum{};
        for (auto i{k + 1}; i != n; ++i) {
            rsum += a[i];
            chmin(rmin, rsum);
            chmax(rmax, rsum);
        }
        for (int i{lmin + rmin}; i <= lmax + rmax; ++i) {
            o.insert(i + *p);
        }
    }
    else {
        calc(a);
    }

    std::cout << o.size() << '\n';
    for (auto const e : o) {
        std::cout << e << ' ';
    }
    std::cout << '\n';
}
} // namespace
