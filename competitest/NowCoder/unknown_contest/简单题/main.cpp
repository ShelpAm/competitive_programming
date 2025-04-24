#pragma once

// Problem: 简单题
// Contest: unknown_contest
// Judge: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/106899/C
// Start: Sun 06 Apr 2025 05:42:27 PM CST
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
template <std::ranges::range Range> class Trie {
    struct Node {
        using Value_type = std::ranges::range_value_t<Range>;
        std::map<Value_type, std::size_t> edges;
        std::size_t terminal_count{};
        std::size_t num_children{}; // *this excluded if is_terminal
    };

  public:
    static constexpr std::size_t npos{-1UZ};

    Trie() : nodes_(1) {}

    void finish_init()
    {
        auto dfs = [&](auto dfs, int x) -> void {
            for (auto [k, c] : nodes_[x].edges) {
                dfs(dfs, c);
                nodes_[x].num_children += nodes_[c].num_children;
                if (nodes_[c].edges.empty()) {
                    nodes_[x].num_children += nodes_[c].terminal_count;
                }
            }
        };
        dfs(dfs, 0);
    }

    std::size_t insert(std::size_t root, Range const &range)
    {
        auto x = root;
        for (auto ele : range) {
            // ++nodes_[x].num_children; // Delay this operation after full init
            if (!nodes_[x].edges.contains(ele)) {
                nodes_[x].edges.insert({ele, nodes_.size()});
                nodes_.push_back({});
            }
            x = nodes_[x].edges[ele];
        }
        ++nodes_[x].terminal_count;
        return x;
    }

    [[nodiscard]] bool find(Range const &range) const
    {
        auto i = find_terminal(0, range);
        return i != npos && nodes_[i].terminal_count != 0;
    }

    void remove(Range const &range)
    {
        auto x = 0UZ;
        for (auto ele : range) {
            --nodes_[x].num_children;
            if (!nodes_[x].children.contains(ele)) {
                nodes_[x].children.insert({ele, nodes_.size()});
                nodes_.push_back({});
            }
            x = nodes_[x].children[ele];
        }
        --nodes_[x].terminal_count;
    }

    std::vector<Node> nodes_;

  private:
    // Returns npos if not found
    [[nodiscard]] std::size_t find_terminal(std::size_t root,
                                            Range const &range) const
    {
        auto x = root; // root
        for (auto ch : range) {
            if (!nodes_[x].children.contains(ch)) {
                return npos;
            }
            x = nodes_[x].children.at(ch);
        }
        return x;
    }
};
void solve_case()
{
    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(n);
    std::cin >> a;

    Trie<std::span<int>> t;
    for (auto it{a.begin()}; it != a.end(); ++it) {
        auto x = 0UZ;
        for (auto jt = it; jt != a.end(); ++jt) {
            x = t.insert(x, {jt, std::next(jt)});
        }
    }
    t.finish_init();

    k = n * (n + 1) / 2 - k + 1;

    auto x = 0;
    std::vector<int> path;
    int cnt = 0;
    while (k != 1) {
        debug("k", k);
        debug("path", path);
        for (auto [key, c] : t.nodes_[x].edges) {
            ++cnt;
            if (cnt == 100) {
                return;
            }
            auto &child = t.nodes_[c];
            debug("key", key);
            debug("child.num_children", child.num_children);
            if (k > child.num_children) {
                k -= child.num_children;
                debug("skipping", "");
            }
            else {
                debug("go deeper", "");
                path.push_back(key);
                x = c;
                break;
            }
        }
    }
    for (auto e : path) {
        std::cout << e << ' ';
    }
}
} // namespace
