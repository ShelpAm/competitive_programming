#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstddef>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using ::std::abs;
using ::std::cin;
using ::std::cout;
using ::std::deque;
using ::std::greater;
using ::std::less;
using ::std::map;
using ::std::multimap;
using ::std::multiset;
using ::std::numeric_limits;
using ::std::pair;
using ::std::priority_queue;
using ::std::ptrdiff_t;
using ::std::queue;
using ::std::set;
using ::std::size_t;
using ::std::stack;
using ::std::string;
using ::std::string_view;
using ::std::unordered_map;
using ::std::unordered_set;
using ::std::operator""sv;

#ifdef __cpp_lib_ranges
#include <ranges>
using ::std::ranges::binary_search;
using ::std::ranges::count;
using ::std::ranges::find;
using ::std::ranges::lower_bound;
using ::std::ranges::max;
using ::std::ranges::min;
using ::std::ranges::sort;
using ::std::ranges::swap;
using ::std::ranges::upper_bound;
using ::std::ranges::views::drop;
using ::std::ranges::views::iota;
using ::std::ranges::views::reverse;
using ::std::ranges::views::split;
using ::std::ranges::views::take;
#else
// TODO: Defines my own sort, etc.
using ::std::swap;
#endif

using i64 = ::std::ptrdiff_t;
using u64 = ::std::size_t;
using vi = ::std::vector<i64>;
using vvi = ::std::vector<vi>;
using vvvi = ::std::vector<vvi>;
using vvvvi = ::std::vector<vvvi>;
using vu = ::std::vector<u64>;
using vvu = ::std::vector<vu>;
using vvvu = ::std::vector<vvu>;
using vvvvu = ::std::vector<vvvu>;
using vb = ::std::vector<bool>;
using vvb = ::std::vector<vb>;
using vc = std::vector<char>;
using vvc = std::vector<vc>;
using pii = ::std::pair<i64, i64>;
using puu = ::std::pair<u64, u64>;
using triplei = ::std::tuple<i64, i64, i64>;
using tripleu = ::std::tuple<u64, u64, u64>;

