#pragma once

// Problem: D. Tree Jumps
// Contest: Educational Codeforces Round 175 (Rated for Div. 2)
// Judge: Codeforces
// URL: https://codeforces.com/contest/2070/problem/D
// Start: Thu 27 Feb 2025 10:58:03 PM CST
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
constexpr std::int_least64_t modular_inverse(std::int_least64_t n,
                                             std::int_least64_t mod)
{
    return pow(n % mod, mod - 2, mod);
}

template <std::int_least64_t mod> class Z {
  public:
    constexpr Z() : value_{} {}

    constexpr Z(std::int_least64_t n) : value_{n} {}

    constexpr Z &operator+=(Z rhs)
    {
        value_ += rhs.value_;
        if (value_ >= mod) {
            value_ -= mod;
        }
        return *this;
    }

    constexpr Z &operator-=(Z rhs)
    {
        value_ -= rhs.value_;
        if (value_ < 0) {
            value_ += mod;
        }
        return *this;
    }

    constexpr Z &operator*=(Z rhs)
    {
        value_ *= rhs.value_;
        value_ %= mod;
        return *this;
    }

    constexpr Z &operator/=(Z rhs)
    {
        value_ *= modular_inverse(rhs.value_, mod); // modular_inverse
        value_ %= mod;
        return *this;
    }

    friend constexpr Z operator+(Z lhs, Z rhs)
    {
        return lhs += rhs;
    }

    friend constexpr Z operator-(Z lhs, Z rhs)
    {
        return lhs -= rhs;
    }

    friend constexpr Z operator*(Z lhs, Z rhs)
    {
        return lhs *= rhs;
    }

    friend constexpr Z operator/(Z lhs, Z rhs)
    {
        return lhs /= rhs;
    }

    friend std::ostream &operator<<(std::ostream &os, Z rhs)
    {
        return os << rhs.value_;
    }

    friend std::istream &operator>>(std::istream &is, Z rhs)
    {
        is >> rhs.value_;
        rhs.value_ %= mod;
        if (rhs.value_ < 0) {
            rhs.value_ += mod;
        }
        return is;
    }

  private:
    std::int_least64_t value_; // n_ is guarenteed to be normalized.
};
void solve_case()
{
    int n;
    std::cin >> n;
    std::vector<int> pa(n);
    std::vector<int> d(n);
    std::vector<std::vector<int>> sons(n);
    for (int i{1}; auto &p : pa | std::views::drop(1)) {
        std::cin >> p;
        --p;
        sons[p].push_back(i);
        d[i++] = d[p] + 1;
    }

    debug("d", d);

    std::unordered_set<int> vs;
    std::vector<Z<mod998244353>> f(n);
    std::vector<Z<mod998244353>> sum_depth(n);
    f[0] = 1;
    sum_depth[0] = 1;
    std::queue<int> q; // idx
    for (auto const v : sons[0]) {
        f[v] = 1;
        sum_depth[1] += 1;
        vs.insert(v);
        q.push(v);
    }
    while (!q.empty()) {
        auto const u{q.front()};
        q.pop();

        debug("u", u);
        if (!vs.contains(u)) {
            f[u] = sum_depth[d[u] - 1] - f[pa[u]];
            sum_depth[d[u]] += f[u];
        }

        for (auto const v : sons[u]) {
            q.push(v);
        }
    }
    debug("f", f);

    std::cout << sum_of(f) << '\n';
}
} // namespace
