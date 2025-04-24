#pragma once

// Problem: E. A, B, AB and BA
// Contest: Educational Codeforces Round 174 (Rated for Div. 2)
// Judge: Codeforces
// URL: https://codeforces.com/problemset/problem/2069/E
// Start: Tue 04 Mar 2025 10:00:34 PM CST
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
    std::string s;
    std::cin >> s;
    int a, b, ab, ba;
    std::cin >> a >> b >> ab >> ba;

    std::vector<std::string> blocks;
    for (char prev{s.front()}; auto const e : s) {
        if (prev == e) {
            blocks.push_back("");
        }
        else {
            prev = e;
        }
        blocks.back().push_back(e);
    }
    for (auto const &block : blocks) {
        std::cerr << block << ' ';
    }
    std::cerr << '\n';

    std::map<std::pair<char, char>, std::vector<std::string>> types;
    for (auto const &e : blocks) {
        types[{e.front(), e.back()}].push_back(e);
    }

    for (auto &r : types | std::views::values) {
        std::ranges::sort(r);
    }

    for (auto const &e : types[{'A', 'B'}]) {
        auto const max_ab{std::min<int>(e.size() / 2, ab)};
        ab -= max_ab;
        auto const max_ba{
            std::max(0, std::min<int>(ba, (e.size() - (max_ab * 2)) / 2 - 1))};
        ba -= max_ba;
        auto const left{(e.size() - max_ab * 2 - max_ba * 2)};
        debug("e, max_ab, left", std::tuple{e, max_ab, left});
        a -= left / 2;
        b -= left / 2;
    }
    for (auto const &e : types[{'B', 'A'}]) {
        auto const max_ba{std::min<int>(ba, e.size() / 2)};
        ba -= max_ba;
        auto const max_ab{
            std::max(0, std::min<int>((e.size() - max_ba * 2) / 2 - 1, ab))};
        ab -= max_ab;
        auto const left{(e.size() - max_ab * 2 - max_ba * 2)};
        a -= left / 2;
        b -= left / 2;
    }

    int num_compounds{};
    for (auto const &e : types[{'A', 'A'}]) {
        num_compounds += e.size() / 2;
        --a;
    }
    for (auto const &e : types[{'B', 'B'}]) {
        num_compounds += e.size() / 2;
        --b;
    }

    debug("num_compounds", num_compounds);
    debug("And current a, b, ab, ba", std::tuple{a, b, ab, ba});
    auto const overflow{std::max(0, num_compounds - (ab + ba))};
    a -= overflow;
    b -= overflow;

    std::cout << (a >= 0 && b >= 0 ? "YES" : "NO") << '\n';
}
} // namespace
