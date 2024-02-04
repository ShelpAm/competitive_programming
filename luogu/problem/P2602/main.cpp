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
size_t constexpr base{10};
size_t constexpr n{12};
static inline auto solve_case()
{
  arr1<size_t, n + 1> pow_base{1};
  for (size_t i{1}; i != pow_base.size(); ++i) {
    pow_base[i] = pow_base[i - 1] * base;
  }
  arr2uz<n + 1, base> f{};
  f[1].fill(1);
  for (size_t i{2}; i != f.size(); ++i) {
    for (size_t j{}; j != f[0].size(); ++j) {
      f[i][j] = f[i - 1][j] * base + pow_base[i - 1];
    }
  }

  auto count{[&](size_t x) {
    arr1<size_t, base> cnt{};
    vec1<size_t> digits{0};
    while (x != 0) {
      digits.emplace_back(x % base);
      x /= base;
    }
    for (size_t i{1}; i != digits.size(); ++i) {
      for (size_t j{}; j != base; ++j) {
        cnt[j] += digits[i] * f[i][j];
      }
    }
    return cnt;
  }};

  size_t a, b;
  cin >> a >> b;
  // vec1<size_t> cnt(10);
  // for (auto i: std::ranges::views::iota(a, b + 1)) {
  //   do {
  //     ++cnt[i % 10];
  //     i /= 10;
  //   }
  //   while (i != 0);
  // }
  // print(cnt);
  auto p{count(b)}, q{count(a - 1)};
  print(p);
  print(q);
  for (size_t i{}; i != p.size(); ++i) {
    cout << p[i] - q[i] << ' ';
  }
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