namespace {
template<typename T> [[maybe_unused]]
constexpr T mod{static_cast<T>(998244353)};
template<typename T> [[maybe_unused]] constexpr T inf{numeric_limits<T>::max() >> 2};
[[maybe_unused]] constexpr double eps{1e-6};

namespace impl {
template<typename value_type> using vec2_placeholder = std::vector<std::vector<value_type>>;
template<typename value_type, size_t size> using arr1 = ::std::array<value_type, size>;
template<size_t i, size_t j, typename value_type> using arr2 = std::array<std::array<value_type, j>, i>;
template<typename value_type> using vec1 = ::std::vector<value_type>;
template<typename value_type> class vec2 : public vec2_placeholder<value_type> {
  public:
    constexpr vec2(size_t const i, size_t const j, value_type const& value = {})
        : vec2_placeholder<value_type>(i, std::vector<value_type>(j, value))
    {}
};

// Concepts.
#ifdef __cpp_concepts
using ::std::remove_cvref_t;

template<typename T> concept pair = requires(T t) {
    t.first;
    t.second;
};

template<typename> struct is_tuple_t : std::false_type {};
template<typename... T> struct is_tuple_t<std::tuple<T...>> : std::true_type {};
template<typename... T> concept tuple = is_tuple_t<T...>::value;

template<typename T> concept c_str = std::same_as<char const*, remove_cvref_t<T>>;
template<typename T> concept string = std::same_as<string, remove_cvref_t<T>>;
template<typename T> concept string_view = std::same_as<string_view, remove_cvref_t<T>>;
template<typename T> concept string_like = string<T> || string_view<T> || c_str<T>;
#endif

/// @brief Turns off synchronization with stdio.
class io_accelerator {
  public:
    io_accelerator()
    {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
        // The following line needn't to be executed because the above line
        // actually had done this. std::cout.tie(nullptr);
    }
    io_accelerator(const io_accelerator&) = delete;
    io_accelerator(io_accelerator&&) = delete;
    io_accelerator& operator=(const io_accelerator&) = delete;
    io_accelerator& operator=(io_accelerator&&) = delete;
    ~io_accelerator()
    {
        std::ios::sync_with_stdio(true);
        std::cin.tie(&std::cout);
    }
};
} // namespace impl

#ifdef __cpp_concepts
auto& operator>>(auto& istream, auto&& t)
{
    using T = ::std::remove_cvref_t<decltype(t)>;
#ifdef __cpp_lib_ranges
    if constexpr (std::ranges::range<T>) {
        for (auto& ele: t) {
            istream >> ele;
        }
    }
#endif
    else if constexpr (impl::pair<T>) {
        istream >> t.first >> t.second;
    }
    else if constexpr (impl::tuple<T>) {
        static_assert(!impl::tuple<T>, "[operator>>] tuple: not implemented yet.");
    }
    else {
        istream >> t;
    }
    return istream;
}
/// @warning Do not put string literals in this function, because we hasn't
/// (can't) inplement checking-string-literals functions.
void print(auto const& t, u64 const depth = 0)
{
    using T = ::std::remove_cvref_t<decltype(t)>;
    if constexpr (impl::string_like<T>) {
        cout << t;
    }
    else if constexpr (::std::is_convertible_v<T, char const*>) {
        cout << static_cast<char const*>(t);
    }
#ifdef __cpp_lib_ranges
    else if constexpr (std::ranges::range<T>) {
        for (auto const& ele: t) {
            print(ele, depth + 1);
        }
        if (depth != 0) {
            cout << '\n';
        }
    }
#endif
    else if constexpr (impl::pair<T>) {
        std::cout << "{ " << t.first << ", " << t.second << " } ";
    }
    else if constexpr (impl::tuple<T>) {
        static_assert(!impl::tuple<T>, "[print] tuple: not implemented yet.\n");
    }
    else {
        std::cout << t << ' ';
    }

    if (depth == 0) {
        cout << '\n';
    }
}
void debug([[maybe_unused]] std::string_view s, [[maybe_unused]] auto const& t)
{
#ifdef DEBUG
    std::cout << "[debug] " << s << ": ";
    print(t);
    cout.flush();
#endif
}
// #define debug(t) impl::debug({#t}, t);
constexpr bool check_max(auto& value, auto const& other)
#else
template<typename T> constexpr bool check_max(T& value, T const& other)
#endif
{
    if (value < other) {
        value = other;
        return true;
    }
    return false;
}
#ifdef __cpp_concepts
constexpr bool check_min(auto& value, auto const& other)
#else
template<typename T> constexpr bool check_min(T& value, T const& other)
#endif
{
    if (value > other) {
        value = other;
        return true;
    }
    return false;
}
#ifdef __cpp_concepts
[[maybe_unused]] constexpr auto sum(auto const& coll) noexcept
{
    using value_type = ::std::remove_cvref_t<decltype(coll.front())>;
    return std::accumulate(coll.begin(), coll.end(), value_type{});
}
[[maybe_unused]] constexpr auto pow(auto a, auto b, u64 const p) noexcept
{
    u64 res{1};
    while (b != 0) {
        if ((b & 1) == 1) {
            res = res * a % p;
        }
        a = a * a % p;
        b >>= 1;
    }
    return res;
}
#endif
[[maybe_unused]] constexpr u64 gcd(u64 a, u64 b) noexcept
{
    while (b != 0) {
        auto t = b;
        b = a % b;
        a = t;
    }
    return a;
}
[[maybe_unused]] constexpr u64 lcm(u64 a, u64 b) noexcept
{
    return a * b / gcd(a, b);
}
struct sieve {
    sieve(u64 const upper_bound): min_factor(upper_bound + 1, 0)
    {
        for (u64 i{2}; i != min_factor.size(); ++i) {
            if (min_factor[i] == 0) {
                primes.push_back(i);
                min_factor[i] = i;
            }
            for (auto const p: primes) {
                if (i * p > upper_bound || p > min_factor[i]) {
                    break;
                }
                min_factor[i * p] = p;
            }
        }
    }

    [[nodiscard]] std::map<u64, u64> factorize(u64 x) const
    {
        std::map<u64, u64> res;
        assert(x <= (min_factor.size() - 1) * (min_factor.size() - 1));
        for (auto const p: primes) {
            if (p > x) {
                break;
            }
            while (x % p == 0) {
                x /= p;
                ++res[p];
            }
        }
        if (x >= min_factor.size()) {
            ++res[x];
        }
        return res;
    }

