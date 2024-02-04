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
using ::std::ranges::views::iota;
using ::std::ranges::views::reverse;
using ::std::ranges::views::split;
using ::std::ranges::views::take;
#else
// TODO: Defines my own sort, etc.
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

  template<typename> struct is_tuple_t : std::false_type {};
  template<typename... T> struct is_tuple_t<std::tuple<T...>> : std::true_type {};

  template<typename... T> concept is_tuple = is_tuple_t<T...>::value;
  template<typename T> concept is_c_str = std::is_same_v<char const*, std::remove_cvref_t<T>>;
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
  using T = std::remove_cvref_t<decltype(t)>;
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
  else if constexpr (impl::is_tuple<T>) {
    std::cout
        << "[operator>>] TODO: This is a tuple whose output method hasn't been implemented.\n";
  }
#endif
  return is >> t;
}
static inline void print(auto const& t)
{
  using T = std::remove_cvref_t<decltype(t)>;
  if constexpr (impl::is_string<T> || impl::is_string_view<T> || impl::is_c_str<T>) {
    cout << t;
  }
#ifdef __cpp_lib_ranges
  else if constexpr (std::ranges::range<T>) {
    for (auto&& ele: t) {
      print(ele);
    }
    std::cout << endl;
  }
#endif
#ifdef __cpp_concepts
  else if constexpr (impl::is_pair<T>) {
    std::cout << t.first << ": " << t.second << ", ";
  }
  else if constexpr (impl::is_tuple<T>) {
    std::cout << "[print] TODO: This is a tuple whose output method hasn't been implemented.\n";
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
size_t m = 1e9 + 7;
static inline auto solve_case()
{
  size_t n, l;
  cin >> n >> l;
  if (n == 1) {
    return 0UZ;
  }
  size_t i{1};
  while ((i <<= 1) <= n) {
  }
  size_t a{l / 2};
  size_t b{l - a};
  return a * b % m * (i - 1) % m;
}
static inline void solve_all_cases(auto&& solve_case_f)
{
  size_t t{1};
  std::cin >> t;
  for (size_t i{}; i != t; ++i) {
    if constexpr (std::is_void_v<decltype(solve_case_f())>) {
      solve_case_f();
    }
    else {
      print(solve_case_f());
      cout << '\n';
    }
  }
}
int main()
{
  impl::io_accelerator accelerator;
  solve_all_cases(solve_case);
  return 0;
}
