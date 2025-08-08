#pragma once

// Problem: M. Ordainer of Inexorable Judgment
// Contest: The 2024 ICPC Asia Nanjing Regional Contest (The 3rd Universal Cup.
// Stage 16: Nanjing) Judge: Codeforces URL:
// https://codeforces.com/gym/105484/problem/M Start: Fri 18 Jul 2025 02:23:45
// PM CST Author: ShelpAm

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
    std::cerr << std::setprecision(my_precision);
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
#pragma once

#include <array>
#include <cmath>
#include <cstdint>
#include <numbers>

template <typename Value_type, std::size_t Dimension> struct Vector {
    friend auto operator+(Vector lhs, Vector const &rhs)
    {
        return lhs += rhs;
    }

    friend auto operator-(Vector lhs, Vector const &rhs)
    {
        return lhs -= rhs;
    }

    friend auto dot(Vector const &lhs, Vector const &rhs) -> Value_type
    {
        Value_type result{};
        for (std::size_t i{}; i != Dimension; ++i) {
            result += lhs.coordinate[i] * rhs.coordinate[i];
        }
        return result;
    }

    /*friend auto cross(Vector const &lhs, Vector const &rhs) -> Vector {}*/

    auto operator+=(Vector const &rhs) -> Vector &
    {
        for (std::size_t i{}; i != Dimension; ++i) {
            coordinate[i] += rhs.coordinate[i];
        }
        return *this;
    }

    auto operator-=(Vector const &rhs) -> Vector &
    {
        for (std::size_t i{}; i != Dimension; ++i) {
            coordinate[i] -= rhs.coordinate[i];
        }
        return *this;
    }

    [[nodiscard]] double length() const
    {
        return std::sqrt(dot(*this, *this));
    }

    std::array<Value_type, Dimension> coordinate{};
};

template <typename Value_type> using Vector2d = Vector<Value_type, 2>;

template <typename Value_type> class Line2d {
    friend Vector<Value_type, 2> intersect(Line2d const &lhs, Line2d const &rhs)
    {
    }

    std::array<Vector<Value_type, 2>, 2> points;
};

/// @return angle in Radians
double polar_angle(Vector2d<std::int_least64_t> v)
{
    auto result = std::atan2(v.coordinate[1], v.coordinate[0]);
    if (result < 0) {
        result += 2 * std::numbers::pi;
    }
    return result;
}
using namespace shelpam;
namespace {
using i64 = std::int_least64_t;
using i128 = __int128_t;
using u64 = std::uint_least64_t;
using u128 = __uint128_t;
void solve_case()
{
    int n, x, y, d;
    int t;
    std::cin >> n >> x >> y >> d >> t;
    std::vector<std::pair<int, int>> a(n);
    std::cin >> a;

    auto get_angle = [&](int i) {
        return polar_angle({{a[i].first, a[i].second}});
    };
    using std::numbers::pi;
    debug("polar_angle({{1, -1}})", polar_angle({{1, -1}}));
    assert(std::abs(polar_angle({{1, 0}}) - 0) < eps);
    assert(std::abs(polar_angle({{1, 1}}) - pi / 4) < eps);
    assert(std::abs(polar_angle({{0, 1}}) - pi / 2) < eps);
    assert(std::abs(polar_angle({{-1, 1}}) - 3 * pi / 4) < eps);
    assert(std::abs(polar_angle({{-1, 0}}) - 4 * pi / 4) < eps);
    assert(std::abs(polar_angle({{-1, -1}}) - 5 * pi / 4) < eps);
    assert(std::abs(polar_angle({{0, -1}}) - 6 * pi / 4) < eps);
    assert(std::abs(polar_angle({{1, -1}}) - 7 * pi / 4) < eps);

    for (int i{}; i != n; ++i) {
        debug("i", i);
        debug("angle", get_angle(i) * 180 / std::numbers::pi);
    }

    std::vector<int> s(n);
    std::ranges::iota(s, 0);
    std::ranges::sort(s, {}, get_angle);
    int p{-1}, q{-1};
    for (int i{}; i != n; ++i) {
        if (std::fmod(get_angle(s[(i + 1) % n]) - get_angle(s[i]) + (2 * pi),
                      2 * pi) > pi) {
            p = s[(i + 1) % n];
            q = s[i];
        }
    }
    assert(p != -1 && q != -1);

    debug("p, q", std::pair{p, q});

    auto f = get_angle(p) -
             std::asin(std::min(
                 1., d / Vector2d<i64>{{a[p].first, a[p].second}}.length()));
    f = std::fmod(f + (2 * pi), 2 * pi);
    debug("-1", std::fmod(-1, 3));
    auto g = get_angle(q) +
             std::asin(std::min(
                 1., d / Vector2d<i64>{{a[q].first, a[q].second}}.length()));
    g = std::fmod(g, 2 * pi);

    auto quo = t / std::numbers::pi / 2;
    auto rounds = std::trunc(quo);
    auto rem = t - (rounds * 2 * std::numbers::pi);
    assert(std::abs(rem + 2 * pi * rounds - t) < eps);
    debug("rounds rem", std::pair{rounds, rem});
    auto round_value =
        std::fmod(g - f + (2 * std::numbers::pi), 2 * std::numbers::pi);
    debug("rounds_value", round_value);
    auto ans = rounds * round_value;
    auto start = polar_angle({{x, y}});

    auto inter = [](double l, double r, double s, double t) {
        return std::max(0., std::min(r, t) - std::max(s, l));
    };
    std::vector<std::pair<double, double>> A, B;
    if (f > g) {
        A.push_back({0, g});
        A.push_back({f, 2 * pi});
    }
    else {
        A.push_back({f, g});
    }
    if (start + rem > 2 * pi) {
        B.push_back({start, 2 * pi});
        B.push_back({0, start + rem - 2 * pi});
    }
    else {
        B.push_back({start, start + rem});
    }
    for (auto [l, r] : A) {
        for (auto [s, t] : B) {
            ans += inter(l, r, s, t);
        }
    }

    debug("f, g", std::pair{f * 180 / pi, g * 180 / pi});
    debug("alpha, alpha+r",
          std::pair{start * 180 / pi, (start + rem) * 180 / pi});
    std::cout << ans << '\n';
}
} // namespace
