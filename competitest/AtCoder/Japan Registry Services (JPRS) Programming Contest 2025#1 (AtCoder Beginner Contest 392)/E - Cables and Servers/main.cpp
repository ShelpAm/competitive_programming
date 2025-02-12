#pragma once

// Problem: E - Cables and Servers
// Contest: Japan Registry Services (JPRS) Programming Contest 2025#1 (AtCoder
// Beginner Contest 392) Judge: AtCoder URL:
// https://atcoder.jp/contests/abc392/tasks/abc392_e Start: Sun 09 Feb 2025
// 03:19:33 PM CST Author: ShelpAm

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
    if constexpr (shelpam::concepts::pair<T>) {
        istream >> t.first >> t.second;
    }
    else if constexpr (std::ranges::range<T>) {
        for (auto &ele : t) {
            istream >> ele;
        }
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
namespace shelpam {

class Disjoint_set_union {
  public:
    explicit Disjoint_set_union(int size) : _parent(size), _size(size, 1)
    {
        std::iota(_parent.begin(), _parent.end(), 0);
    }

    // With path compression
    auto find(int x) -> int
    {
        return _parent[x] == x ? x : _parent[x] = find(_parent[x]);
    }

    /// @return:
    /// false if there has been pair x,y in the set.
    /// true successfully united
    auto unite(int x, int y) -> bool
    {
        x = find(x), y = find(y);
        if (x == y) {
            return false;
        }
        _parent[y] = x;
        _size[x] += _size[y];
        return true;
    }
    [[nodiscard]] auto united(int x, int y) -> bool
    {
        return find(x) == find(y);
    }
    [[nodiscard]] auto size(int const x) -> int
    {
        return _size[find(x)];
    }

  private:
    std::vector<int> _parent;
    std::vector<int> _size;
};

using Dsu = Disjoint_set_union;
} // namespace shelpam
void solve_case()
{
    int n, m;
    std::cin >> n >> m;
    std::vector<std::pair<int, int>> a(m);
    std::cin >> a;

    std::vector<int> duplicated_edges;
    Dsu dsu(n);
    for (int i{}; auto &[u, v] : a) {
        if (!dsu.unite(--u, --v)) {
            duplicated_edges.push_back(i);
        }
        ++i;
    }

    std::set<int> s; // ancestors
    for (int i{}; i != n; ++i) {
        s.insert(dsu.find(i));
    }

    std::vector<std::tuple<int, int, int>> ans;
    while (s.size() != 1) {
        auto const u{a[duplicated_edges.back()].first};
        s.erase(dsu.find(u));

        auto const v{*s.begin()};

        dsu.unite(v, u);
        ans.push_back({duplicated_edges.back(), u, v});

        duplicated_edges.pop_back();
    }

    std::cout << ans.size() << '\n';
    for (auto const &[a, b, c] : ans) {
        std::cout << a + 1 << ' ' << b + 1 << ' ' << c + 1 << '\n';
    }

    assert(std::ranges::all_of(std::views::iota(0, n), [&](auto i) {
        return dsu.find(i) == dsu.find(0);
    }));
}
} // namespace
