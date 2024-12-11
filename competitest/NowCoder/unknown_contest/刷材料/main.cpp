#pragma once

/*Problem: 刷材料*/
/*Contest: unknown_contest*/
/*Judge: NowCoder*/
/*URL: https://ac.nowcoder.com/acm/contest/97487/E*/
/*Start: Sat 07 Dec 2024 02:26:55 PM CST*/
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
    // std::cin >> t;
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
class Combinatorics {
  public:
    /// @param  upper_bound  Maximum number whose inverse can be queried.
    /// @param  mod  Modulos of the results.
    Combinatorics(int upper_bound, std::int_fast64_t const mod)
        : _inverse(upper_bound + 1), _factorial(upper_bound + 1),
          _prefix_inverse(upper_bound + 1), _upper_bound(upper_bound), _mod{mod}
    {
        _inverse[0] = _inverse[1] = _factorial[0] = _factorial[1] =
            _prefix_inverse[0] = _prefix_inverse[1] = 1;
        for (std::int_fast64_t i{2}; i != upper_bound + 1; ++i) {
            _inverse[i] = (mod - mod / i) * _inverse[mod % i] % mod;
            _factorial[i] = _factorial[i - 1] * i % mod;
            _prefix_inverse[i] = _prefix_inverse[i - 1] * _inverse[i] % mod;
        }
    }

    [[nodiscard]] auto inverse(int const n) const -> std::int_fast64_t
    {
        return _inverse[n];
    }

    [[nodiscard]] auto factorial(int const n) const -> std::int_fast64_t
    {
        assert(n >= 0);
        assert(n <= _upper_bound);
        return _factorial[n];
    }

    [[nodiscard]] auto prefix_inverse(int const n) const -> std::int_fast64_t
    {
        assert(n >= 0);
        assert(n <= _upper_bound);
        return _prefix_inverse[n];
    }

    auto combination(int const n, int const m) -> std::int_fast64_t
    {
        assert(n >= 0);
        assert(n <= _upper_bound);
        if (n < m) {
            return 0;
        }
        return _factorial[n] * _prefix_inverse[m] % _mod *
               _prefix_inverse[n - m] % _mod;
    }

  private:
    std::vector<std::int_fast64_t> _inverse;
    std::vector<std::int_fast64_t> _factorial;
    std::vector<std::int_fast64_t> _prefix_inverse;
    std::int_fast64_t _upper_bound;
    std::int_fast64_t _mod;
};
void solve_case()
{
    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector<int> a(k);
    std::cin >> a;
    m -= n;

    i64 ans{};
    Combinatorics c{200000, mod1e9p7};

    int depth{};
    auto dfs{[&](auto dfs, int i, int sum, i64 inv, int cnt) -> void {
        if (sum >= m) {
            (ans += inv * c.factorial(cnt) % mod1e9p7) %= mod1e9p7;
            debug(std::string(2 * depth, ' ') + "delta",
                  inv * c.factorial(cnt) % mod1e9p7);
        }
        if (i == k) {
            return;
        }
        for (int j{}; sum + (j - 1) * a[i] < m; ++j) {
            ++depth;
            std::cerr << std::string(2 * depth, ' ') << "in " << i
                      << "-th, selected " << j << '\n';
            dfs(dfs, i + 1, sum + (j * a[i]),
                inv * c.prefix_inverse(j) % mod1e9p7, cnt + j);
            --depth;
        }
    }};
    dfs(dfs, 0, 0, 1, 0);
    std::cout << ans << '\n';
}
} // namespace
