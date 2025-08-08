#pragma once

// Problem: E. I Just Want... One More...
// Contest: The 2023 ICPC Asia Jinan Regional Contest (The 2nd Universal Cup.
// Stage 17: Jinan) Judge: Codeforces URL:
// https://codeforces.com/gym/104901/problem/E Start: Mon 21 Jul 2025 01:59:25
// PM CST Author: ShelpAm

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
struct BipartiteGraph {
    int n1, n2;                      // number of vertices in X and Y, resp.
    std::vector<std::vector<int>> g; // edges from X to Y
    std::vector<int> ma, mb; // matches from X to Y and from Y to X, resp.
    std::vector<int> dist;   // distance from unsaturated vertices in X.

    BipartiteGraph(int n1, int n2)
        : n1(n1), n2(n2), g(n1), ma(n1, -1), mb(n2, -1)
    {
    }

    // Add an edge from u in X to v in Y.
    void add_edge(int u, int v)
    {
        g[u].emplace_back(v);
    }

    // Build the level graph.
    bool bfs()
    {
        dist.assign(n1, -1);
        std::queue<int> q;
        for (int u = 0; u < n1; ++u) {
            if (ma[u] == -1) {
                dist[u] = 0;
                q.emplace(u);
            }
        }
        // Build the level graph for all reachable vertices.
        bool succ = false;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                if (mb[v] == -1) {
                    succ = true;
                }
                else if (dist[mb[v]] == -1) {
                    dist[mb[v]] = dist[u] + 1;
                    q.emplace(mb[v]);
                }
            }
        }
        return succ;
    }

    // Find an augmenting path starting at u.
    bool dfs(int u)
    {
        for (int v : g[u]) {
            if (mb[v] == -1 || (dist[mb[v]] == dist[u] + 1 && dfs(mb[v]))) {
                ma[u] = v;
                mb[v] = u;
                return true;
            }
        }
        dist[u] = -1; // Mark this point as inreachable after one visit.
        return false;
    }

    // Hopcroft-Karp maximum matching algorithm.
    std::vector<std::pair<int, int>> hopcroft_karp_maximum_matching()
    {
        // Build the level graph and then find a blocking flow.
        while (bfs()) {
            for (int u = 0; u < n1; ++u) {
                if (ma[u] == -1) {
                    dfs(u);
                }
            }
        }
        // Collect the matched pairs.
        std::vector<std::pair<int, int>> matches;
        matches.reserve(n1);
        for (int u = 0; u < n1; ++u) {
            if (ma[u] != -1) {
                matches.emplace_back(u, ma[u]);
            }
        }
        return matches;
    }
};
namespace {
using i64 = std::int_least64_t;
using i128 = __int128_t;
using u64 = std::uint_least64_t;
using u128 = __uint128_t;
void solve_case()
{
    using namespace ::shelpam;
    int n, m;
    std::cin >> n >> m;
    BipartiteGraph g(n, n);
    for (int i{}; i != m; ++i) {
        int u, v;
        std::cin >> u >> v;
        g.add_edge(u - 1, v - 1);
    }

    auto res = g.hopcroft_karp_maximum_matching();
}
} // namespace
