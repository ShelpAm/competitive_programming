#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <string_view>
#include <vector>

using ::std::size_t;

// constexpr bool debug{false};

template<typename T> T read()
{
  T tmp;
  std::cin >> tmp;
  return tmp;
}
template<size_t i, size_t j, typename value_type> using arr2
    = std::array<std::array<value_type, j>, i>;
template<size_t i, size_t j> using arr2uz = arr2<i, j, size_t>;
template<size_t i, size_t j> using arr2ll = arr2<i, j, long long>;
template<typename value_type> using vec2_impl
    = std::vector<std::vector<value_type>>;
template<typename value_t> class vec2 : public vec2_impl<value_t> {
public:
  vec2(size_t const i, size_t const j)
      : vec2_impl<value_t>(i, std::vector<value_t>(j))
  {}
};
using vec2uz = vec2<size_t>;
using vec2ll = vec2<long long>;
template<typename T> concept is_pair = requires(T t) {
  t.first;
  t.second;
};
void print(auto&& t)
{
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      print(ele);
    }
    std::cout << '\n';
  }
  else if constexpr (is_pair<decltype(t)>) {
    std::cout << t.first << ": " << t.second << ", ";
  }
  else {
    std::cout << t << ' ';
  }
}
void debug(std::string_view const& sv, auto&& t)
{
  std::cout << sv << ": ";
  print(t);
}
auto&& operator>>(auto&& is, auto&& t)
{
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      is >> ele;
    }
  }
  else if constexpr (is_pair<decltype(t)>) {
    is >> t.first >> t.second;
  }
  else {
    is >> t;
  }
  return is;
}
std::array<size_t, 6> const idx1{2, 5, 8, 1, 4, 7};
std::array<size_t, 6> const idx2{1, 4, 7, 2, 5, 8};
bool search_for_deletion(std::array<size_t, 10>& arr, size_t const i,
                         size_t const r, size_t const s,
                         std::array<size_t, 6> const& idx)
{
  if (i == 6) {
    return false;
  }
  if (r == s % 3) {
    return true;
  }
  if (arr[idx[i]] > 0) {
    --arr[idx[i]];
    bool ok = search_for_deletion(arr, i, r, s + idx[i], idx);
    if (ok) {
      return true;
    }
    ++arr[idx[i]];
  }
  bool ok = search_for_deletion(arr, i + 1, r, s, idx);
  return ok;
}
void solve_case()
{
  size_t n{};
  std::cin >> n;
  std::vector<size_t> v(n);
  for (size_t& e: v) {
    std::cin >> e;
  }
  std::array<size_t, 10> num_digit{};
  for (auto const i: v) {
    ++num_digit[i];
  }
  size_t sum_digits{};
  for (size_t i{}; i != num_digit.size(); ++i) {
    sum_digits += i * num_digit[i];
  }

  size_t r{sum_digits % 3};
  if (search_for_deletion(num_digit, 0, r, 0, r == 2 ? idx1 : idx2)) {
    size_t s{};
    for (size_t i{}; i != num_digit.size(); ++i) {
      s += i * num_digit[i];
    }
    if (s == 0) {
      if (num_digit[0]) {
        std::cout << 0;
      }
      else {
        std::cout << -1;
      }
    }
    else {
      for (size_t i{9}; i != -1; --i) {
        for (size_t j{}; j != num_digit[i]; ++j) {
          std::cout << i;
        }
      }
    }
  }
  else {
    std::cout << -1;
  }
}
int main()
{
  // std::freopen("in", "r", stdin);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // std::cout.tie(nullptr);

  size_t n{1};
  std::cin >> n;
  for (size_t i{}; i != n; ++i) {
    solve_case();
    std::cout << '\n';
  }
  return 0;
}
