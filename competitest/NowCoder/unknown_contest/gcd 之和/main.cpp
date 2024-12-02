#pragma once

/*Problem: gcd 之和*/
/*Contest: unknown_contest*/
/*Judge: NowCoder*/
/*URL: https://ac.nowcoder.com/acm/contest/93820/B*/
/*Start: Sat 16 Nov 2024 08:03:01 PM CST*/
/*Author: ShelpAm*/

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
[[maybe_unused]] constexpr std::uint_fast64_t mod998244353{998'244'353ULL};
[[maybe_unused]] constexpr std::uint_fast64_t mod1e9p7{1'000'000'007ULL};
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
    return std::accumulate(coll.begin(), coll.end(), std::int_fast64_t{});
}
constexpr auto pow(auto a, std::int_fast64_t b, std::uint_fast64_t p)
{
    static_assert(sizeof(a) > sizeof(int), "Use of int is bug-prone.");
    if (b < 0) {
        throw std::invalid_argument{"Invalid exponent. It should be positive."};
    }
    decltype(a) res{1};
    while (b != 0) {
        if ((b & 1) == 1) {
            res = res * a % p;
        }
        a = a * a % p;
        b >>= 1;
    }
    return res;
}
auto binary_search(std::invocable<std::int_fast64_t> auto check,
                   std::int_fast64_t ok, std::int_fast64_t ng,
                   bool check_ok = true) -> std::int_fast64_t
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
    return sizeof(i) * CHAR_BIT - 1 - std::countl_zero(i);
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
        try {
            std::cerr << "Test case " << i << '\n';
            solve_case();
        }
        catch (std::exception &e) {
            std::cerr << "Exception: " << e.what() << '\n';
        }
    }
    return 0;
}
namespace {
using i64 = std::int_fast64_t;
using u64 = std::uint_fast64_t;
namespace sparse_table {
// Note: 0-indexed
template <typename T, typename F> class Sparse_table {
  public:
    constexpr Sparse_table(std::vector<T> table)
        : _table(msb(table.size()) + 1, std::move(table))
    {
        for (std::size_t i{1}; i != _table.size(); ++i) {
            for (std::size_t j{}; j != _table[0].size(); ++j) {
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
struct Gcd {
    auto operator()(auto const &a, auto const &b) const
    {
        return std::gcd(a, b);
    }
};
struct Bit_or {
    auto operator()(int i, int j) const
    {
        return i | j;
    }
};
void solve_case()
{
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    std::cin >> a;
    sparse_table::Sparse_table<int, Gcd> st{a};
    sparse_table::Sparse_table<int, Bit_or> bit_or{a};

    __int128_t ans{};
    for (int i{}; i != n; ++i) {
        // Find right most whose gcd and bit-wise or is the same as [i,i].
        auto d{a[i]};
        auto bo{a[i]};
        for (int j{i}; j != n;) {
            d = std::gcd(d, a[j]);
            bo |= a[j];
            auto const nj{binary_search(
                [&](auto nj) {
                    return st.query(i, nj) == d && bit_or.query(i, nj) == bo;
                },
                j, n)};
            ans += static_cast<__int128_t>(d) * bo * (nj - j + 1);
            j = nj + 1;
        }
    }

    std::vector<int> t;
    while (ans != 0) {
        t.push_back(ans % 10);
        ans /= 10;
    }
    std::ranges::reverse(t);
    for (auto e : t) {
        std::cout << e;
    }
    std::cout << '\n';
}
} // namespace
