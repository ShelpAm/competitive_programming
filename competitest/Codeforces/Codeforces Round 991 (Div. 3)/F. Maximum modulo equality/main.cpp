#pragma once

// Problem: F. Maximum modulo equality
// Contest: Codeforces Round 991 (Div. 3)
// Judge: Codeforces
// URL: https://codeforces.com/problemset/problem/2050/F
// Start: Mon 23 Dec 2024 01:44:11 PM CST
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
namespace sparse_table {
// Note: 0-indexed
template <typename T, typename F> class Sparse_table {
  public:
    constexpr Sparse_table(std::vector<T> const &a)
        : _table(msb(a.size() + 1) + 1, a)
    {
        for (std::size_t i{1}; i != _table.size(); ++i) {
            for (std::size_t j{}; j + (1 << i) - 1 != _table[0].size(); ++j) {
                _table[i][j] =
                    _f(_table[i - 1][j], _table[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    [[nodiscard]] constexpr auto query(std::size_t l, std::size_t r) const
        -> decltype(F{}(T{}, T{}))
    {
        assert(r >= l);
        auto const k{msb(r - l + 1)};
        return _f(_table[k][l], _table[k][r - (1 << k) + 1]);
    }

  private:
    std::vector<std::vector<T>> _table;
    F _f;
};

namespace details {
template <typename T> struct Min {
    constexpr auto operator()(T const &lhs, T const &rhs) const -> T const &
    {
        return std::min(lhs, rhs);
    }
};
template <typename T> struct Max {
    constexpr auto operator()(T const &lhs, T const &rhs) const -> T const &
    {
        return std::max(lhs, rhs);
    }
};
} // namespace details

template <typename T> class Min_st : public Sparse_table<T, details::Min<T>> {
  public:
    using Sparse_table<T, details::Min<T>>::Sparse_table;
};
template <typename T> Min_st(std::vector<T>) -> Min_st<T>;
template <typename T> class Max_st : public Sparse_table<T, details::Max<T>> {
  public:
    using Sparse_table<T, details::Max<T>>::Sparse_table;
};
template <typename T> Max_st(std::vector<T>) -> Max_st<T>;
} // namespace sparse_table
void solve_case()
{
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    std::cin >> a;

    if (n == 1) {
        for (int i{}; i != q; ++i) {
            int l, r;
            std::cin >> l >> r;
            std::cout << 0 << ' ';
        }
        std::cout << '\n';
        return;
    }

    assert(n >= 2);

    std::vector<int> b(n - 1);
    for (int i{}; i != n - 1; ++i) {
        b[i] = a[i + 1] - a[i];
    }

    auto gcd{[](int x, int y) { return std::gcd(x, y); }};
    sparse_table::Sparse_table<int, decltype(gcd)> f(b);

    for (int i{}; i != q; ++i) {
        int l, r;
        std::cin >> l >> r;
        if (l == r) {
            std::cout << 0 << ' ';
            continue;
        }
        --l, r -= 2;
        if (l < 0 || r < 0) {
            std::cout << "ERROR" << std::flush;
        }
        std::cout << f.query(l, r) << ' ';
    }
    std::cout << '\n';
}
} // namespace
