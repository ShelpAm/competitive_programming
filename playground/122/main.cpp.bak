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
namespace {
using i64 = std::int_least64_t;
using i128 = __int128_t;
using u64 = std::uint_least64_t;
using u128 = __uint128_t;
namespace math {

constexpr double eps{1e-8};

template <typename T> class Matrix {
  public:
    // Matrix() : mat_() {}
    Matrix(std::size_t n, std::size_t m, T val) : n_(n), m_(m)
    {
        assert(n == m && "Matrix must be square to use scalar constructor");

        for (std::size_t i{}; i != n; ++i) {
            get(i, i) = val;
        }
    }
    Matrix(std::vector<std::vector<T>> mat)
        : mat_(mat), n_{mat.size()}, m_{mat[0].size()}
    {
    }

    std::vector<T> &operator[](std::size_t i)
    {
        return mat_[i];
    }

    std::vector<T> const &operator[](std::size_t i) const
    {
        return mat_[i];
    }

    [[nodiscard]] T &get(std::size_t i, std::size_t j)
    {
        return mat_.at(i).at(j);
    }

    [[nodiscard]] T get(std::size_t i, std::size_t j) const
    {
        return mat_.at(i).at(j);
    }

    [[nodiscard]] std::size_t n() const
    {
        return n_;
    }

    [[nodiscard]] std::size_t m() const
    {
        return m_;
    }

  private:
    std::vector<std::vector<T>> mat_;
    std::size_t n_;
    std::size_t m_;
};

template <typename T>
[[nodiscard]] Matrix<T> operator*(Matrix<T> const &lhs, Matrix<T> const &rhs)
{
    assert(lhs.m() == rhs.n());

    auto const n = lhs.n();
    auto const m = lhs.m();
    auto const p = rhs.m();

    Matrix<T> res{};
    for (std::size_t i{}; i != n; ++i) {
        for (std::size_t j{}; j != p; ++j) {
            for (std::size_t k{}; k != m; ++k) {
                res.get(i, j) += lhs.get(i, k) * rhs.get(k, j);
            }
        }
    }
    return res;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, Matrix<T> const &mat)
{
    for (std::size_t i{}; i != mat.n(); ++i) {
        for (std::size_t j{}; j != mat.m(); ++j) {
            os << mat.get(i, j) << ' ';
        }
        os << '\n';
    }
}

// template<>

enum class Solution_kind {
    infinite,
    only_one,
    DNE // Does not exist
};

template <typename Matrix> struct Gauss_elimination_result {
    Solution_kind solution_kind{};
    Matrix eliminated_matrix;
    std::vector<int> pivot_row;
};

template <typename Matrix>
Gauss_elimination_result<Matrix> gauss_elimination(Matrix a, int n, int m,
                                                   int p)
    requires requires(int i, int j) {
        a[i][j];
        std::abs(a[i][j]);
    }
{
    // The row that i-th column pivot resides in. -1 represents this column
    // doesn't contain a pivot.
    std::vector<int> pivot_row(m, -1);
    int row{};
    for (int j{}; j != m; ++j) {

        // Find the row with max a[`row`][j], and swap it to the top(`row`)
        int max_row{row};
        for (int i{row + 1}; i != n; ++i) {
            if (std::abs(a[i][j]) > std::abs(a[max_row][j])) {
                max_row = i;
            }
        }
        if (std::abs(a[max_row][j]) < eps) {
            continue;
        }
        pivot_row[j] = row;
        std::swap(a[row], a[max_row]);

        // 向下消去
        for (int i{row + 1}; i != n; ++i) {
            if (a[i][j]) {
                a[i] ^= a[row];
            }
        }
        ++row;
        if (row == n) {
            break;
        }
    }

    // 向上消去
    for (int j{m - 1}; j != -1; --j) {
        if (pivot_row[j] == -1) {
            continue;
        }

        for (int i{}; i != pivot_row[j]; ++i) {
            if (a[i][j]) {
                a[i] ^= a[pivot_row[j]];
            }
        }
    }

    // Identify DNE situations
    for (int j{m}; j != m + p; ++j) {
        for (int i{row}; i != n; ++i) {
            if (a[i][j] > eps) {
                // No solution
                return {.solution_kind = Solution_kind::DNE,
                        .eliminated_matrix = a,
                        .pivot_row = pivot_row};
            }
        }
    }

    auto const num_pivots = n - std::ranges::count(pivot_row, -1); // 主元个数
    if (num_pivots < m) {
        // Many solutions
        return {.solution_kind = Solution_kind::infinite,
                .eliminated_matrix = a,
                .pivot_row = pivot_row};
    }

    // Only one solution
    return {.solution_kind = Solution_kind::only_one,
            .eliminated_matrix = a,
            .pivot_row = pivot_row};
};

} // namespace math
void solve_case()
{
    using namespace ::shelpam;
    int n, m, p;
    std::cin >> n >> m >> p;
    std::vector<std::bitset<2000>> a(n);
    for (int i{}; i != n; ++i) {
        for (int j{}; j != m; ++j) {
            int b;
            std::cin >> b;
            a[i].set(j, b);
        }
    }
    for (int i{}; i != n; ++i) {
        for (int j{}; j != p; ++j) {
            int b;
            std::cin >> b;
            a[i].set(m + j, b);
        }
    }

    using namespace math;
    // auto [res, pivot_row] = gauss(a, n, m, p);
    auto [res, b, pivot_row] = gauss_elimination(a, n, m, p);
    a = b;
    if (res == Solution_kind::DNE) {
        std::cout << "No\n";
        return;
    }

    std::cout << "Yes\n";
    if (res == Solution_kind::only_one) {
        for (int i{}; i != m; ++i) {
            for (int j{}; j != p; ++j) {
                std::cout << a[i][m + j] << ' ';
            }
            std::cout << '\n';
        }
    }
    else {
        std::vector b(m, std::vector<int>(p));
        for (int i{}; i != p; ++i) {
            for (int j{}; j != m; ++j) {
                if (pivot_row[j] == -1) {
                    b[j][i] = 0;
                }
                else {
                    b[j][i] = a[pivot_row[j]][m + i];
                }
            }
        }
        for (int i{}; i != m; ++i) {
            for (int j{}; j != p; ++j) {
                std::cout << b[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }
}
} // namespace
