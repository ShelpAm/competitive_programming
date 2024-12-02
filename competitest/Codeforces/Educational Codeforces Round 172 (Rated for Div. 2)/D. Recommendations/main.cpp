#pragma once

/*Problem: D. Recommendations*/
/*Contest: Educational Codeforces Round 172 (Rated for Div. 2)*/
/*Judge: Codeforces*/
/*URL: https://codeforces.com/contest/2042/problem/D*/
/*Start: Mon 02 Dec 2024 11:52:50 PM CST*/
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
    std::cin >> t;
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
class Segment_tree {
    struct Lazy_tag {
        auto operator+=(Lazy_tag const &rhs) -> Lazy_tag &
        {
            chmax(max_l, rhs.max_l);
            chmin(min_r, rhs.min_r);
            return *this;
        }

        i64 max_l{-inf<i64>};
        i64 min_r{inf<i64>};
    };

    struct Node {
        int left{};
        int right{};
    };

    struct Info {
        auto operator+=(Info const &rhs) -> Info &
        {
            chmax(max_l, rhs.max_l);
            chmin(min_r, rhs.min_r);
            return *this;
        }

        void apply(Lazy_tag const &lazy_tag, int segment_length)
        {
            chmax(max_l, lazy_tag.max_l);
            chmin(min_r, lazy_tag.min_r);
        }

        i64 max_l{-inf<i64>};
        i64 min_r{inf<i64>};
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
    int n;
    std::cin >> n;
    std::vector<std::array<i64, 3>> a(n);
    std::set<int> set;
    std::map<std::pair<int, int>, int> cnt;
    for (int idx{}; auto &[x, y, z] : a) {
        std::cin >> x >> y;
        z = idx++;
        set.insert(x);
        set.insert(y);
        ++cnt[{x, y}];
    }

    std::ranges::sort(a, [](auto const &l, auto const &r) {
        return std::tuple{l[0], -l[1]} < std::tuple{r[0], -r[1]};
    });

    std::unordered_map<int, int> mapping;
    for (int idx{1}; auto const e : set) {
        mapping[e] = idx++;
    }

    debug("mapping", mapping);

    Segment_tree seg(1, 2 * n);

    std::vector<i64> ans(n);
    for (auto const &[l, r, i] : a) {
        auto [p, q]{seg.query(mapping[r], mapping[*set.rbegin()])};
        seg.apply(mapping[r], mapping[r], {.max_l = l, .min_r = r});
        ans[i] = (q - p) - (r - l);
        if (ans[i] > inf<i64>) {
            ans[i] = 0;
        }
        if (cnt[{l, r}] > 1) {
            ans[i] = 0;
        }
        // ans[i] = std::max(0L, (q - p) - (r - l));
    }

    for (auto const e : ans) {
        std::cout << e << '\n';
    }
}
} // namespace
