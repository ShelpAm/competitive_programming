#pragma once

// Problem: D. Palindrome Shuffle
// Contest: Educational Codeforces Round 174 (Rated for Div. 2)
// Judge: Codeforces
// URL: https://codeforces.com/contest/2069/problem/D
// Start: Tue 18 Feb 2025 11:01:21 PM CST
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
    std::string s;
    std::cin >> s;

    int first_diff{-1};
    for (int i{}; i != s.size() / 2; ++i) {
        if (s[i] != s[s.size() - 1 - i]) {
            first_diff = i;
            break;
        }
    }
    if (first_diff != -1) {
        s = s.substr(first_diff, s.size() - 2 * first_diff);
    }
    debug("s", s);

    int n{static_cast<int>(s.size())};

    s.insert(s.begin(), 0);

    std::vector<int> pal(s.size());
    for (int i{1}; i != s.size(); ++i) {
        if (s[i] == s[s.size() - i]) {
            pal[i] = 1;
        }
    }

    std::vector<int> bad;
    std::unordered_set<char> fuck;
    std::vector<std::vector<int>> pref(26, std::vector<int>(s.size()));
    std::vector<std::vector<int>> F(26, std::vector<int>(s.size()));
    for (int i{1}; i != s.size(); ++i) {
        for (int j{}; j != 26; ++j) {
            pref[j][i] = pref[j][i - 1];
        }
        if (pal[i] == 0) {
            bad.push_back(i);
            fuck.insert(s[i]);
            F[s[i] - 'a'][i] += 1;
        }
        pref[s[i] - 'a'][i] += 1;
    }

    if (bad.empty()) {
        std::cout << 0 << '\n';
        return;
    }

    debug("bad", bad);
    int mid{};
    for (auto const i : bad) {
        if (i <= s.size() / 2) {
            mid = i;
        }
    }
    assert(mid != 0);
    debug("mid", mid);

    int ans{inf<int>};
    for (int i{1}; i != s.size() / 2 + 1; ++i) {
        debug("i", i);
        int r{i}; // [i, r)

        // At least one of the bad pos in the left or right should show up in
        // the segment.
        if (i > bad.front()) {
            chmax(r, bad.back() + 1);
        }
        else { // i <= bad.front()
            chmax(r, mid + 1);
        }
        debug("initial r", r);

        for (char c{'a'}; auto const &[p, d] : std::views::zip(pref, F)) {
            if (fuck.contains(c)) {
                int D{inf<int>};
                chmin(D,
                      std::ranges::lower_bound(p, (p.back() / 2) + p[i - 1]) -
                          p.begin() + 1);
                chmin(D,
                      std::ranges::lower_bound(d, (d.back() / 2) + d[i - 1]) -
                          d.begin() + 1);
                chmax(r, D);
                debug("p", p);
                debug(std::string("for ") + c, r);
                c++;
            }
        }
        debug("last r", r);
        if (r <= n + 1) {
            debug("CHECKING MIN", r - i);
            chmin(ans, r - i);
        }
    }
    std::cout << ans << '\n';

    int f{inf<int>};
    for (int i{1}; i != s.size(); ++i) {
        for (int j{i}; j != s.size(); ++j) {
            auto t{s};
            std::unordered_map<char, int> o;
            for (int k{i}; k != j + 1; ++k) {
                ++o[s[k]];
            }
            bool bad{};
            int l, r;
            if (j <= s.size() / 2 || i > s.size() / 2) {
                l = i;
                r = j;
            }
            else {
                if (i > s.size() - j) {
                    l = s.size() - i + 1;
                    r = j;
                }
                else if (i < s.size() - j) {
                    l = i;
                    r = s.size() - j - 1;
                }
                else {
                    l = 0, r = -1;
                }
            }
            for (int k{l}; k != r + 1; ++k) {
                if (--o[t[k] = s[s.size() - k]] < 0) {
                    bad = true;
                }
            }
            if (!bad &&
                std::ranges::all_of(o | std::views::values,
                                    [](auto x) { return x % 2 == 0; }) &&
                [&] {
                    for (int k{1}; k != s.size(); ++k) {
                        if ((k < i || k > j) && t[k] != t[s.size() - k]) {
                            return false;
                        }
                    }
                    return true;
                }()) {
                if (chmin(f, j - i + 1)) {
                    debug("i, j", std::pair{i, j});
                }
            }
            if (i == 1 && j == s.size() - 1) {
                debug("o", o);
            }
        }
    }
    debug("ans", ans);
    debug("f", f);
    assert(f == ans);
}
} // namespace
