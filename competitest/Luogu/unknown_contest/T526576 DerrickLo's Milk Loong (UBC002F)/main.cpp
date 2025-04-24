#pragma once

// Problem: T526576 DerrickLo's Milk Loong (UBC002F)
// Contest: unknown_contest
// Judge: Luogu
// URL: https://www.luogu.com.cn/problem/T526576?contestId=203994
// Start: Sun 13 Apr 2025 03:14:55 PM CST
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
    return std::accumulate(coll.begin(), coll.end(),
                           std::ranges::range_value_t<decltype(coll)>{});
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
class Sieve {
  public:
    Sieve(int const upper_bound) : _min_factor(upper_bound + 1, 0)
    {
        for (int i = 2; i != upper_bound + 1; ++i) {
            if (_min_factor[i] == 0) {
                _primes.push_back(i);
                _min_factor[i] = i;
            }
            for (auto const p : _primes) {
                if (i * p > upper_bound || p > _min_factor[i]) {
                    break;
                }
                _min_factor[i * p] = p;
            }
        }
    }

    // Time complexity: O(sqrt(x))
    [[nodiscard]] auto factorize(std::uint_fast64_t x) const
        -> std::map<std::uint_fast64_t, std::uint_fast64_t>
    {
        std::map<std::uint_fast64_t, std::uint_fast64_t> res;
        assert(x <= (_min_factor.size() - 1) * (_min_factor.size() - 1));
        for (auto const p : _primes) {
            if (p > x) {
                break;
            }
            while (x % p == 0) {
                x /= p;
                ++res[p];
            }
        }
        if (x >= _min_factor.size()) {
            ++res[x];
        }
        return res;
    }

    [[nodiscard]] auto is_prime(int x) const -> bool
    {
        return _min_factor[x] == x;
    }

    [[nodiscard]] auto primes() const -> std::vector<int> const &
    {
        return _primes;
    }

  private:
    std::vector<int> _primes;
    std::vector<int> _min_factor;
};
void solve_case()
{
    int n;
    // std::cin >> n;

    Sieve s(5e6);

    auto lcm = [](auto &&r) {
        i64 res{1};
        for (auto e : r) {
            res = std::lcm(res, e);
        }
        return res;
    };

    for (n = 3; n != 5e6; ++n) {
        // if (!s.is_prime(n)) {
        //     continue;
        // }

        auto solve = [&](int n) {
            for (int l = 2; l <= 3; ++l) {
                for (int i{1}; i != 20; ++i) {
                    std::vector<int> a(l + 1);
                    std::ranges::iota(a, i);
                    auto m = lcm(a);

                    std::bitset<5'000'000> bs;
                    bs.set(0);
                    for (auto e : a) {
                        bs |= bs << e;
                    }
                    if (bs.test(m)) {
                        // std::cout << "Yes" << std::endl;
                        return true;
                    }
                }
            }
            return false;
        };
        if (!solve(n)) {
            std::cout << "n = " << n << " ";
            std::cout << "No" << std::endl;
        }

        // auto solve = [lcm](int n) {
        //     for (int l = 2; l <= 3; ++l) {
        //         for (int i{1}; i != 20; ++i) { // begin
        //             std::vector<int> a(l + 1);
        //             std::ranges::iota(a, i);
        //             auto m = lcm(a);
        //
        //             std::vector<int> cnt(l + 1);
        //             auto check = [&](auto const &cnt) {
        //                 i64 s{};
        //                 for (int i{}; i != cnt.size(); ++i) {
        //                     s += a[i] * cnt[i];
        //                 }
        //                 return s == m;
        //             };
        //             std::set<std::pair<int, std::vector<int>>> ans;
        //             auto dfs = [&](auto dfs, int i, int now) -> void {
        //                 if (i == cnt.size()) {
        //                     if (check(cnt)) {
        //                         ans.insert({l, cnt});
        //                     }
        //                     return;
        //                 }
        //                 for (auto e : std::views::iota(
        //                          i == cnt.size() - 1 ? std::max(1, n - now) :
        //                          1, n - now + 1)) {
        //                     cnt[i] = e;
        //                     dfs(dfs, i + 1, now + e);
        //                     if (ans.size() == 1) {
        //                         return;
        //                     }
        //                 }
        //             };
        //             cnt[0] = 1;
        //             dfs(dfs, 1, 1);
        //             std::ranges::reverse(a);
        //             std::ranges::reverse(cnt);
        //             cnt[0] = 1;
        //             dfs(dfs, 1, 1);
        //             if (!ans.empty()) {
        //                 std::cout << "n = " << n << std::endl;
        //                 for (auto [d, cnt] : ans | std::views::take(5)) {
        //                     for (auto e : cnt) {
        //                         std::cout << e << ' ';
        //                     }
        //                     std::cout << " | a: ";
        //                     for (auto e : a) {
        //                         std::cout << e << ' ';
        //                     }
        //                     std::cout << " , diff: "
        //                               << d
        //                               // << " lcm: " << lcm(a)
        //                               //       << " sum: " << sum_of(a)
        //                               << std::endl;
        //                 }
        //                 return true;
        //             }
        //         }
        //     }
        //     return false;
        // };

        // if (!solve(n)) {
        //     std::cout << "DIDN'T FIND FOR n = " << n << std::endl;
        // }

        // std::vector<int> a(n + 1);
        // a[0] = 1;
        // auto check = [&](auto const &a) { return sum_of(a) == lcm(a); };
        // std::set<std::pair<int, std::vector<int>>> ans;
        // auto dfs = [&](auto dfs, int i) -> void {
        //     if (i == n + 1) {
        //         if (check(a | std::views::drop(1))) {
        //             std::vector<int> tmp = {a.begin() + 1, a.end()};
        //             ans.insert({tmp.back() - tmp.front(), tmp});
        //         }
        //         return;
        //     }
        //     for (auto e : std::views::iota(a[i - 1], 10)) {
        //         if (e - a[1] > 4) {
        //             break;
        //         }
        //         a[i] = e;
        //         dfs(dfs, i + 1);
        //     }
        // };
        // dfs(dfs, 1);
        // std::cout << "n = " << n << std::endl;
        // for (auto [d, a] : ans | std::views::take(5)) {
        //     for (auto e : a) {
        //         std::cout << e << ' ';
        //     }
        //     std::cout << " , diff: "
        //               << d
        //               // << " lcm: " << lcm(a)
        //               //       << " sum: " << sum_of(a)
        //               << std::endl;
        // }
    }
}
} // namespace