    vu primes;
    vu min_factor;
};
struct graph {
  public:
    graph(u64 max_num_of_vertices): adjacent(max_num_of_vertices, 0) {}
    void add_edge(u64 u, u64 v, u64 w) { adjacent[u].emplace_back(w, v); }
    [[nodiscard]] std::vector<puu> edges_of(u64 u) const { return adjacent[u]; }
    impl::vec2<puu> adjacent;
};
[[maybe_unused]] graph read_graph(u64 const num_of_vertices, u64 const num_of_edges, bool const bidirectional, bool const contains_w,
                                  bool const read_from_1)
{
    graph g(num_of_vertices);
    for (u64 i{}; i != num_of_edges; ++i) {
        u64 u, v, w;
        cin >> u >> v;
        if (contains_w) {
            cin >> w;
        }
        else {
            w = 1;
        }
        if (read_from_1) {
            --u, --v;
        }
        g.add_edge(u, v, w);
        if (bidirectional) {
            g.add_edge(v, u, w);
        }
    }
    return g;
}
struct dijkstra_result {
    vu distance;
    vu previous;
};
[[maybe_unused]] dijkstra_result dijkstra(graph const& graph, u64 const source)
{
    vu distance(graph.adjacent.size(), inf<u64>);
    vu previous(graph.adjacent.size());
    distance[source] = 0;

    priority_queue<puu, std::vector<puu>, greater<>> q;
    q.emplace(distance[source], source);

    while (!q.empty()) { // The main loop
        auto const [_, u]{q.top()}; // Extract the closest vertex. (Get and
                                    // remove the best vertex)
        q.pop();

        for (auto const& [w, v]: graph.edges_of(u)) {
            if (auto const alt{distance[u] + w}; alt < distance[v]) {
                distance[v] = alt;
                previous[v] = u;
                q.emplace(alt, v);
            }
        }
    }

    return {distance, previous};
}
[[maybe_unused]] vvi floyd(impl::vec2<pii> const& adjacent)
{
    auto const n{adjacent.size()};

    vvi f(adjacent.size(), vi(adjacent.size(), inf<i64>));
    // Initialize data
    for (u64 u{}; u != n; ++u) {
        f[u][u] = 0;
        for (auto const& [w, v]: adjacent[u]) {
            f[u][v] = w;
        }
    }

    for (u64 k{}; k != n; ++k) {
        // In k-th round (At the end of the round), f[i][j] denotes the minimum
        // distance between i, j, concerning first k vertices.
        for (u64 i{}; i != n; ++i) {
            for (u64 j{}; j != n; ++j) {
                check_min(f[i][j], f[i][k] + f[k][j]);
            }
        }
    }

    return f;
}

class disjoint_set {
  public:
    disjoint_set(u64 size): parent_(size), size_(size, 1) { std::iota(parent_.begin(), parent_.end(), 0); }
    // with path compression
    size_t find(u64 const x) { return parent_[x] == x ? x : parent_[x] = find(parent_[x]); }
    /// @return:
    /// false if there has been pair x,y in the set.
    /// true successfully united
    bool unite(u64 x, u64 y)
    {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        if (size_[x] < size_[y]) {
            swap(x, y);
        }
        parent_[y] = x;
        size_[x] += size_[y];
        return true;
    }
    bool united(size_t const x, size_t const y) { return find(x) == find(y); }
    [[nodiscard]] auto const& size() const { return size_; }
  private:
    std::vector<size_t> parent_;
    std::vector<size_t> size_;
};
using ds = disjoint_set;
constexpr auto lsb(i64 const i)
{
    return i & (-i);
}
// i mustn't be 0
[[maybe_unused]] constexpr auto msb(u64 const i)
{
    return sizeof(u64) * CHAR_BIT - 1 - __builtin_clzll(i | 1);
}
class fenwick_tree {
  public:
    fenwick_tree(u64 const size): tree_(size) {}
    // The input array should start from the index 1.
    fenwick_tree(vi coll): tree_{std::move(coll)}
    {
        for (size_t i{1}; i != tree_.size(); ++i) {
            auto parent_index{i + lsb(static_cast<i64>(i))};
            if (parent_index < tree_.size()) {
                tree_[parent_index] += tree_[i];
            }
        }
    }
    [[nodiscard]] i64 query(i64 index) const
    {
        i64 sum{};
        while (index > 0) {
            sum += tree_[index];
            index -= lsb(index);
        }
        return sum;
    }
    void update(u64 index, i64 const value)
    {
        while (index < tree_.size()) {
            tree_[index] += value;
            index += lsb(static_cast<i64>(index));
        }
    }
  private:
    vi tree_;
};
// template<typename info_type, typename tag_type> class segment_tree {
//   public:
//     segment_tree(u64 n);
//     // The input array should start from the index 0.
//     segment_tree(std::vector<i64> const& raw);
//
//     [[deprecated("unimplemented")]] void modify_range(u64 a, u64 b, u64 x)
//     {
//         modify_range_impl(1, 0, n_, a, b, x);
//     }
//     void apply_range(u64 a, u64 b, tag_type const& tag) { apply_range_impl(1, 0, n_, a, b, tag);
//     } info_type query_range(u64 a, u64 b) { return query_range_impl(1, 0, n_, a, b); }
//   private:
//     // pull info from subtree(s)
//     void pull(u64 p);
//
//     // push tag into subtree(s)
//     void push(u64 p, u64 l, u64 r);
//
//     // apply tag on node `p`
//     void apply(u64 p, tag_type const& tag);
//
//     void modify_range_impl(u64 p, u64 l, u64 r, u64 a, u64 b, i64 x);
//     void apply_range_impl(u64 p, u64 l, u64 r, u64 a, u64 b, tag_type const& tag);
//     info_type query_range_impl(u64 p, u64 l, u64 r, u64 a, u64 b);
//
//     [[deprecated]] void add_on_segment_impl(u64 a, u64 b, i64 d, u64 l, u64 r, u64 x)
//     {
//         if (a <= l && r <= b) {
//             info_[x].tag += d;
//             return;
//         }
//
//         push(l, r, x);
//         u64 const mid = (l + r) / 2;
//         if (a <= mid) {
//             add_on_segment_impl(a, b, d, l, mid, x * 2);
//         }
//         if (mid < b) {
//             add_on_segment_impl(a, b, d, mid + 1, r, x * 2 + 1);
//         }
//         pull(x);
//     }
//
//     u64 n_;
//     std::vector<info_type> info_;
//     std::vector<tag_type> tags_;
// };
// template<typename info_type, typename tag_type>
// segment_tree<info_type, tag_type>::segment_tree(u64 const n)
//     : n_(n), info_(4ULL << msb(n_), info_type{0, 0, 0, 0}), tags_(4ULL << msb(n_))
// {}
// template<typename info_type, typename tag_type>
// segment_tree<info_type, tag_type>::segment_tree(std::vector<i64> const& raw)
//     : segment_tree(raw.size())
// {
//     auto build = [this, &raw](auto build, u64 p, u64 l, u64 r) {
//         // if we don't change the structure of the tree, we won't save info of internal
//         // nodes, since it can be calculated at runtime.
//         if (r - l == 1) {
//             info_[p] = raw[l];
//             return;
//         }
//
//         u64 const m = (l + r) / 2;
//         build(build, p * 2, l, m);
//         build(build, p * 2 + 1, m, r);
//         pull(p);
//     };
//     build(build, 1, n_, 1);
// }
// template<typename info_type, typename tag_type> void segment_tree<info_type, tag_type>::pull(u64
// p)
// {
//     info_[p] = info_[p * 2] + info_[p * 2 + 1];
// }
// template<typename info_type, typename tag_type>
// void segment_tree<info_type, tag_type>::push(u64 p, u64 l, u64 r)
// {
//     if (r - l == 1) {
//         return;
//     }
//
//     apply(p * 2, tags_[p]);
//     apply(p * 2 + 1, tags_[p]);
//     tags_[p] = tag_type{};
// }
// template<typename info_type, typename tag_type>
// void segment_tree<info_type, tag_type>::apply(u64 p, tag_type const& tag)
// {
//     info_[p].apply(tag);
//     tags_[p].apply(tag);
// }
// template<typename info_type, typename tag_type>
// void segment_tree<info_type, tag_type>::modify_range_impl([[maybe_unused]] u64 p, u64 l, u64 r,
//                                                           u64 a, u64 b, [[maybe_unused]] i64 x)
// {
//     // ranges not intersecting
//     if (b <= l || r <= a) {
//         return;
//     }
// }
// template<typename info_type, typename tag_type>
// void segment_tree<info_type, tag_type>::apply_range_impl(u64 p, u64 l, u64 r, u64 a, u64 b,
//                                                          tag_type const& tag)
// {
//     // ranges not intersecting
//     if (b <= l || r <= a) {
//         return;
//     }
//
//     // range fully included in [a, b)
//     if (a <= l && r <= b) {
//         apply(p, tag);
//         return;
//     }
//
//     push(p, l, r);
//     u64 const m = (l + r) / 2;
//     apply_range_impl(p * 2, l, m, a, b, tag);
//     apply_range_impl(p * 2 + 1, m, r, a, b, tag);
//     pull(p);
// }
// template<typename info_type, typename tag_type>
// info_type segment_tree<info_type, tag_type>::query_range_impl(u64 p, u64 l, u64 r, u64 a, u64 b)
// {
//     // ranges not intersecting
//     if (b <= l || r <= a) {
//         return info_type{};
//     }
//
//     // range fully included in [a, b)
//     if (a <= l && r <= b) {
//         return info_[p];
//     }
//
//     push(l, r, p);
//     u64 const m = (l + r) / 2;
//     return query_range_impl(p * 2, l, m, a, b) + query_range_impl(p * 2 + 1, m, r, a, b);
// }
//
// struct tag {
//     void apply(tag const& tag) { add += tag.add; }
//     i64 add;
// };
// struct info {
//     info operator+(info const& rhs) const
//     {
//         return info{.min = ::min(this->min, rhs.min),
//                     .max = ::max(this->max, rhs.max),
//                     .sum = this->sum + rhs.sum,
//                     .act = this->act + rhs.act};
//     }
//     void apply(tag const& tag)
//     {
//         min += tag.add;
//         max += tag.add;
//         sum += act * tag.add;
//     }
//     i64 min = inf<i64>;
//     i64 max = -inf<i64>;
//     i64 sum = 0;
//     i64 act = 0;
// };
// using segtree = segment_tree<info, tag>;
// TODO: to be implemented
// class trie {
// public:
//   [[nodiscard]] bool find(string_view s) const
//   {
//     u64 idx{};
//     for (auto const c: s) {
//       if (next_[idx][c] == -1UZ) {
//         return false;
//       }
//       idx = next_[idx][c];
//       cout << "next: " << idx << '\n';
//     }
//     return true;
//   }
//   void emplace(string_view s)
//   {
//     u64 idx{};
//     for (auto const c: s) {
//       if (next_[idx][c] == -1UZ) {
//         next_.emplace_back(alphabet_size, -1);
//         next_[idx][c] = next_.size() - 1;
//       }
//       idx = next_[idx][c];
//     }
//   }
// private:
//   static constexpr u64 alphabet_size{26};
//   vvu next_{1, vu(alphabet_size, -1UZ)};
// };
#ifdef __cpp_concepts
void solve_all_cases(auto solve_case)
{
    u64 t{1};
    std::cin >> t;
    using return_type = decltype(solve_case());
    for (u64 i{}; i != t; ++i) {
        if constexpr (std::same_as<return_type, void>) {
            solve_case();
        }
        else if constexpr (std::same_as<return_type, bool>) {
            print(solve_case() ? "YES" : "NO");
        }
        else {
            print(solve_case());
        }
    }
}
#else
template<typename T> void solve_all_cases(T solve_case)
{
    u64 t{1};
    // std::cin >> t;
    for (u64 i{}; i != t; ++i) {
        solve_case();
    }
}
#endif
} // namespace

auto solve_case()
{
    u64 n;
    cin >> n;
    string s;
    cin >> s;

    string t(n + 1, '0');
    bool singles = s.size() % 2 == 1;
    u64 already = 0;
    u64 need = 0;
    for (u64 i = 0; i != n / 2; ++i) {
        if (s[i] == s[n - 1 - i]) {
            ++already;
        }
        else {
            ++need;
        }
    }
    for (u64 i = 0; i <= already; ++i) {
        t[need + i * 2] = '1';
        if (singles) {
            t[need + i * 2 + 1] = '1';
        }
    }
    debug("already", already);
    return t;
}

int main()
{
    impl::io_accelerator accelerator;
    solve_all_cases(solve_case);
    return 0;
}
