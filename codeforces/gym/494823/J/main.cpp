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
using ::std::ranges::max;
using ::std::ranges::min;
using ::std::ranges::sort;
using ::std::operator""sv;
using ::std::numeric_limits;
using ::std::pair;
using ::std::ranges::swap;
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
struct pos {
  long long x, y, z;
};
static inline auto solve_case()
{
  size_t n;
  cin >> n;
  vec1<pos> a(n);
  for (auto&& [x, y, z]: a) {
    cin >> x >> y >> z;
  }

  // for asix-x
  arr1<vec1<double>, 3> axis{vec1<double>(n), vec1<double>(n), vec1<double>(n)};
  for (size_t i{}; i != n; ++i) {
    axis[0][i] = sqrt(a[i].y * a[i].y + a[i].z * a[i].z);
    axis[1][i] = sqrt(a[i].x * a[i].x + a[i].z * a[i].z);
    axis[2][i] = sqrt(a[i].y * a[i].y + a[i].x * a[i].x);
  }

  auto check{[&](size_t const main, double const r) {
    std::priority_queue<pair<double, double>, vec1<pair<double, double>>, std::greater<>> q;
    std::priority_queue<double, vec1<double>, std::greater<>> selected_r;
    for (size_t i{}; i != n; ++i) {
      long long x{};
      if (main == 0) {
        x = a[i].x;
      }
      else if (main == 1) {
        x = a[i].y;
      }
      else if (main == 2) {
        x = a[i].z;
      }
      auto y{axis[main][i]};
      auto d{r >= y ? sqrt(r * r - y * y) : -1};
      if (d != -1) {
        q.emplace(x - d, x + d);
      }
    }
    while (!q.empty()) {
      selected_r.emplace(q.top().second);
      while (!selected_r.empty() && selected_r.top() < q.top().first) {
        debug("selected_r.top()", selected_r.top());
        debug("q.top()", q.top().first);
        selected_r.pop();
      }
      if (selected_r.size() >= n / 2) {
        return true;
      }
      q.pop();
    }
    return false;
  }};

  double m{0x3f3f3f3f};
  for (size_t main{}; main != 3; ++main) {
    double l{}, r{0x3f3f3f3f};
    while (l + 1e-7 < r) {
      auto mid{(l + r) / 2};
      if (check(main, mid)) {
        r = mid;
      }
      else {
        l = mid;
      }
    }
    check_min(m, l);
  }
  cout << std::setprecision(6) << std::fixed << m;
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

