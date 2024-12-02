#pragma once

/*Problem: G. Geometric Gridlock*/
/*Contest: JXNU ICPC Kunming Selection*/
/*Judge: Codeforces*/
/*URL: https://codeforces.com/gym/563673/problem/G*/
/*Start: Mon 04 Nov 2024 09:07:32 PM CST*/
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
void solve_case()
{
    using Shape = std::vector<std::string>;

    auto now = std::chrono::steady_clock::now();

    std::vector<std::function<Shape(Shape)>> trans{
        {[](auto s) {
            for (int i{}; i != s.size() / 2; ++i) {
                std::swap(s[i], s[s.size() - 1 - i]);
            }
            return s;
        }},
        {[](auto s) {
            for (int i{}; i != s.size(); ++i) {
                for (int j{}; j != s[i].size() / 2; ++j) {
                    std::swap(s[i][j], s[i][s[i].size() - 1 - j]);
                }
            }
            return s;
        }}};

    auto rotate{[](auto s) {
        auto const n{s.size()};
        auto const m{s[0].size()};
        Shape t(m, std::string(n, 0));
        for (int i{}; i != n; ++i) {
            for (int j{}; j != m; ++j) {
                t[j][n - 1 - i] = s[i][j];
            }
        }
        return t;
    }};

    int n, m;
    std::cin >> n >> m;

    if (n * m % 5 != 0) {
        std::cout << "no\n";
        return;
    }

    std::vector<std::pair<char, Shape>> shapes{
        {'F', {".oo", "oo.", ".o."}}, {'I', {"ooooo"}},
        {'L', {"oooo", "o..."}},      {'N', {"ooo.", "..oo"}},
        {'P', {"ooo", "oo."}},        {'T', {"ooo", ".o.", ".o."}},
        {'U', {"o.o", "ooo"}},        {'V', {"ooo", "..o", "..o"}},
        {'W', {"o..", "oo.", ".oo"}}, {'X', {".o.", "ooo", ".o."}},
        {'Y', {"oooo", ".o.."}},      {'Z', {"oo.", ".o.", ".oo"}},
    };

    constexpr std::string_view order{"LPUVIYTNZWXF"};

    auto const origin_size{shapes.size()};

    for (int i{}; i != origin_size; ++i) {
        auto s{shapes[i]};
        for (int j{}; j != 4; ++j) {
            s.second = rotate(s.second);
            for (int k{}; k != 4; ++k) {
                auto t{s};
                for (int l{}; l != 2; ++l) {
                    if (k & 1 << l) {
                        t.second = trans[l](t.second);
                    }
                }
                shapes.push_back(t);
            }
        }
    }

    std::ranges::sort(shapes);
    shapes.erase(std::unique(shapes.begin(), shapes.end()), shapes.end());

    std::ranges::sort(shapes, [&](auto const &l, auto const &r) {
        return order.find(l.first) < order.find(r.first);
    });

    // for (auto const &[ch, s] : shapes) {
    //     std::cerr << ch << '\n';
    //     for (int i{}; i != s.size(); ++i) {
    //         for (int j{}; j != s[i].size(); ++j) {
    //             std::cerr << s[i][j];
    //         }
    //         std::cerr << '\n';
    //     }
    // }
    // std::cerr << '\n';

    Shape pic(n, std::string(m, '.'));

    auto check{[&](Shape const &s, int x, int y, char ch) {
        int p = s[0].find('o');
        if (x - p < 0 || x - p + s.size() > n ||
            y + s[0].size() > m) { // Overflow
            return false;
        }
        for (int i{}; i != s.size(); ++i) {
            for (int j{}; j != s[i].size(); ++j) {
                if (s[i][j] == 'o') {
                    if (pic[x + i - p][y + j] != '.') {
                        return false;
                    }
                    for (int l{-1}; l != 2; ++l) {
                        for (int r{-1}; r != 2; ++r) {
                            if (std::abs(l) + std::abs(r) != 1) {
                                continue;
                            }
                            if (x + i - p + l >= 0 && x + i - p + l < n &&
                                y + j + r >= 0 && y + j + r < m &&
                                pic[x + i - p + l][y + j + r] == ch) {
                                return false;
                            }
                        }
                    }
                }
            }
        }
        return true;
    }};

    auto place{[&](Shape const &s, int x, int y, char ch) {
        auto const p{s[0].find('o')};
        for (int i{}; i != s.size(); ++i) {
            for (int j{}; j != s[i].size(); ++j) {
                if (s[i][j] == 'o') {
                    pic[x + i - p][y + j] = ch;
                }
            }
        }
    }};

    bool ok{};
    auto dfs{[&](auto dfs, int i) {
        if (i == n * m) {
            bool all{true};
            for (auto const &e : pic) {
                for (auto const f : e) {
                    if (f == '.') {
                        all = false;
                    }
                }
            }
            if (all) {
                ok = true;
            }
            return;
        }

        // auto t = std::chrono::steady_clock::now();
        // if (t - now >= std::chrono::milliseconds{900}) {
        //     std::cout << "no\n";
        //     std::exit(0);
        // }

        auto const x{i / m};
        auto const y{i % m};

        if (pic[x][y] != '.') {
            dfs(dfs, i + 1);
            return;
        }

        for (auto const &[ch, s] : shapes) {
            if (!check(s, x, y, ch)) {
                continue;
            }
            // Place
            place(s, x, y, ch);
            dfs(dfs, i + 1);
            if (ok) {
                return;
            }
            place(s, x, y, '.');
        }
    }};
    dfs(dfs, 0);

    if (!ok) {
        std::cout << "no\n";
    }
    else {
        std::cout << "yes\n";
        for (auto const &e : pic) {
            std::cout << e << '\n';
        }
    }
}
} // namespace
