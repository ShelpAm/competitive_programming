#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <deque>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#ifdef __cpp_concepts
#include <ranges>
#endif
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// configs
using ::std::cin;
using ::std::cout;
using ::std::size_t;
using ::std::string;
using ::std::string_view;
using ::std::operator""sv;
using ::std::greater;
using ::std::less;
using ::std::map;
using ::std::numeric_limits;
using ::std::pair;
using ::std::priority_queue;
using ::std::queue;
using ::std::set;
using ::std::stack;
using ::std::unordered_map;
using ::std::unordered_set;
#ifdef __cpp_lib_ranges
using ::std::ranges::max;
using ::std::ranges::min;
using ::std::ranges::sort;
using ::std::ranges::swap;
using ::std::ranges::views::drop;
using ::std::ranges::views::reverse;
using ::std::ranges::views::take;
#endif
template<typename value_type, size_t size> using arr1 = ::std::array<value_type, size>;
template<typename value_type> using vec1 = ::std::vector<value_type>;
using pii = pair<size_t, size_t>;

[[maybe_unused]] char constexpr endl{'\n'};
[[maybe_unused]] size_t constexpr mod{998244353};
[[maybe_unused]] size_t constexpr big{0x3f3f3f3f};

namespace impl {
  template<typename value_type> using vec2 = std::vector<std::vector<value_type>>;
#ifdef __cpp_concepts
  template<typename T> concept is_pair = requires(T t) {
    t.first;
    t.second;
  };
  template<typename T> concept is_string = std::is_same_v<string, std::remove_cvref_t<T>>;
  template<typename T> concept is_string_view = std::is_same_v<string_view, std::remove_cvref_t<T>>;
#endif
  class io_accelerator {
  public:
    inline io_accelerator()
    {
      std::ios::sync_with_stdio(false);
      std::cin.tie(nullptr);
      // The following line needn't to be executed because the above line actually had done this.
      // std::cout.tie(nullptr);
    }
    io_accelerator(const io_accelerator&) = delete;
    io_accelerator(io_accelerator&&) = delete;
    io_accelerator& operator=(const io_accelerator&) = delete;
    io_accelerator& operator=(io_accelerator&&) = delete;
    inline ~io_accelerator()
    {
      std::ios::sync_with_stdio(true);
      std::cin.tie(&std::cout);
    }
  };
} // namespace impl
[[maybe_unused]] static inline bool check_max(auto&& value, auto&& other)
{
  if (value < other) {
    value = other;
    return true;
  }
  return false;
}
[[maybe_unused]] static inline bool check_min(auto&& value, auto&& other)
{
  if (value > other) {
    value = other;
    return true;
  }
  return false;
}
template<size_t i, size_t j, typename value_type> using arr2
    = std::array<std::array<value_type, j>, i>;
template<size_t i, size_t j> using arr2uz = arr2<i, j, size_t>;
template<size_t i, size_t j> using arr2ll = arr2<i, j, long long>;
template<typename value_type> class vec2 : public impl::vec2<value_type> {
public:
  vec2(size_t const i, size_t const j, value_type const& value = {})
      : impl::vec2<value_type>(i, std::vector<value_type>(j, value))
  {}
};
using vec2uz = vec2<size_t>;
using vec2ll = vec2<long long>;
static inline auto&& operator>>(auto&& is, auto&& t)
{
#ifdef __cpp_lib_ranges
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      is >> ele;
    }
    return is;
  }
#endif
#ifdef __cpp_concepts
  if constexpr (impl::is_pair<decltype(t)>) {
    return is >> t.first >> t.second;
  }
#endif
  return is >> t;
}
static inline void print(auto const& t)
{
  if constexpr (impl::is_string<decltype(t)> || impl::is_string_view<decltype(t)>) {
    cout << t;
  }
#ifdef __cpp_lib_ranges
  else if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      print(ele);
    }
    std::cout << endl;
  }
#endif
#ifdef __cpp_concepts
  else if constexpr (impl::is_pair<decltype(t)>) {
    std::cout << t.first << ": " << t.second << ", ";
  }
#endif
  else {
    std::cout << t << ' ';
  }
}
static inline void debug([[maybe_unused]] std::string_view const sv, [[maybe_unused]] auto&& t)
{
#ifdef DEBUG
  std::cout << sv << ": ";
  print(t);
  std::cout << endl;
#endif
}
struct dsu {
  dsu(size_t size_): pa(size_), size(size_, 1) { std::iota(pa.begin(), pa.end(), 0); }
  size_t find(size_t const x) { return pa[x] == x ? x : pa[x] = find(pa[x]); }
  void unite(size_t x, size_t y)
  {
    x = find(x);
    y = find(y);
    if (x == y) {
      return;
    }
    if (size[x] < size[y]) {
      std::ranges::swap(x, y);
    }
    pa[y] = x;
    size[x] += size[y];
  }
  bool united(size_t const x, size_t const y) { return find(x) == find(y); }
  std::vector<size_t> pa;
  std::vector<size_t> size;
};
static inline auto solve_case()
{
  size_t n, m, k;
  cin >> n >> m >> k;
  vec2<pii> g(n, 0);
  dsu d(n);
  for (size_t i{}; i != m; ++i) {
    size_t x, y, l;
    cin >> x >> y >> l;
    --x;
    --y;
    g[x].emplace_back(l, y);
    g[y].emplace_back(l, x);
    d.unite(x, y);
  }

  vec1<size_t> roots;
  for (size_t i{}; i != n; ++i) {
    if (d.find(i) == i) {
      roots.emplace_back(i);
    }
  }
  if (roots.size() > k) {
    cout << "No Answer";
  }

  vec1<size_t> len;
  for (auto root: roots) {
    priority_queue<pii, vec1<pii>, greater<>> q;
    q.emplace(0, root);
    unordered_set<size_t> p;
    while (!q.empty()) {
      auto [d, curr]{q.top()};
      q.pop();
      if (!p.contains(curr)) {
        p.emplace(curr);
        len.emplace_back(d);
        for (auto const next: g[curr]) {
          q.emplace(next);
        }
      }
    }
  }
  sort(len);
  cout << std::accumulate(len.begin(), len.begin() + n - k + roots.size(), 0UZ);
}
static inline void solve_all_cases(auto&& solve_case_f)
{
  size_t t{1};
  // std::cin >> t;
  for (size_t i{}; i != t; ++i) {
    if constexpr (std::is_void_v<decltype(solve_case_f())>) {
      solve_case_f();
    }
    else {
      print(solve_case_f());
    }
  }
}
int main()
{
  impl::io_accelerator accelerator;
  solve_all_cases(solve_case);
  return 0;
}
