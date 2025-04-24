#pragma once

// Problem: $(PROBLEM)
// Contest: $(CONTEST)
// Judge: $(JUDGE)
// URL: $(URL)
// Start: $(DATE)
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

#ifndef ONLINE_JUDGE
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
    constexpr auto my_precision{3};
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
namespace {
using i64 = std::int_least64_t;
using i128 = __int128_t;
using u64 = std::uint_least64_t;
using u128 = __uint128_t;
void solve_case()
{
    int n; std::cin >> n;
    using Vertex = std::string;
    struct Edge {
        Vertex v;
        int w;
        int com;
    };
    using Distance = std::pair<int, int>;
    using Node = std::tuple<Distance, int, Vertex>; // dist, company, u
    std::unordered_map<Vertex, std::vector<Edge>> g;
    std::map<std::pair<Vertex,Vertex>, int> com_of_edge;
    for (int i{}; i!=n; ++i) {
        int k; std::cin >> k;
        std::vector<Vertex> a(k); for (auto &e : a) std::cin >> e;
        for (int j{}; j+1!=k; ++j) {
            com_of_edge[{a[j], a[j+1]}] = i;
            com_of_edge[{a[j + 1], a[j]}] = i;
            g[a[j]].push_back({a[j+1], 1, i});
            g[a[j + 1]].push_back({a[j], 1, i});
        }
    }
    auto dijkstra = [](auto g, Vertex s) {
        std::unordered_map<Vertex, Distance> dist;
        std::unordered_map<Vertex, bool> vis;
        std::unordered_map<Vertex, Vertex> prev;
        g[s];
        for (auto const& [u, edges] : g) {
            dist[u] = {inf<int>, inf<int>};
            for (auto [v, w, c] : edges) {
                dist[v] = {inf<int>, inf<int>};
            }
        }
        std::priority_queue<Node, std::vector<Node>, std::greater<>> q;
        q.push({dist[s] = {0, 0}, -1, s});
        while (!q.empty()) {
            auto [_, com, u] = q.top();
            q.pop();
            if (vis[u]) {
                continue;
            }
            vis[u] = true;
            for (auto [v, w, c] : g.at(u)) {
                if (!vis[v] && chmin(dist[v], Distance{ dist[u].first + w, dist[u].second + (com != c)} )) {
                    prev[v] = u;
                    q.push({dist[v], c, v});
                }
            }
        }
        return std::pair{dist, prev};
    };
    int t; std::cin >> t;
    for (int i{}; i!=t; ++i) {
        Vertex s, d; std::cin >> s >> d;
        auto dest = d;
        auto [dist, prev] = dijkstra(g, s);
        if (!dist.contains(dest) || dist.at(dest).first == inf<int>) {
            std::cout << "Sorry, no line is available.\n";
            continue;
        }
        std::list<std::tuple<Vertex,Vertex,int>> path; // u, v, c
        while (d != s) {
            assert(prev.contains(d));
            path.push_front({prev[d],d,com_of_edge[{prev[d], d}]});
            d = prev[d];
        }
        for (auto it = path.begin(); it != path.end(); ) {
            if (std::next(it) != path.end() && std::get<2>(*it) == std::get<2>(*std::next(it))) {
                std::get<1>(*it) = std::get<1>(*std::next(it));
                path.erase(std::next(it));
            } else {
                ++it;
            }
        }
        std::cout << dist[dest].first << '\n';
        for (auto [u,v,c] : path) {
            std::cout << "Go by the line of company #" << c + 1 << " from " << u << " to " << v << ".\n";
        }
    }
}
} // namespace
