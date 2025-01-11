#pragma once

// Problem: 完美主义追求者
// Contest: unknown_contest
// Judge: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/100007/B
// Start: Fri 10 Jan 2025 07:13:18 PM CST
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
constexpr auto pow(auto base, auto exp, std::uint_least64_t p)
{
    static_assert(sizeof(base) > sizeof(int), "Use of `int`s is bug-prone.");
    if (exp < 0) {
        throw std::invalid_argument{"Exponent should be non-negative"};
    }
    decltype(base) res{1};
    while (exp != 0) {
        if (exp.to_string()[0] & 1) {
            res = res * base % p;
        }
        base = base * base % p;
        exp /= 2;
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
namespace shelpam::multiprecision {
// Only supports positive numbers.
template <int Base> class Multiprecision {
    friend constexpr auto operator<(Multiprecision const &lhs,
                                    Multiprecision const &rhs) -> bool
    {
        if (lhs._bits.size() != rhs._bits.size()) {
            return lhs._bits.size() < rhs._bits.size();
        }
        for (auto i{lhs._bits.size()}; i != 0; --i) {
            if (lhs._bits[i - 1] != rhs._bits[i - 1]) {
                return lhs._bits[i - 1] < rhs._bits[i - 1];
            }
        }
        return false;
    }

    friend constexpr auto operator==(Multiprecision const &lhs,
                                     Multiprecision const &rhs) -> bool
    {
        return lhs._bits == rhs._bits;
    }

    friend constexpr auto operator<=(Multiprecision const &lhs,
                                     Multiprecision const &rhs) -> bool
    {
        return lhs < rhs || lhs == rhs;
    }

    static constexpr auto max_base_for_string{10};

  public:
    Multiprecision() : _bits{0} {}

    constexpr Multiprecision(std::string_view const s)
        : _bits(s.begin(), s.end())
    {
        std::reverse(_bits.begin(), _bits.end());
        for (auto &e : _bits) {
            e -= '0';
        }
    }

    constexpr Multiprecision(std::int_fast64_t n)
    {
        while (n != 0) {
            _bits.push_back(n % Base);
            n /= Base;
        }
        if (_bits.empty()) {
            _bits.push_back(0);
        }
    }

    auto operator+=(Multiprecision const &rhs) -> Multiprecision &
    {
        _bits.resize(std::max(_bits.size(), rhs._bits.size()) + 1);
        for (std::size_t i{}; i != rhs.size(); ++i) {
            _bits[i] += rhs._bits[i];
        }
        push_up();
        normalize();
        return *this;
    }

    auto operator-=(Multiprecision const &rhs) -> Multiprecision &
    {
        assert(rhs <= *this);
        for (std::size_t i{}; i != rhs.size(); ++i) {
            _bits[i] -= rhs._bits[i];
        }
        push_down();
        normalize();
        return *this;
    }

    auto operator*=(Multiprecision const &rhs) -> Multiprecision &
    {
        std::vector<int> result(size() + rhs.size() + 1);

        for (std::size_t i{}; i != size(); ++i) {
            for (std::size_t j{}; j != rhs.size(); ++j) {
                result[i + j] += _bits[i] * rhs._bits[j];
            }
        }

        _bits = std::move(result);
        push_up();

        normalize();
        return *this;
    }

    auto operator/=(Multiprecision const &rhs) -> Multiprecision &
    {
        std::vector<int> quotient(size());
        Multiprecision current;

        for (std::size_t i{_bits.size()}; i != 0; --i) {
            current._bits.insert(current._bits.begin(), _bits[i - 1]);
            current.normalize();
            while (rhs <= current) {
                current -= rhs;
                ++quotient[i - 1];
            }
        }

        _bits = std::move(quotient);
        normalize();
        return *this;
    }

    auto operator%=(Multiprecision const &rhs) -> Multiprecision &
    {
        std::vector<int> quotient(_bits.size());
        Multiprecision current;

        for (std::size_t i{_bits.size()}; i != 0; --i) {
            current._bits.insert(current._bits.begin(), _bits[i - 1]);
            current.normalize();
            while (rhs <= current) {
                current -= rhs;
                ++quotient[i - 1];
            }
        }

        return *this = std::move(current);
    }

    [[nodiscard]] auto size() const -> std::size_t
    {
        return _bits.size();
    }

    [[nodiscard]] auto to_string() const -> std::string
    {
        static_assert(Base <= max_base_for_string, "Only for 10 and lower");
        std::string s{_bits.begin(), _bits.end()};
        std::reverse(s.begin(), s.end());
        for (auto &e : s) {
            e += '0';
        }
        return s;
    }

  private:
    // Buffered constructor
    Multiprecision(std::size_t const size, int const _) : _bits(size) {}

    void normalize()
    {
        while (!_bits.empty() && _bits.back() == 0) {
            _bits.pop_back();
        }
        if (_bits.empty()) {
            _bits.push_back(0);
        }
    }

    void push_up()
    {
        for (std::size_t i{}; i != size() - 1; ++i) {
            _bits[i + 1] += _bits[i] / Base;
            _bits[i] %= Base;
        }
    }

    void push_down()
    {
        for (std::size_t i{}; i != size() - 1; ++i) {
            _bits[i + 1] += (_bits[i] - Base + 1) / Base;
            _bits[i] = (_bits[i] % Base + Base) % Base;
        }
    }

    std::vector<int> _bits; // Stored by little-endian.
};

template <int Base>
[[nodiscard]] constexpr auto operator+(Multiprecision<Base> const &lhs,
                                       Multiprecision<Base> const &rhs)
    -> Multiprecision<Base>
{
    return Multiprecision{lhs} += rhs;
}

template <int Base>
[[nodiscard]] constexpr auto operator-(Multiprecision<Base> const &lhs,
                                       Multiprecision<Base> const &rhs)
    -> Multiprecision<Base>
{
    return Multiprecision{lhs} -= rhs;
}

template <int Base>
[[nodiscard]] constexpr auto operator*(Multiprecision<Base> const &lhs,
                                       Multiprecision<Base> const &rhs)
    -> Multiprecision<Base>
{
    return Multiprecision{lhs} *= rhs;
}

template <int Base>
[[nodiscard]] constexpr auto operator/(Multiprecision<Base> const &lhs,
                                       Multiprecision<Base> const &rhs)
    -> Multiprecision<Base>
{
    return Multiprecision{lhs} /= rhs;
}

template <int Base>
[[nodiscard]] constexpr auto operator%(Multiprecision<Base> const &lhs,
                                       Multiprecision<Base> const &rhs)
    -> Multiprecision<Base>
{
    return Multiprecision{lhs} %= rhs;
}

namespace details {
constexpr auto default_base{10};
}
using Int = Multiprecision<details::default_base>;
} // namespace shelpam::multiprecision
void solve_case()
{
    std::string n;
    i64 p;
    std::cin >> n >> p;

    multiprecision::Int s{n};
    multiprecision::Int ans{1};

    if (p <= s) {
        std::cout << 0 << '\n';
        return;
    }

    // s < p (1e6)
    for (multiprecision::Int i{1}; i <= s; i += 1) {
        ans *= i;
        ans %= p;
    }

    std::cout << ans.to_string() << '\n';
}
} // namespace
