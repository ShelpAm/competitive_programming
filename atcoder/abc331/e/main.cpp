#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <set>
#include <string_view>
#include <vector>

using ::std::size_t;

// constexpr bool debug{false};

template<size_t i, size_t j, typename value_type> using arr2
    = std::array<std::array<value_type, j>, i>;
template<size_t i, size_t j> using arr2uz = arr2<i, j, size_t>;
template<size_t i, size_t j> using arr2ll = arr2<i, j, long long>;
template<typename value_type> using vec2_impl = std::vector<std::vector<value_type>>;
template<typename value_t> class vec2 : public vec2_impl<value_t> {
public:
  vec2(size_t const i, size_t const j): vec2_impl<value_t>(i, std::vector<value_t>(j)) {}
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
struct dish_t {
  size_t id{};
  size_t price{};
  bool operator<(dish_t const& o) const { return price > o.price; }
};
void solve_case()
{
  size_t n{};
  size_t m{};
  size_t l{};
  std::cin >> n >> m >> l;
  std::vector<dish_t> a(n);
  std::vector<dish_t> b(m);
  for (size_t idx{}; auto&& e: a) {
    e.id = idx;
    std::cin >> e.price;
    ++idx;
  }
  for (size_t idx{}; auto&& e: b) {
    e.id = idx;
    std::cin >> e.price;
    ++idx;
  }

  std::ranges::sort(a, std::less<>());
  std::ranges::sort(b, std::less<>());

  std::vector<std::set<size_t>> cannot_compose(n);
  for (size_t i{}; i != l; ++i) {
    size_t c{};
    size_t d{};
    std::cin >> c >> d;
    cannot_compose[c - 1].emplace(d - 1);
  }

  for (size_t i{}; i != n;) {
    for (size_t j{}; j != m;) {
      if (!cannot_compose[a[i].id].contains(b[j].id)) {
        std::cout << a[i].price + b[j].price << '\n';
        std::cout << a[i].id << ' ' << b[j].id;
        return;
      }
      if (i == n - 1 || a[i].price - a[i + 1].price > b[j].price - b[j + 1].price) {
        ++j;
      }
      else {
        ++i;
      }
    }
  }
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
