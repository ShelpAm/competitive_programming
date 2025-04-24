#pragma once

// Problem: D. Game With Triangles
// Contest: Codeforces Round 1000 (Div. 2)
// Judge: Codeforces
// URL: https://codeforces.com/problemset/problem/2063/D
// Start: Tue 18 Feb 2025 10:07:45 PM CST
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
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n), b(m);
    std::cin >> a >> b;

    int kmax{};
    if (auto const [min, max]{std::ranges::minmax(n, m)}; min * 2 < max) {
        kmax = min;
    }
    else {
        kmax = (n + m) / 3;
    }

    std::vector<std::set<int>> s{{a.begin(), a.end()}, {b.begin(), b.end()}};
    std::vector<std::priority_queue<std::tuple<int, int, int>,
                                    std::vector<std::tuple<int, int, int>>,
                                    std::ranges::greater>>
        selected(2);

    std::cout << kmax << '\n';

    i64 ans{};
    for (int i{1}; i != kmax + 1; ++i) {
        std::vector<int> candidates(2);
        bool at_least_one{};
        for (int id{}; auto &set : s) {
            // Originally set.size() - s[id ^ 1].size() >= 2, but to avoid
            // overflow of std::size_t.
            if (set.size() >= 2 + selected[id ^ 1].size()) {
                candidates[id] = *set.rbegin() - *set.begin();
                at_least_one = true;
            }
            ++id;
        }
        assert(at_least_one);
        debug("candidates", candidates);

        auto const better{std::ranges::max_element(candidates) -
                          candidates.begin()};
        s[better].erase(*s[better].begin());
        s[better].erase(*s[better].rbegin());

        // We don't explicitly remove the point from the set, but memorize it
        // via the size of each `selected`. That means, if the size of a
        // `selected` is x, then it should require x points from the other set.
        // So we *should* check every place where involves the size of the sets.

        // No points available
        if (s[better ^ 1].size() == selected[better].size()) {
            // Number of left points in another set - selected[better].size()
            // (prefetched size) ==
            // 0 Remove the worst from it
            auto const [_, l, r]{selected[better ^ 1].top()};
            selected[better ^ 1].pop();
            s[better ^ 1].insert(l);
            s[better ^ 1].insert(r);
            ans -= r - l;
        }
        ans += candidates[better];

        std::cout << ans << ' ';
    }
    std::cout << '\n';
}
} // namespace
