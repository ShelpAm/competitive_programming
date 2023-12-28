#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <string_view>
#include <vector>

// configs
using ::std::size_t;

namespace impl {
  template<typename value_t> using vec2 = std::vector<std::vector<value_t>>;
  template<typename T> concept is_pair = requires(T t) {
    t.first;
    t.second;
  };
} // namespace impl
template<size_t i, size_t j, typename value_t> using arr2 = std::array<std::array<value_t, j>, i>;
template<size_t i, size_t j> using arr2uz = arr2<i, j, size_t>;
template<size_t i, size_t j> using arr2ll = arr2<i, j, long long>;
template<typename value_t> class vec2 : public impl::vec2<value_t> {
public:
  vec2(size_t const i, size_t const j): impl::vec2<value_t>(i, std::vector<value_t>(j)) {}
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
auto&& operator<<(auto&& os, auto&& t)
{
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      os << ele << ' ';
    }
    os << '\n';
  }
  else if constexpr (impl::is_pair<decltype(t)>) {
    os << t.first << ": " << t.second << ", ";
  }
  else {
    os << t << ' ';
  }
  return os;
}
void debug([[maybe_unused]] std::string_view const& sv, [[maybe_unused]] auto&& t)
{
#ifdef DEBUG
  std::cout << sv << ": " << t << '\n';
#endif
}
auto my_pow(auto a, std::size_t n) -> decltype(a)
{
  if (n == 0) {
    return 1;
  }
  if (a == 0) {
    return 0;
  }
  decltype(a) extra = 1.0;
  while (n != 1) {
    if ((n & 1) == 1) {
      extra *= a;
      n -= 1;
    }
    else {
      a *= a;
      n /= 2;
    }
  }
  return (a * extra);
}
void solve_case()
{
  size_t n{};
  size_t m{};
  std::string s;
  std::cin >> n >> m >> s;
  s.insert(0, "0");

  constexpr size_t base1{131};
  std::vector<size_t> hash1(n + 1);

  for (size_t i{1}; i != n + 1; ++i) {
    hash1[i] = hash1[i - 1] * base1 + s[i];
  }

  auto hashed1{[&](size_t const l, size_t const r) {
    return hash1[r] - hash1[l - 1] * my_pow(base1, r - l + 1);
  }};

  constexpr size_t base2{667};
  std::vector<size_t> hash2(n + 1);

  for (size_t i{1}; i != n + 1; ++i) {
    hash2[i] = hash2[i - 1] * base2 + s[i];
  }

  auto hashed2{[&](size_t const l, size_t const r) {
    return hash2[r] - hash2[l - 1] * my_pow(base2, r - l + 1);
  }};

  for (size_t i{}; i != m; ++i) {
    size_t l1, r1, l2, r2;
    std::cin >> l1 >> r1 >> l2 >> r2;
    // --l1, --l2, --r1, --r2;
    // ++l1, ++l2, ++r1, ++r2;
    if (hashed1(l1, r1) == hashed1(l2, r2) && hashed2(l1, r1) == hashed2(l2, r2)) {
      std::cout << "GY\n";
    }
    else {
      std::cout << "LX\n";
    }
  }
}
int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // std::cout.tie(nullptr);

  size_t t{1};
  // std::cin >> t;
  for (size_t i{}; i != t; ++i) {
    solve_case();
  }
  return 0;
}
