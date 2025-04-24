#pragma once

// Problem: T543701 DerrickLo's Game (UBC002B)
// Contest: unknown_contest
// Judge: Luogu
// URL: https://www.luogu.com.cn/problem/T543701?contestId=203994
// Start: Sun 13 Apr 2025 04:20:12 PM CST
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
using namespace shelpam;
namespace {
using i64 = std::int_least64_t;
using i128 = __int128_t;
using u64 = std::uint_least64_t;
using u128 = __uint128_t;
namespace shelpam {

class Segment_tree {
    struct Lazy_tag {
        auto operator+=(Lazy_tag const &rhs) -> Lazy_tag &
        {
            set = rhs.set;
            return *this;
        }

        std::int_fast64_t set{};
    };

    struct Node {
        int left{};
        int right{};
    };

    struct Info {
        auto operator+=(Info const &rhs) -> Info &
        {
            value += rhs.value;
            chmax(max, rhs.max);
            return *this;
        }

        void apply(Lazy_tag const &lazy_tag, int segment_length)
        {
            value += lazy_tag.set * segment_length;
            max += lazy_tag.set;
        }

        std::int_fast64_t value{};
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
        debug("l: ", _nodes[u].left);
        debug("r: ", _nodes[u].right);
        // If [l, r] nests node u, the segment node doesn't have to be divided
        // anymore. So we direct return the info of this node.
        if (l <= _nodes[u].left && _nodes[u].right <= r) {
            debug("info, max", _info[u].max);
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
        _info[u] = res;
        debug("info, max", res.max);
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

} // namespace shelpam
void solve_case()
{
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    std::cin >> a;
    std::vector<std::array<int, 3>> queries(q);
    std::cin >> queries;

    Segment_tree st(0, n - 1);
    for (int i{}; i != n; ++i) {
        st.apply(i, i, {.set = a[i]});
    }
    debug("maxi", st.query(0, 2).max);
    debug("sum 00", st.query(0, 0).value);
    debug("sum 01", st.query(0, 1).value);
    debug("sum 02", st.query(0, 2).value);

    // for (int i{}; i != n; ++i) {
    //     std::cerr << st.query(i, i).max << ' ';
    // }
    // std::cerr << '\n';

    // for (auto [o, p, q] : queries) {
    //     if (o == 1) {
    //         auto k = p - 1;
    //         auto x = q;
    //         st.apply(k, k, {.addition = x - a[k]});
    //         a[k] = x;
    //     }
    //     else {
    //         auto l = p - 1;
    //         auto r = q - 1;
    //         i64 max = st.rangeQuery(l, r).max;
    //         debug("l, r", std::pair{l, r});
    //         debug("max", max);
    //         auto ll = a[l] == max
    //                       ? binary_search([&](auto x) { return a[x] != max;
    //                       },
    //                                       r, l, false)
    //                       : l;
    //         auto rr = a[r] == max
    //                       ? binary_search([&](auto x) { return a[x] != max;
    //                       },
    //                                       l, r, false)
    //                       : r;
    //         debug("ll, rr", std::pair{ll, rr});
    //         if (ll > rr) { // Empty
    //             std::cout << 0 << '\n';
    //         }
    //         else {
    //             auto second = st.rangeQuery(ll, rr).max;
    //             std::cout
    //                 << std::min({max - second + (rr - ll + 1) * (rr - ll +
    //                 1),
    //                              (rr - ll + 2) * (rr - ll + 2),
    //                              ((r - l + 1) * max) - st.rangeQuery(l,
    //                              r).sum})
    //                 << '\n';
    //         }
    //     }
    // }
}
} // namespace
