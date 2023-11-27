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
bool is_prime(size_t const n)
{
  if (n < 2) {
    return false;
  }
  for (size_t i{2}; i * i <= n; ++i) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}
void solve_case()
{
  size_t n{};
  size_t m{};
  std::cin >> n >> m;
  std::vector<size_t> a(n);
  std::vector<size_t> b(m);
  std::cin >> a >> b;

  std::ranges::sort(a);
  std::ranges::sort(b);
  size_t i{};
  size_t j{};
  while (i != n && a[i] == 1) {
    ++i;
  }
  while (j != m && b[j] == 1) {
    ++j;
  }
  if ((n - i) - (m - j) != 1) {
    std::cout << "NO";
    return;
  }

  while (j != b.size()) {
    if (a[i] != b[j]) {
      if (is_prime(a[i])) {
        std::cout << "YES";
      }
      else {
        std::cout << "NO";
      }
      return;
    }
    ++i;
    ++j;
  }

  if (is_prime(a[i])) {
    std::cout << "YES";
  }
  else {
    std::cout << "NO";
  }
}

int main()
{
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);
  // std::cout.tie(nullptr);

  size_t n{1};
  std::cin >> n;
  for (size_t i{}; i != n; ++i) {
    solve_case();
    std::cout << '\n';
  }
  return 0;
}
