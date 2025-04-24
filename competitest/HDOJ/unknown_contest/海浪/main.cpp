#pragma once

// Problem: 海浪
// Contest: unknown_contest
// Judge: HDOJ
// URL: https://acm.hdu.edu.cn/contest/problem?cid=1150&pid=1004
// Start: Fri 07 Mar 2025 08:54:21 PM CST
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
#include <fstream>
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
[[maybe_unused]] auto gen_rand() noexcept
{
    static std::mt19937_64 rng(
        std::chrono::steady_clock::now().time_since_epoch().count());
    return rng();
}
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
// Note: 0-indexed
template <typename T, typename F> class Sparse_table {
  public:
    constexpr Sparse_table(std::vector<T> const &base)
        : _table(msb(base.size()) + 1, base)
    {
        for (std::size_t i{1}; i != _table.size(); ++i) {
            for (std::size_t j{}; j + (1 << i) - 1 != _table[0].size(); ++j) {
                _table[i][j] =
                    _f(_table[i - 1][j], _table[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    [[nodiscard]] constexpr auto query(std::size_t l, std::size_t r) const
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
void solve_case()
{
    int n, q;
    std::cin >> n >> q;
    std::vector<i64> a(n);
    std::cin >> a;
    std::vector<std::pair<int, int>> queries(q);
    std::cin >> queries;

    n = 1000;
    a.assign(n, 0);
    for (auto &e : a) {
        e = gen_rand() % 10000000;
    }
    queries.clear();
    for (int i{}; i != n; ++i) {
        for (int j{i}; j != n; ++j) {
            queries.push_back({i + 1, j + 1});
        }
    }

    std::ofstream ofs("/home/shelpam/wofule");
    ofs << 1 << '\n' << n << ' ' << queries.size() << '\n';
    for (auto const e : a) {
        ofs << e << ' ';
    }
    ofs << '\n';
    for (auto const &[l, r] : queries) {
        ofs << l << ' ' << r << '\n';
    }

    // debug("a", a);
    // for (auto &e : a) {
    //     e *= 2;
    // }

    std::vector<std::pair<i64, i64>> interval(n - 1);
    for (int i{}; i != n - 1; ++i) {
        interval[i].first = std::ranges::min(a[i], a[i + 1]);
        interval[i].second = std::ranges::max(a[i], a[i + 1]);
    }
    // debug("interval", interval);
    struct Merge {
        std::pair<int, int> operator()(std::pair<i64, i64> lhs,
                                       std::pair<i64, i64> rhs) const
        {
            return {std::max(lhs.first, rhs.first),
                    std::min(lhs.second, rhs.second)};
        }
    };

    Sparse_table<std::pair<i64, i64>, Merge> st(interval);
    // [l, r)
    std::vector<int> R(n - 1); // Actual point that can be reached
    std::vector<int> f(n - 1);
    for (int i{}; i != n - 1; ++i) {
        R[i] = binary_search(
                   [&](auto r) {
                       if (r == i) {
                           return true;
                       }
                       auto const [p, q]{st.query(i, r - 1)};
                       return p < q;
                   },
                   i, n + 1) +
               1;
        f[i] = R[i] - i; // Get length
    }
    Max_st<int> max(f);
    // debug("R", R);

    i64 ans{};
    // i64 fy{};
    for (i64 i{1}; auto [x, y] : queries) {
        // debug("x,y", std::pair{x, y});
        --x;

        i64 tmp{};
        auto const r{binary_search([&](auto l) { return R[l] >= y; }, y - 1,
                                   x - 1, false)};
        // debug("r", r);
        chmax(tmp, y - r);
        if (r - 1 >= x) {
            chmax(tmp, max.query(x, r - 1));
        }

        // debug("ans i", tmp);
        // Brute force
        // {
        //     i64 fuck{1};
        //     for (int l{x}; l != y; ++l) {
        //         for (int r{l + 1}; r != y; ++r) {
        //             bool ok{true};
        //             i64 LOW{-inf<i64>}, HIGH{inf<i64>};
        //             for (int i{l}; i != r; ++i) {
        //                 chmin(HIGH, std::max(a[i], a[i + 1]));
        //                 chmax(LOW, std::min(a[i], a[i + 1]));
        //                 // chmin(HIGH, interval[i].second);
        //                 // chmax(LOW, interval[i].first);
        //             }
        //             if (LOW < HIGH) {
        //                 if (chmax(fuck, r - l + 1)) {
        //                     debug("fuck", fuck);
        //                 }
        //             }
        //         }
        //     }
        //     assert(tmp == fuck);
        //     fy += i * fuck % mod1e9p7;
        //     fy %= mod1e9p7;
        // }

        assert(tmp >= 1);
        ans += i * tmp % mod1e9p7;
        ans %= mod1e9p7;
        ++i;
    }
    // assert(ans == fy);
    std::cout << ans << '\n';
}
} // namespace
