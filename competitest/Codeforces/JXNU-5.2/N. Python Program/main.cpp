#pragma once

// Problem: N. Python Program
// Contest: JXNU-5.2
// Judge: Codeforces
// URL: https://codeforces.com/gym/607629/problem/N
// Start: Fri 02 May 2025 01:11:12 PM CST
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

struct Node {
    bool is_literal;
    int literal;
    std::string variable;
};
struct Range {
    // range(a,b[,c]):
    Range(std::string_view sv)
    {
        int i = 0;
        auto next_between = [&](char u, char v) -> std::string_view {
            auto p = sv.find(u, i);
            if (p == std::string_view::npos) {
                return "";
            }
            auto q = sv.find(v, p + 1);
            if (q == std::string_view::npos) {
                return "";
            }
            i = p + 1;
            return sv.substr(p + 1, q - p - 1);
        };
        auto s = next_between('(', ',');
        if (s.size() == 1 && std::isalpha(s[0])) {
            a.is_literal = false;
            a.variable = s;
        }
        else {
            a.is_literal = true;
            a.literal = std::stoi(std::string(s));
        }
        s = next_between(',', ',');
        if (s.empty()) {
            s = next_between(',', ')');
        }
        if (s.size() == 1 && std::isalpha(s[0])) {
            b.is_literal = false;
            b.variable = s;
        }
        else {
            b.is_literal = true;
            b.literal = std::stoi(std::string(s));
        }

        s = next_between(',', ')');
        if (s.empty()) {
            c.is_literal = true;
            c.literal = 1;
        }
        else if (s.size() == 1 && std::isalpha(s[0])) {
            c.is_literal = false;
            c.variable = s;
        }
        else {
            c.is_literal = true;
            c.literal = std::stoi(std::string(s));
        }
    }
    Node a, b, c;
};

i64 calc(i64 a, i64 b, i64 c)
{
    if (c > 0) {
        if (b <= a) {
            return 0;
        }
        auto k = (b - a + c - 1) / c;
        // std::cout << a << ' ' << b << ' ' << c << '\n';
        return (a + (a + (k - 1) * c)) * k / 2;
    }
    return -calc(-a, -b, -c);
}
i64 calc(char u, int v, Range const &r)
{
    auto a = r.a.is_literal ? r.a.literal : v;
    auto b = r.b.is_literal ? r.b.literal : v;
    auto c = r.c.is_literal ? r.c.literal : v;
    return calc(a, b, c);
};
void solve_case()
{
    std::string s;
    std::getline(std::cin, s); // ans=0
    std::string l1, l2;
    std::getline(std::cin, l1);
    std::getline(std::cin, l2);
    char v1 = l1[4];
    Range r1(l1.substr(l1.find("range")));
    Range r2(l2.substr(l2.find("range")));
    i64 ans{};
    // std::cout << "????";
    if (r1.c.literal < 0) {
        for (int i{r1.a.literal}; i > r1.b.literal; i += r1.c.literal) {
            ans += calc(v1, i, r2);
        }
    }
    else {
        for (int i{r1.a.literal}; i < r1.b.literal; i += r1.c.literal) {
            ans += calc(v1, i, r2);
        }
    }
    std::cout << ans << '\n';
}
} // namespace
