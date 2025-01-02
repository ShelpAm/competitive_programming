#pragma once

// Problem: D. Drunken Maze
// Contest: 2024 ICPC Asia Taichung Regional Contest (Unrated, Online Mirror,
// ICPC Rules, Preferably Teams) Judge: Codeforces URL:
// https://codeforces.com/problemset/problem/2041/D Start: Thu 26 Dec 2024
// 05:31:13 PM CST Author: ShelpAm

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
    int n, m;
    std::cin >> n >> m;
    std::vector a(n, std::string(m, '\0'));
    std::cin >> a;

    std::vector f(n, std::vector(m, std::vector(4, std::vector(4, inf<int>))));
    std::vector vis(n, std::vector(m, inf<int>));

    std::pair<int, int> beg;
    std::pair<int, int> end;
    for (int i{}; i != n; ++i) {
        for (int j{}; j != m; ++j) {
            if (a[i][j] == 'S') {
                beg = {i, j};
            }
            else if (a[i][j] == 'T') {
                end = {i, j};
            }
        }
    }

    f[beg.first][beg.second].assign(4, std::vector(4, 0));
    std::vector const dirs{std::pair{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    std::queue<std::pair<int, int>> q;
    q.push(beg);
    while (!q.empty()) {
        debug("q.size()", q.size());
        auto const [x, y]{q.front()};
        q.pop();

        for (int i{}; auto [dx, dy] : dirs) {
            dx += x, dy += y;
            if (dx < 0 || dx >= n || dy < 0 || dy >= m || a[dx][dy] == '#') {
                ++i;
                continue;
            }

            for (int j{}; j != 4; ++j) { // x,y 's from dir

                if (i == j) { // this time's from dir
                    for (int k{1}; k != 4; ++k) {
                        if (chmin(f[dx][dy][i][k], 1 + f[x][y][j][k - 1])) {
                            q.push({dx, dy});
                        }
                    }
                }
                else {
                    for (int k{}; k != 4; ++k) {
                        if (chmin(f[dx][dy][i][1], 1 + f[x][y][j][k])) {
                            q.push({dx, dy});
                        }
                    }
                }
            }

            ++i;
        }
    }

    int ans{inf<int>};
    for (auto const &e : f[end.first][end.second]) {
        for (auto const &g : e) {
            chmin(ans, g);
        }
    }

    std::cout << (ans == inf<int> ? -1 : ans) << '\n';
}
} // namespace
