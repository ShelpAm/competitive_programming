#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <cstddef>
#include <deque>
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
template<typename value_type> using vec1 = ::std::vector<value_type>;
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

[[maybe_unused]] char constexpr endl{'\n'};

namespace impl {
  template<typename value_type> using vec2 = std::vector<std::vector<value_type>>;
#ifdef __cpp_concepts
  template<typename T> concept is_pair = requires(T t) {
    t.first;
    t.second;
  };
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
auto&& operator>>(auto&& is, auto&& t)
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
void print(auto const& t)
{
  if constexpr (std::ranges::range<decltype(t)>) {
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
void debug(std::string_view const sv, auto&& t)
{
#ifdef DEBUG
  std::cout << sv << ": ";
  print(t);
  std::cout << endl;
#endif
}
size_t n;
void quick_sort(vec1<size_t> const& a, vec1<size_t>& idx, long long const l, long long const r)
{
  if (l >= r) {
    return;
  }
  auto i{l - 1}, j{r + 1};
  auto pivot{a[(l + r) / 2]};
  while (i < j) {
    while (a[idx[++i]] < pivot) {
    }
    while (a[idx[--j]] > pivot) {
    }
    if (i < j) {
      std::swap(idx[i], idx[j]);
    }
  }
  quick_sort(a, idx, l, j);
  if (j + 1 <= (n - 1) / 2) {
    quick_sort(a, idx, j + 1, r);
  }
}
auto solve_case()
{
  cin >> n;
  vec1<std::pair<size_t, size_t>> a(n);
  for (size_t idx{}; auto&& e: a) {
    cin >> e.first;
    a[idx].second = idx;
    ++idx;
  }
  // quick_sort(a, idx, 0, n - 1);
  size_t sum{};
  vec1<size_t> ans;
  std::nth_element(a.begin(), a.begin() + (n + 1) / 2, a.end());
  for (size_t i{}; i <= (n - 1) / 2; ++i) {
    ans.emplace_back(a[i].second);
    sum += a[i].first;
  }
  sort(ans.begin(), ans.end());
  cout << sum << endl;
  for (auto const i: ans) {
    cout << i + 1 << ' ';
  }
}
void solve_all_cases(auto&& solve_case_f)
{
  size_t t{1};
  // std::cin >> t;
  for (size_t i{}; i != t; ++i) {
    if constexpr (std::is_same_v<decltype(solve_case_f()), void>) {
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
