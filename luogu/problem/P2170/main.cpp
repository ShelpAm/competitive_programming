#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <cstddef>
#include <deque>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// configs
using ::std::array;
using ::std::cin;
using ::std::cout;
using ::std::size_t;
using ::std::string;
using ::std::string_view;
using ::std::ranges::max;
using ::std::ranges::min;
using ::std::ranges::sort;
using ::std::operator""sv;
using ::std::numeric_limits;
using ::std::pair;
using ::std::ranges::views::drop;
using ::std::ranges::views::reverse;
using ::std::ranges::views::take;
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
static inline bool check_max(auto&& value, auto&& other)
{
  if (value < other) {
    value = other;
    return true;
  }
  return false;
}
static inline bool check_min(auto&& value, auto&& other)
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
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      is >> ele;
    }
  }
#ifdef __cpp_concepts
  else if constexpr (impl::is_pair<decltype(t)>) {
    is >> t.first >> t.second;
  }
#endif
  else {
    is >> t;
  }
  return is;
}
static inline void print(auto const& t)
{
  if constexpr (impl::is_string<decltype(t)> || impl::is_string_view<decltype(t)>) {
    cout << t;
  }
  else if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      print(ele);
    }
    std::cout << endl;
  }
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
  dsu d(n);
  for (size_t i{}; i != k; ++i) {
    size_t a, b;
    cin >> a >> b;
    d.unite(a - 1, b - 1);
  }
  std::unordered_map<size_t, size_t> map;
  for (size_t i{}; i != n; ++i) {
    ++map[d.find(i)];
  }
  std::unordered_map<size_t, size_t> num_of;
  for (auto const& [_, p]: map) {
    ++num_of[p];
  }
  vec1<bool> dp(2 * m + 1);
  dp[0] = true;
  for (auto [p, t]: num_of) {
    vec1<size_t> list;
    size_t c{1};
    while (t > c) {
      list.emplace_back(c);
      t -= c;
      c *= 2;
    }
    list.emplace_back(t);
    for (auto const num: list) {
      for (size_t j{2 * m}; j >= p * num; --j) {
        dp[j] = dp[j] || dp[j - p * num];
      }
    }
  }
  for (size_t i{0}; i <= m; ++i) {
    if (dp[m - i]) {
      cout << m - i;
      return;
    }
    if (dp[m + i]) {
      cout << m + i;
      return;
    }
  }
  cout << "NOTHING?";
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
