#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <map>
#include <ranges>
#include <string_view>
#include <vector>

using ::std::size_t;

// constexpr bool debug{false};

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
std::string const a{"Why did you just play the Spring Shadow"};
std::string const b{"Don't go, I'm willing to do anything"};
std::string const c{
    "You're such a person that your mind is full of thoughts about yourself"};
std::string const s{a + b + a + c + a};
constexpr size_t max_n{static_cast<size_t>(1e5 + 1)};
std::array<size_t, max_n> len{};
char search(size_t const n, size_t const k)
{
  if (n == 0) {
    return a[k];
  }
  if (n == 1) {
    return s[k];
  }
  if (k < len[n - 1]) {
    return search(n - 1, k);
  }
  if (k < len[n - 1] + b.size()) {
    return b[k - len[n - 1]];
  }
  if (k < 2 * len[n - 1] + b.size()) {
    return search(n - 1, k - (len[n - 1] + b.size()));
  }
  if (k < 2 * len[n - 1] + b.size() + c.size()) {
    return c[k - (2 * len[n - 1] + b.size())];
  }
  // k is of 5th segment.
  return search(n - 1, k - (2 * len[n - 1] + b.size() + c.size()));
}
void solve_case()
{
  size_t q{};
  std::cin >> q;

  len[0] = a.size();
  for (size_t i{1}; i != len.size(); ++i) {
    len[i] = len[i - 1] * 3 + b.size() + c.size();
  }

  std::string ans;
  for (size_t i{}; i != q; ++i) {
    size_t n{};
    size_t k{};
    std::cin >> n >> k;
    ans += search(std::ranges::min(n, 36UZ), k);
  }
  std::cout << ans;
}
int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // std::cout.tie(nullptr);

  size_t n{1};
  // std::cin >> n;
  for (size_t i{}; i != n; ++i) {
    solve_case();
  }
  return 0;
}
