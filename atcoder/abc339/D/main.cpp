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
[[maybe_unused]] constexpr auto endl{'\n'};
template<typename T> [[maybe_unused]] constexpr T mod{static_cast<T>(998244353ULL)};
template<typename T> [[maybe_unused]] constexpr T inf{numeric_limits<T>::max() >> 16};
namespace impl {
  template<typename value_type> using vec2_placeholder = std::vector<std::vector<value_type>>;
  template<typename value_type, size_t size> using arr1 = ::std::array<value_type, size>;
  template<size_t i, size_t j, typename value_type> using arr2
      = std::array<std::array<value_type, j>, i>;
  template<typename value_type> using vec1 = ::std::vector<value_type>;
  template<typename value_type> class vec2 : public vec2_placeholder<value_type> {
  public:
    constexpr vec2(size_t const i, size_t const j, value_type const& value = {})
        : vec2_placeholder<value_type>(i, std::vector<value_type>(j, value))
    {}
  };

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
using puz = pair<size_t, size_t>;
using pll = pair<long long, long long>;
template<size_t i, size_t j> using arr2uz = impl::arr2<i, j, size_t>;
template<size_t i, size_t j> using arr2ll = impl::arr2<i, j, long long>;
template<size_t i, size_t j> using arr2b = impl::arr2<i, j, bool>;
using vec1uz = impl::vec1<size_t>;
using vec1ll = impl::vec1<long long>;
using vec1b = impl::vec1<bool>;
using vec2uz = impl::vec2<size_t>;
using vec2ll = impl::vec2<long long>;
using vec2b = impl::vec2<bool>;
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
  else if constexpr (std::is_convertible_v<T, char const*>) {
    cout << static_cast<char const*>(t);
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
static inline auto solve_case()
{
  size_t n;
  cin >> n;
  impl::vec2<char> v(n, n);
  cin >> v;

  size_t a{inf<size_t>}, b{}, p{}, t{};
  for (size_t i{}; i != n; ++i) {
    for (size_t j{}; j != n; ++j) {
      if (v[i][j] == 'P') {
        if (a == inf<size_t>) {
          a = i, b = j;
        }
        else {
          p = i, t = j;
        }
      }
    }
  }
  struct quad {
    size_t a, b, c, d, _;
  };
  impl::arr1<pll, 4> dirs{pll{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

  auto move{[&](puz const& pos, pll const& dir) {
    auto const [x, y]{pos};
    auto const [dx, dy]{dir};
    auto const nx{x + dx}, ny{y + dy};
    if (nx >= n || ny >= n || v[nx][ny] == '#') {
      return pos;
    }
    return puz{x + dx, y + dy};
  }};

  impl::vec2<vec2uz> f(n, n, vec2uz(n, n, inf<size_t>));
  queue<quad> q;
  q.emplace(quad{a, b, p, t, 0});
  while (!q.empty()) {
    auto const [a, b, c, d, _]{q.front()};
    q.pop();

    if (check_min(f[a][b][c][d], _)) {
      for (auto const dir: dirs) {
        auto const [s, t]{move({a, b}, dir)};
        auto const [u, v]{move({c, d}, dir)};
        q.emplace(quad{s, t, u, v, _ + 1});
      }
    }
  }

  size_t min_steps{inf<size_t>};
  for (size_t i{}; i != n; ++i) {
    for (size_t j{}; j != n; ++j) {
      check_min(min_steps, f[i][j][i][j]);
    }
  }
  return min_steps == inf<size_t> ? -1LL : static_cast<long long>(min_steps);
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
