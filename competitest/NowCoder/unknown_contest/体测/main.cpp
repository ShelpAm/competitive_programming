#pragma once

// Problem: 体测
// Contest: unknown_contest
// Judge: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/100672/H
// Start: Sun 02 Mar 2025 04:25:08 PM CST
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
void solve_case()
{
    int n, a, b, c, l;
    std::cin >> n >> a >> b >> c >> l;
    std::vector<int> p(n + 1);
    for (auto &e : p) {
        std::cin >> e;
    }

    auto check{[&p](auto x) {
        return std::ranges::any_of(
            p, [&](auto e) { return std::ranges::binary_search(p, e + x); });
    }};

    std::vector<int> t; // Required
    for (auto const e : {a, b, c}) {
        if (!check(e)) {
            t.push_back(e);
        }
    }

    if (t.size() == 0) {
        std::cout << 0 << '\n';
        return;
    }

    if (t.size() == 1) {
        std::cout << 1 << '\n';
        return;
    }

    // PRE WORK
    // Returns positions that're ok
    auto solve_with_once{[&p, l](std::vector<int> const &dist) {
        std::vector<std::set<int>> sets;
        for (auto const tx : dist) {
            std::set<int> s;
            for (auto const e : p) {
                if (e - tx >= 0) {
                    s.insert(e - tx);
                }
                if (e + tx <= l) {
                    s.insert(e + tx);
                }
            }
            sets.push_back(s);
        }
        std::vector<int> v(sets.front().begin(), sets.front().end());
        std::vector<int> u;
        for (auto const &s : sets) {
            std::ranges::set_intersection(v, s, std::back_inserter(u));
            v = std::move(u);
        }
        return v;
    }};

    auto v{solve_with_once(t)};
    if (t.size() == 2) {
        if (!v.empty()) {
            std::cout << 1 << '\n';
        }
        else {
            std::cout << 2 << '\n';
        }
        return;
    }

    assert(t.size() == 3);
    if (!v.empty()) {
        std::cout << 1 << '\n';
        return;
    }

    // Cost 2
    // METHOD 1: 3 out of 2
    auto go{[&p, l](std::vector<int> perm) {
        debug("p", p);
        debug("perm", perm);
        auto a{perm[0]};
        auto b{perm[1]};
        auto c{perm[2]};
        std::set<int> A, C;
        for (auto const e : p) {
            if (e - a >= 0) {
                A.insert(e - a);
            }
            if (e + a <= l) {
                A.insert(e + a);
            }
        }
        for (auto const e : p) {
            if (e - c >= 0) {
                C.insert(e - c);
            }
            if (e + c <= l) {
                C.insert(e + c);
            }
        }
        debug("A", A);
        debug("C", C);
        return std::ranges::any_of(
            A, [&](auto e) { return C.contains(e + b) || C.contains(e - b); });
    }};

    std::ranges::sort(t);
    do {
        if (go(t)) {
            std::cout << 2 << '\n';
            return;
        }
    } while (std::next_permutation(t.begin(), t.end()));

    // METHOD 2: 2 out of 1 and 1 out of one
    if (!solve_with_once({t[0], t[1]}).empty()) {
        std::cout << 2 << '\n';
        return;
    }
    if (!solve_with_once({t[2], t[1]}).empty()) {
        std::cout << 2 << '\n';
        return;
    }
    if (!solve_with_once({t[0], t[2]}).empty()) {
        std::cout << 2 << '\n';
        return;
    }

    std::cout << 3 << '\n';
}
} // namespace
