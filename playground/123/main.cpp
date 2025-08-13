#pragma once

// Problem: $(PROBLEM)
// Contest: $(CONTEST)
// Judge: $(JUDGE)
// URL: $(URL)
// Start: $(DATE)
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
    std::cin >> t;
    for (int i{}; i != t; ++i) {
#ifndef ONLINE_JUDGE
        std::cerr << "Test case " << i << '\n';
#endif
        solve_case();
    }
    return 0;
}
namespace shelpam::math {

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

    // 向量 * 标量
    friend auto operator*(Vector lhs, Value_type const &scalar)
    {
        return lhs *= scalar;
    }

    // 标量 * 向量
    friend auto operator*(Value_type const &scalar, Vector const &rhs)
    {
        Vector result = rhs;
        return result *= scalar;
    }

    // 向量 / 标量
    friend auto operator/(Vector lhs, Value_type const &scalar)
    {
        return lhs /= scalar;
    }

    friend std::istream &operator>>(std::istream &is, Vector &self)
    {
        for (auto &v : self.coordinate) {
            is >> v;
        }
        return is;
    }

    Vector &operator+=(Vector const &rhs)
    {
        for (std::size_t i{}; i != Dimension; ++i) {
            coordinate.at(i) += rhs.coordinate.at(i);
        }
        return *this;
    }

    Vector &operator-=(Vector const &rhs)
    {
        for (std::size_t i{}; i != Dimension; ++i) {
            coordinate.at(i) -= rhs.coordinate.at(i);
        }
        return *this;
    }

    // 数乘赋值运算符
    Vector &operator*=(Value_type const &scalar)
    {
        for (std::size_t i{}; i != Dimension; ++i) {
            coordinate.at(i) *= scalar;
        }
        return *this;
    }

    // 数除赋值运算符
    Vector &operator/=(Value_type const &scalar)
    {
        if (scalar == Value_type{}) {
            throw std::invalid_argument("Division by zero");
        }
        for (std::size_t i{}; i != Dimension; ++i) {
            coordinate.at(i) /= scalar;
        }
        return *this;
    }

    bool operator==(Vector const &rhs) const
    {
        return coordinate == rhs.coordinate;
    }

    [[nodiscard]] Value_type x() const
    {
        return coordinate.at(0);
    }

    [[nodiscard]] Value_type y() const
    {
        return coordinate.at(1);
    }

    [[nodiscard]] Value_type z() const
    {
        return coordinate.at(2);
    }

    [[nodiscard]] auto length() const
    {
        Value_type result{};
        for (auto e : coordinate) {
            result += e * e;
        }
        return std::sqrt(result);
    }

    std::array<Value_type, Dimension> coordinate{};
};

template <typename Value_type> using Vector2d = Vector<Value_type, 2>;

template <typename T> T cross(Vector2d<T> const &a, Vector2d<T> const &b)
{
    return (a.coordinate[0] * b.coordinate[1]) -
           (a.coordinate[1] * b.coordinate[0]);
}

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

// 计算凸包，返回凸包顶点索引的顺序
template <typename T>
std::vector<Vector2d<T>> convex_hull(std::vector<Vector2d<T>> points)
{
    if (points.size() <= 3) {
        return points;
    }

    // 1. 找到最低的点（Y最小，Y相同X最小）
    auto it = std::min_element(points.begin(), points.end(),
                               [](auto const &a, auto const &b) {
                                   return (a.coordinate[1] < b.coordinate[1]) ||
                                          (a.coordinate[1] == b.coordinate[1] &&
                                           a.coordinate[0] < b.coordinate[0]);
                               });
    std::swap(points[0], *it);
    Vector2d<T> base = points[0];

    // 2. 按极角排序（以 base 点为原点）
    std::sort(points.begin() + 1, points.end(),
              [&base](auto const &a, auto const &b) {
                  Vector2d<T> va = a - base;
                  Vector2d<T> vb = b - base;
                  auto c = cross(va, vb);
                  if (c == 0) { // 共线，离base近的排前面
                      auto da = (va.coordinate[0] * va.coordinate[0]) +
                                (va.coordinate[1] * va.coordinate[1]);
                      auto db = (vb.coordinate[0] * vb.coordinate[0]) +
                                (vb.coordinate[1] * vb.coordinate[1]);
                      return da < db;
                  }
                  return c > 0;
              });

    // 3. 使用栈构造凸包
    std::vector<Vector2d<T>> hull;
    hull.push_back(points[0]);
    hull.push_back(points[1]);

    for (size_t i = 2; i < points.size(); ++i) {
        while (hull.size() > 1) {
            Vector2d<T> v1 = hull.back() - hull[hull.size() - 2];
            Vector2d<T> v2 = points[i] - hull.back();
            if (cross(v1, v2) > 0) {
                break; // 左转，保持凸包
            }
            hull.pop_back(); // 右转，pop
        }
        hull.push_back(points[i]);
    }
    return hull;
}

} // namespace shelpam::math
namespace {
using i64 = std::int_least64_t;
using i128 = __int128_t;
using u64 = std::uint_least64_t;
using u128 = __uint128_t;
void solve_case()
{
    using namespace ::shelpam;
    using V2 = math::Vector2d<i64>;
    std::array<V2, 4> p;
    std::cin >> p;
    auto trans = [](V2 v) { return V2{v.x() + v.y(), v.x() - v.y()}; };
    for (auto &e : p) {
        e = trans(e);
    }
    auto d = (p[0] + p[1] - p[2] - p[3]) / 2;
    std::cout << std::abs(d.x()) + std::abs(d.y()) << '\n';
}
} // namespace
