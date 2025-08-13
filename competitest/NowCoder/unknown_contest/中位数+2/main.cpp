#pragma once

// Problem: 中位数+2
// Contest: unknown_contest
// Judge: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/115567/D
// Start: Wed 13 Aug 2025 03:34:25 PM CST
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
    return std::accumulate(
        coll.begin(), coll.end(),
        typename std::remove_cvref_t<decltype(coll)>::value_type{});
}
template <typename T> constexpr T pow(T base, auto exp, std::integral auto p)
{
    static_assert(sizeof(base) > sizeof(int), "Use of `int`s is bug-prone.");
    if (exp < 0) {
        base = pow(base, p - 2, p);
        exp = -exp;
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
        auto const x = (ok + ng) / 2;
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
namespace math {

using Value_type = std::uint_least64_t;
// template <std::unsigned_integral Value_type>
class Xor_linear_basis {
    static constexpr auto num_bits = sizeof(Value_type) * CHAR_BIT;

  public:
    void insert(Value_type x)
    {
        for (int i{num_bits - 1}; i != -1; --i) {
            if ((x >> i & 1) == 0) {
                continue;
            }
            // x's i-th bit is 1
            if (bases_.at(i) == 0) {
                bases_.at(i) = x;
                return;
            }
            // There exists a basis for i-th bit.
            assert(bases_.at(i) >> i & 1);
            x ^= bases_.at(i);
        }
    }

    [[nodiscard]] bool find(Value_type x) const
    {
        for (int i{num_bits - 1}; i != -1; i--) {
            if ((x >> i & 1) == 0) {
                continue;
            }

            if (bases_.at(i) == 0) {
                return false;
            }

            x ^= bases_.at(i);
        }

        return true;
    }

    // Make bases_[i] the most clear (its lower bits will be eliminated.)
    std::vector<Value_type> rebuild()
    {
        std::vector<Value_type> bases;
        for (std::size_t i{}; i != num_bits; ++i) {
            for (std::size_t j{i - 1}; j != -1UZ; --j) {
                if ((bases_.at(i) >> j & 1) != 0 && bases_.at(j) != 0) {
                    bases_.at(i) ^= bases_.at(j);
                }
            }
            if (bases_.at(i) != 0) {
                bases.push_back(bases_.at(i));
            }
        }
        return bases;
    }

    [[nodiscard]] std::array<Value_type, num_bits> bases() const
    {
        return bases_;
    }

  private:
    // bases_[i] controls i-th bit.
    std::array<Value_type, num_bits> bases_{};
};

} // namespace math
namespace {
using i64 = std::int_least64_t;
using i128 = __int128_t;
using u64 = std::uint_least64_t;
using u128 = __uint128_t;
void solve_case()
{
    using namespace ::shelpam;
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    std::cin >> a;

    math::Xor_linear_basis xlb;
    for (auto e : a) {
        xlb.insert(e);
    }
    auto t = xlb.rebuild();
    auto k = 1 << (t.size() - 1);
    int s{};
    for (int i{}; i != t.size(); ++i) {
        if (k & 1 << i) {
            s ^= t[i];
        }
    }
    std::cout << s << '\n';

    // std::multiset<int> s;
    // for (int i{1}; i != 1 << n; ++i) {
    //     int x{};
    //     for (int j{}; j != n; ++j) {
    //         if (i & 1 << j) {
    //             x ^= a[j];
    //         }
    //     }
    //     s.insert(x);
    // }
    // debug("s", s);
}
} // namespace
