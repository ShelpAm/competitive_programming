#pragma once

// Problem: D - Santa Claus 2
// Contest: UNIQUE VISION Programming Contest 2024 Christmas (AtCoder Beginner
// Contest 385) Judge: AtCoder URL:
// https://atcoder.jp/contests/abc385/tasks/abc385_d Start: Sat 21 Dec 2024
// 08:52:49 PM CST Author: ShelpAm

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
[[maybe_unused]] constexpr double eps{1e-8};
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
using u64 = std::uint_least64_t;
void solve_case()
{
    int n, m;
    i64 x, y;
    std::cin >> n >> m >> x >> y;
    std::vector<std::pair<int, int>> a(n);
    std::vector<std::pair<char, int>> b(m);
    std::cin >> a >> b;

    // Wrong answer, we can't use chmax here because the default value is 0, but
    // it fails on negative ranges....
    std::unordered_map<i64, std::map<i64, i64>> horizontal;
    std::unordered_map<i64, std::map<i64, i64>> vertical;

    std::unordered_map<char, std::pair<i64, i64>> dirs{
        {'U', {0, 1}}, {'D', {0, -1}}, {'L', {-1, 0}}, {'R', {1, 0}}};

    for (auto const &[d, c] : b) {
        auto [dx, dy]{dirs[d]};
        if (dx != 0) {
            auto const nx{x + (dx * c)};

            auto p{std::make_pair(x, nx)};
            if (p.first > p.second) {
                std::swap(p.first, p.second);
            }
            chmax(horizontal[y][p.first], p.second);

            x = nx;
        }
        else { // dy != 0
            auto const ny{y + (dy * c)};

            auto p{std::make_pair(y, ny)};
            if (p.first > p.second) {
                std::swap(p.first, p.second);
            }
            chmax(vertical[x][p.first], p.second);

            y = ny;
        }
    }

    auto fix{[](std::unordered_map<i64, std::map<i64, i64>> &c) {
        for (auto &[_, c] : c) {
            for (auto it{c.begin()}; it != c.end(); ++it) {
                while (std::next(it) != c.end() &&
                       std::next(it)->first <= it->second + 1) {
                    // Must use chmax here, rather than assign, because the
                    // std::next(it)->second may be smaller than it->second....
                    chmax(it->second, std::next(it)->second);
                    c.erase(std::next(it));
                }
            }
        }
    }};

    fix(horizontal);
    fix(vertical);

    std::cout << x << ' ' << y << ' '
              << std::ranges::count_if(
                     a,
                     [&](std::pair<int, int> const &p) {
                         auto const &[x, y]{p};
                         if (auto it{vertical[x].upper_bound(y)};
                             it != vertical[x].begin() &&
                             std::prev(it)->second >= y) {
                             return true;
                         }
                         auto it{horizontal[y].upper_bound(x)};
                         if (auto it{horizontal[y].upper_bound(x)};
                             it != horizontal[y].begin() &&
                             std::prev(it)->second >= x) {
                             return true;
                         }
                         return false;
                     })
              << '\n';
}
} // namespace
