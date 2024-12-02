#pragma once

/*Problem: C. Copycat Catcher*/
/*Contest: JXNU ICPC Kunming Selection*/
/*Judge: Codeforces*/
/*URL: https://codeforces.com/gym/563673/problem/C*/
/*Start: Mon 04 Nov 2024 07:28:36 PM CST*/
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
// note: zero-indexed
template <std::size_t Base> class Hash {
  public:
    template <typename R>
    constexpr Hash(R const &range)
        : _hash_value(range.size() + 1), _pow_base(range.size() + 1)
    {
        for (std::size_t i{1}; i != _hash_value.size(); ++i) {
            _hash_value[i] = _hash_value[i - 1] * Base + range[i - 1];
        }

        _pow_base[0] = 1;
        for (std::size_t i{1}; i != _pow_base.size(); ++i) {
            _pow_base[i] = _pow_base[i - 1] * Base;
        }
    }

    [[nodiscard]] auto query(std::size_t l, std::size_t r) const -> std::size_t
    {
        return _hash_value[r + 1] - (_hash_value[l] * _pow_base[r - l + 1]);
    }

  private:
    std::vector<std::size_t> _hash_value;
    std::vector<std::size_t> _pow_base;
};
void solve_case()
{
    int n;
    std::cin >> n;
    std::vector<std::string> tokens(n);
    std::cin >> tokens;

    constexpr std::size_t base{131};

    auto get_hash{[&](std::vector<std::string> const &tokens) {
        std::vector<u64> h(tokens.size());
        std::unordered_map<char, Hash<base>> pos_hash;
        std::unordered_map<char, std::vector<int>> pos_onehot;
        for (int i{}; i != tokens.size(); ++i) {
            h[i] = tokens[i].size() == 1 && std::isalpha(tokens[i][0])
                       ? 0
                       : Hash<base>{tokens[i]}.query(0, tokens[i].size() - 1);
        }
        //
        // for (auto const &e : tokens) {
        //     std::cerr << e << ' ';
        // }
        // std::cerr << '\n';
        // debug("h", h);

        for (char c = 0; c != 127; ++c) {
            if (std::isalpha(c)) {
                pos_onehot[c].assign(tokens.size(), 0);
                for (int idx{}; auto const &token : tokens) {
                    if (token.size() == 1 && c == token[0]) {
                        pos_onehot[c][idx] = 1;
                    }
                    ++idx;
                }
                pos_hash.insert({c, Hash<131>{pos_onehot[c]}});
            }
        }

        Hash<base> hash{h};
        return std::pair{hash, pos_hash};
    }};

    auto const [hash, pos_hash]{get_hash(tokens)};

    int q;
    std::cin >> q;
    for (int i{}; i != q; ++i) {
        int m;
        std::cin >> m;
        std::vector<std::string> line(m);
        std::cin >> line;
        auto const [ds, onehot]{get_hash(line)};

        auto const hashvalue{ds.query(0, m - 1)};
        std::vector<u64> onehot_hash;
        for (auto const &[_, v] : onehot) {
            onehot_hash.push_back(v.query(0, m - 1));
        }
        std::ranges::sort(onehot_hash);

        auto solve{[&]() {
            for (int i{}; i + m - 1 != n; ++i) {
                if (hashvalue == hash.query(i, i + m - 1)) {
                    std::vector<u64> f;
                    for (auto const &[_, v] : pos_hash) {
                        f.push_back(v.query(i, i + m - 1));
                    }
                    std::ranges::sort(f);
                    if (f == onehot_hash) {
                        std::cout << "yes\n";
                        return;
                    }
                }
            }
            std::cout << "no\n";
        }};
        solve();
    }
}
} // namespace
