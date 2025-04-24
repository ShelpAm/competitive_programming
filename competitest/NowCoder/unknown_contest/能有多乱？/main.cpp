#pragma once

// Problem: 能有多乱？
// Contest: unknown_contest
// Judge: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/100672/F
// Start: Sun 02 Mar 2025 03:06:56 PM CST
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
template <typename T, typename U = std::remove_cvref_t<T>>
concept non_string_range =
    !std::same_as<U, std::string> && (std::ranges::range<U> || pair<U>);
} // namespace shelpam::concepts

std::istream &operator>>(std::istream &istream,
                         shelpam::concepts::non_string_range auto &&t)
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
constexpr auto sum_of(std::ranges::range auto const &coll) noexcept
{
    return std::accumulate(
        coll.begin(), coll.end(),
        typename std::remove_cvref_t<decltype(coll)>::value_type{});
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
std::int_least64_t binary_search(std::invocable<std::int_least64_t> auto check,
                                 std::int_least64_t ok, std::int_least64_t ng,
                                 bool check_ok = true)
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
template <std::unsigned_integral T> constexpr T lsb(T i) noexcept
{
    return i & -i;
}
// i mustn't be 0
constexpr int msb(std::unsigned_integral auto i)
{
    if (i == 0) {
        throw std::invalid_argument{"i must be positive."};
    }
    return (sizeof(i) * CHAR_BIT) - 1 - std::countl_zero(i);
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
    // std::cin >> t;
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
void solve_case()
{
    constexpr i64 p = 1e9 + 7;
    std::vector<i64> factorial(1e5 + 2);
    factorial[0] = 1;
    for (int i{1}; i != factorial.size(); ++i) {
        factorial[i] = factorial[i - 1] * i % p;
    }

    int n, t;
    std::cin >> n >> t;
    std::vector<i64> a(n + 1);
    std::vector<i64> squared_pref(n + 1);
    std::vector<i64> pref(n + 1);
    for (int i{1}; i != n + 1; ++i) {
        std::cin >> a[i];
        squared_pref[i] = ((a[i] * a[i]) + squared_pref[i - 1]) % p;
        pref[i] = a[i] + pref[i - 1];
    }

    // debug("pref", pref);

    // DEBUG
    // std::vector<int> nums{0};
    // for (int i{1}; i != a.size(); ++i) {
    //     for (int j{}; j != a[i]; ++j) {
    //         nums.push_back(i);
    //     }
    // }

    for (int i{}; i != t; ++i) {
        i64 l, r;
        std::cin >> l >> r;
        // std::cerr << l << ' ' << r << '\n';
        // Both L and R are PARTIAL
        auto const L{std::ranges::upper_bound(pref, l - 1) - pref.begin()};
        auto const R{std::ranges::upper_bound(pref, r) - pref.begin()};
        // std::cerr << L << ' ' << R << '\n';

        i64 ans{};
        if (L != R) {
            // INCLUSIVE
            auto tmp{((pref[R - 1] - pref[L]) * (pref[R - 1] - pref[L])) -
                     (squared_pref[R - 1] - squared_pref[L])};
            ((tmp %= p) += p) %= p;
            tmp *= pow(2ULL, p - 2, p);
            ((tmp %= p) += p) %= p;
            // std::cerr << "TMP: " << tmp << '\n';
            ans += tmp;
            ((ans %= p) += p) %= p;
            // BOUNDS
            auto const left{(pref[L] - (l - 1)) % p};
            auto const right{(r - pref[R - 1]) % p};
            // std::cerr << "left: " << left << ", right: " << right << '\n';
            ans += left * (pref[R - 1] - pref[L]) % p;
            ((ans %= p) += p) %= p;
            ans += right * (pref[R - 1] - pref[L]) % p;
            ((ans %= p) += p) %= p;
            ans += left * right % p;
            ((ans %= p) += p) %= p;
            debug("in 2s: ", ans);
            // i64 pairs{};
            // for (auto j{l}; j != r + 1; ++j) {
            //     for (auto k{j + 1}; k != r + 1; ++k) {
            //         if (nums[j] != nums[k]) {
            //             ++pairs;
            //         }
            //     }
            // }
            // assert(pairs == ans);
        }

        debug("len", r - l + 1);
        ans *= factorial[r - l + 1];
        debug("factorial", factorial[r - l + 1]);
        ((ans %= p) += p) %= p;
        ans *= pow(2ULL, p - 2, p);
        ((ans %= p) += p) %= p;
        std::cout << ans << '\n';
    }
}
} // namespace
//
