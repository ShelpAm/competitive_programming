#pragma once

// Problem: D. Gifts Order
// Contest: Hello 2025
// Judge: Codeforces
// URL: https://codeforces.com/problemset/problem/2057/D
// Start: Fri 14 Feb 2025 05:30:49 PM CST
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
class Segment_tree {
    struct Lazy_tag {
        auto operator+=(Lazy_tag const &rhs) -> Lazy_tag &
        {
            addition = rhs.addition;
            return *this;
        }

        std::int_fast64_t addition{}; // set
    };

    struct Node {
        int left{};
        int right{};
    };

    struct Info {
        void apply(Lazy_tag const &rhs, int segment_length)
        {
            chmin(min, rhs.addition);
            chmax(max, rhs.addition);
        }

        std::int_least64_t ans{}; // should update
        std::int_fast64_t min{inf<i64>};
        std::int_fast64_t max{};
    };

  public:
    explicit Segment_tree(int l, int r)
        : _nodes(4 * (r - l + 1) + 1), _info(4 * (r - l + 1) + 1),
          _lazy_tags(4 * (r - l + 1) + 1)
    {
        build_tree(l, r, 1);
    }

    void apply(int l, int r, Lazy_tag const &tag)
    {
        apply_impl(l, r, 1, tag);
    }

    auto query(int l, int r) -> Info
    {
        return query_impl(l, r, 1);
    }

  private:
    // Sets up segments that nodes manage.
    void build_tree(int l, int r, int u)
    {
        _nodes[u].left = l;
        _nodes[u].right = r;

        if (l != r) {
            auto const m{(l + r) / 2};
            build_tree(l, m, u * 2);
            build_tree(m + 1, r, u * 2 + 1);
        }
    }

    void do_lazy_propagation(std::size_t u)
    {
        if (!is_leaf(u)) {
            _lazy_tags[u * 2] += _lazy_tags[u];
            _lazy_tags[u * 2 + 1] += _lazy_tags[u];
            _info[u * 2].apply(_lazy_tags[u],
                               _nodes[u * 2].right - _nodes[u * 2].left + 1);
            _info[u * 2 + 1].apply(_lazy_tags[u], _nodes[u * 2 + 1].right -
                                                      _nodes[u * 2 + 1].left +
                                                      1);
        }

        _lazy_tags[u] = {};
    }

    void apply_impl(int l, int r, std::size_t u, Lazy_tag const &tag)
    {
        _info[u].apply(tag, r - l + 1);

        if (l <= _nodes[u].left && _nodes[u].right <= r) {
            _lazy_tags[u] += tag;
            return;
        }

        if (_nodes[u * 2].right >= l) {
            apply_impl(l, std::min(r, _nodes[u * 2].right), u * 2, tag);
        }
        if (_nodes[u * 2 + 1].left <= r) {
            apply_impl(std::max(_nodes[u * 2 + 1].left, l), r, u * 2 + 1, tag);
        }
    }

    // We assume that [l, r] contains [_nodes[u].left_end, _nodes[u].right_end].
    [[nodiscard]] auto query_impl(int l, int r, std::size_t u) -> Info
    {
        // If [l, r] nests node u, the segment node doesn't have to be divided
        // anymore. So we direct return the info of this node.
        if (l <= _nodes[u].left && _nodes[u].right <= r) {
            return _info[u];
        }

        do_lazy_propagation(u);

        Info res;
        if (_nodes[u * 2].right >= l) {
            res += query_impl(l, r, u * 2);
        }
        if (_nodes[u * 2 + 1].left <= r) {
            res += query_impl(l, r, u * 2 + 1);
        }
        return res;
    }

    [[nodiscard]] auto is_leaf(std::size_t u) const -> bool
    {
        return _nodes[u].left == _nodes[u].right;
    }

    std::vector<Node> _nodes;
    std::vector<Info> _info;
    std::vector<Lazy_tag> _lazy_tags;
};
void solve_case()
{
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    std::cin >> a;

    Segment_tree seg(0, n - 1);
    for (int i{}; i != n; ++i) {
        seg.apply(i, i, {.addition{a[i]}});
    }

    for (int i{}; i != q; ++i) {
        int p, x;
        std::cin >> p >> x;
        --p;
    }
}
} // namespace
