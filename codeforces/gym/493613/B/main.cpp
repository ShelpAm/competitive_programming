#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <iostream>
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
using ::std::size_t;

namespace impl {
  template<typename value_t> using vec2 = std::vector<std::vector<value_t>>;
  template<typename T> concept is_pair = requires(T t) {
    t.first;
    t.second;
  };
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
template<size_t i, size_t j, typename value_t> using arr2 = std::array<std::array<value_t, j>, i>;
template<size_t i, size_t j> using arr2uz = arr2<i, j, size_t>;
template<size_t i, size_t j> using arr2ll = arr2<i, j, long long>;
template<typename value_t> class vec2 : public impl::vec2<value_t> {
public:
  vec2(size_t const i, size_t const j, value_t const& value = {})
      : impl::vec2<value_t>(i, std::vector<value_t>(j, value))
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
  else if constexpr (impl::is_pair<decltype(t)>) {
    is >> t.first >> t.second;
  }
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
    std::cout << '\n';
  }
  else if constexpr (impl::is_pair<decltype(t)>) {
    std::cout << t.first << ": " << t.second << ',';
  }
  else {
    std::cout << t << ' ';
  }
}
void debug([[maybe_unused]] std::string_view const& sv, [[maybe_unused]] auto&& t)
{
#ifdef DEBUG
  std::cout << sv << ": ";
  print(t);
  std::cout << '\n';
#endif
}
auto solve_case()
{
  size_t n;
  std::cin >> n;
  long long integer{};
  long long floating{};
  while (n-- != 0) {
    long long i;
    std::cin >> i;
    if (integer % 2 != 0) {
      floating = integer % 2;
    }
    integer = integer / 2 + i;
    if (integer == 0) {
      if (floating == 0) {
        std::cout << '0';
      }
      else if (floating > 0) {
        std::cout << '+';
      }
      else {
        std::cout << '-';
      }
    }
    else if (integer > 0) {
      std::cout << '+';
    }
    else {
      std::cout << '-';
    }
    // debug("i", i);
    // debug("interget", integer);
    // debug("floating", floating);
  }
  // WHY this can't be true.
  // std::vector<int_fast16_t> bits(n + 32);
  // std::priority_queue<size_t> bit_pos;
  // for (size_t i{}; i != n; ++i) {
  //   size_t j{i};
  //   while (a[i] != 0) {
  //     bits[j] += a[i] % 2;
  //     bits[j + 1] += bits[j] / 2;
  //     bits[j] %= 2;
  //     if (bits[j] != 0) {
  //       bit_pos.emplace(j);
  //     }
  //     a[i] /= 2;
  //     ++j;
  //   }
  //   while (!bit_pos.empty() && bits[bit_pos.top()] == 0) {
  //     bit_pos.pop();
  //   }
  //   int_fast16_t sign{};
  //   if (!bit_pos.empty()) {
  //     sign = bits[bit_pos.top()];
  //   }
  //   std::cout << (sign > 0 ? '+' : sign < 0 ? '-' : '0');
  //   print(bits);
  // }
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
