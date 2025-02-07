#pragma once

// Problem: J. Bridge III
// Contest: Firefly Cup (1st Zrnstsr Cup)
// Judge: Codeforces
// URL: https://codeforces.com/group/BJlsDCvlJO/contest/586547/problem/J
// Start: Fri 07 Feb 2025 05:07:52 PM CST
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
template <typename T>
concept non_string_range =
    !std::same_as<std::remove_cvref_t<T>, std::string> && std::ranges::range<T>;
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
    int n;
    std::cin >> n;
    std::vector<std::string> a(n);
    std::cin >> a;

    for (auto &e : a) {
        if (e.size() == 2 && e[1] == 'N') {
            e[1] = 'Z';
        }
    }

    if (n < 4) {
        std::cout << "NO\n";
        return;
    }

    if (std::ranges::all_of(a.begin(), a.begin() + 4,
                            [](auto const &e) { return e == "P"; })) {
        std::cout << (n == 4 ? "YES\n" : "NO\n");
        return;
    }

    auto pass{[&](int i) {
        return a[i] == "P" && a[i + 1] == "P" && a[i + 2] == "P";
    }};
    if (auto const first_non_pass{
            std::ranges::find_if(a, [](auto const &e) { return e != "P"; }) -
            a.begin()};
        std::ranges::any_of(std::views::iota(first_non_pass, n - 3), pass) ||
        !pass(n - 3)) {
        std::cout << "NO\n";
        return;
    }

    int last_player{-1};
    std::string last{"0A"}; // Non-pass last card
    for (int i{}; i != n; ++i) {
        if (a[i] == "X") {
            if (last_player == -1) { // Cannot appear in the first round
                std::cout << "NO\n";
                return;
            }
            if (last_player % 2 == i % 2 || last.contains('X')) {
                // std::cout << "FUCK" << i << last << last_player;
                std::cout << "NO\n"; // Invalid (not a component, or not a bid)
                return;
            }
        }
        else if (a[i] == "XX") {
            if (last_player == -1) { // Cannot appear in the first round
                std::cout << "NO\n";
                return;
            }
            if (last_player % 2 == i % 2 || last != "X") {
                std::cout
                    << "NO\n"; // Invalid (not a component, or not a double)
                return;
            }
        }
        else if (a[i] != "P") { // Bid
            if (a[i] <= last) {
                std::cout << "NO\n";
                return;
            }
        }

        if (a[i] != "P") {
            last_player = i;
            last = a[i];
        }
    }
    std::cout << "YES\n";
}
} // namespace
