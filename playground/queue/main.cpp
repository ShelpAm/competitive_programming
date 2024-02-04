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
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#ifdef __cpp_concepts
#include <ranges>
#endif

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
// using ::std::queue;
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
using puz = pair<size_t, size_t>;
using pll = pair<long long, long long>;

[[maybe_unused]] constexpr auto endl{'\n'};
template<typename T> [[maybe_unused]] constexpr T mod{static_cast<T>(998244353UZ)};
template<typename T> [[maybe_unused]] constexpr T big{numeric_limits<T>::max() / 2};

namespace impl {
  template<typename value_type> using vec2 = std::vector<std::vector<value_type>>;
#ifdef __cpp_concepts
  template<typename T> concept pair = requires(T t) {
    t.first;
    t.second;
  };

  template<typename> struct is_tuple_t : std::false_type {};
  template<typename... T> struct is_tuple_t<std::tuple<T...>> : std::true_type {};

  template<typename... T> concept tuple = is_tuple_t<T...>::value;
  template<typename T> concept c_str = std::same_as<char const*, std::remove_cvref_t<T>>;
  template<typename T> concept string = std::same_as<string, std::remove_cvref_t<T>>;
  template<typename T> concept string_view = std::same_as<string_view, std::remove_cvref_t<T>>;
  template<typename T> concept string_like = string<T> || string_view<T> || c_str<T>;
#endif
  class io_accelerator {
  public:
    io_accelerator()
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
    ~io_accelerator()
    {
      std::ios::sync_with_stdio(true);
      std::cin.tie(&std::cout);
    }
  };
} // namespace impl
[[maybe_unused]] static inline constexpr bool check_max(auto&& value, auto&& other)
{
  if (value < other) {
    value = other;
    return true;
  }
  return false;
}
[[maybe_unused]] static inline constexpr bool check_min(auto&& value, auto&& other)
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
  constexpr vec2(size_t const i, size_t const j, value_type const& value = {})
      : impl::vec2<value_type>(i, std::vector<value_type>(j, value))
  {}
};
using vec2uz = vec2<size_t>;
using vec2ll = vec2<long long>;
static inline constexpr auto&& operator>>(auto&& is, auto&& t)
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
  if constexpr (impl::pair<decltype(t)>) {
    return is >> t.first >> t.second;
  }
  else if constexpr (impl::tuple<T>) {
    std::cout
        << "[operator>>] TODO: This is a tuple whose output method hasn't been implemented.\n";
  }
#endif
  return is >> t;
}
static inline constexpr void print(auto const& t)
{
  using T = std::remove_cvref_t<decltype(t)>;
  if constexpr (impl::string_like<T>) {
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
  else if constexpr (impl::pair<T>) {
    std::cout << t.first << ": " << t.second << ", ";
  }
  else if constexpr (impl::tuple<T>) {
    std::cout << "[print] TODO: This is a tuple whose output method hasn't been implemented.\n";
  }
#endif
  else {
    std::cout << t << ' ';
  }
}
static inline constexpr void debug([[maybe_unused]] std::string_view s, [[maybe_unused]] auto&& t)
{
#ifdef DEBUG
  std::cout << "[debug] " << s << ": ";
  print(t);
  std::cout << endl;
#endif
}
class queue {
public:
  void push(size_t const element)
  {
    data_[rear_] = element;
    increase(rear_);
  }
  size_t pop()
  {
    auto tmp{data_[head_]};
    increase(head_);
    return tmp;
  }
  [[nodiscard]] size_t front() const { return data_[head_]; }
  [[nodiscard]] size_t size() const
  {
    return rear_ > head_ ? rear_ - head_ : rear_ + data_.size() - head_;
  }
private:
  void increase(size_t& i)
  {
    ++i;
    if (i == data_.size()) {
      rear_ = 0;
    }
  }

  arr1<size_t, 100> data_{};
  size_t head_{};
  size_t rear_{};
};
static inline auto solve_case()
{
  queue q;
}
static inline constexpr void solve_all_cases(auto&& solve_case_f)
{
  size_t t{1};
  // std::cin >> t;
  for (size_t i{}; i != t; ++i) {
    if constexpr (std::is_void_v<decltype(solve_case_f())>) {
      solve_case_f();
    }
    else {
      print(solve_case_f());
      cout << endl;
    }
  }
}
int main()
{
  impl::io_accelerator accelerator;
  solve_all_cases(solve_case);
  return 0;
}
