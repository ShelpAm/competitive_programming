#pragma once

// Problem: F - Dangerous Sugoroku
// Contest: HHKB Programming Contest 2025(AtCoder Beginner Contest 388)
// Judge: AtCoder
// URL: https://atcoder.jp/contests/abc388/tasks/abc388_f
// Start: Sun 12 Jan 2025 12:56:17 AM CST
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

std::istream &operator>>(std::istream &istream, auto &&t)
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
    return std::accumulate(coll.begin(), coll.end(), std::int_least64_t{});
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
template <std::signed_integral T> constexpr T lsb(T i) noexcept
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
    i64 n;
    int m, a, b;
    std::cin >> n >> m >> a >> b;
    std::vector<std::pair<i64, i64>> intervals(m);
    std::cin >> intervals;
    intervals.push_back({n + 1, n + 1});

    if (std::ranges::any_of(
            intervals, [b](auto p) { return p.second - p.first + 1 > b; })) {
        std::cout << "No\n";
        return;
    }

    if (a == b) {
        std::cout << (std::ranges::any_of(
                          intervals,
                          [&](auto p) {
                              auto const &[l, r]{p};
                              auto const x{binary_search(
                                  [&](auto x) { return 1 + x * a < l; }, 0,
                                  1e12)};
                              return 1 + (x + 1) * a <= r;
                          }) ||
                              (n - 1) % a != 0
                          ? "No"
                          : "Yes")
                  << '\n';
        return;
    }

    std::unordered_set<i64> ng;
    for (auto const &[l, r] : intervals) {
        for (auto i{l}; i != r + 1; ++i) {
            ng.insert(i);
        }
    }

    i64 p{1}, q{1}; // We guarentee that numbers in [p, q] will be in `ok`.
    std::unordered_set<i64> ok{1};
    for (auto const &[l, r] : intervals) {
        // If a contiguous line of length a can be reached, then we can advance
        // the boy.
        int contiguous{};
        for (auto i{q + 1}; i < l; ++i) {
            bool found{};
            for (int j{a}; j != b + 1; ++j) {
                if (ok.contains(i - j) && !ng.contains(i)) {
                    ok.insert(i);
                    ++contiguous;
                    found = true;
                    break;
                }
            }
            if (!found) {
                contiguous = 0;
            }
            if (contiguous == a - 1) {
                for (auto j{r + 1 - b}; j != l; ++j) {
                    ok.insert(j);
                }
                break;
            }
        }

        auto reachable{r};
        for (auto i{r + 1}; i != r + a; ++i) {
            for (int j{a}; j != b + 1; ++j) {
                if (ok.contains(i - j) && !ng.contains(i)) {
                    ok.insert(i);
                    chmax(reachable, i);
                }
            }
        }
        p = r + 1;
        q = reachable;
    }

    std::cout << (ok.contains(n) ? "Yes\n" : "No\n");
}
} // namespace
