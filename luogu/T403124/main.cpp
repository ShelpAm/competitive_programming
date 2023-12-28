#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <ranges>
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
struct pos_t {
  pos_t(long long const x, long long const y): x{x}, y{y} {}
  pos_t(size_t const i): layer{static_cast<size_t>(std::ceil(std::sqrt(i)) / 2 + 1)}
  {
    if (i == 1) {
      x = y = 0;
      return;
    }
    std::array<pos_t, 4> dirs{pos_t{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    size_t t{};
    // n-th layer contains range from square of 2*n-3 plus 1 to square of
    // 2*n-1.
    // Every edge is of (n-1)*2 length

    size_t len{2 * layer - 2};
    size_t r{static_cast<size_t>(i - std::pow(2 * layer - 3, 2))};
    while (r != 0) {
      size_t distance{std::ranges::min(r, len)};
      *this += dirs[t % 4] * distance;
      r -= distance;
      ++t;
      // std::cout << "Remaining " << r << " distance" << '\n';
    }
    x -= layer - 1;
    y -= layer - 1;
  }
  bool operator==(pos_t const& other) const { return x == other.x && y == other.y; }
  pos_t& operator+=(pos_t const& other)
  {
    x += other.x;
    y += other.y;
    return *this;
  }
  pos_t operator*(long long const scale) const { return pos_t{x * scale, y * scale}; }
  long long x{};
  long long y{};
  size_t layer{};
};
void solve_case()
{
  size_t n{};
  size_t m{};
  size_t k{};
  std::cin >> n >> m >> k;
  pos_t starting_point{n};
  pos_t ending_point{m};
  pos_t bad_starting_point{k};
  // std::cout << starting_point.x << ' ' << starting_point.y << '\n'
  //           << ending_point.x << ' ' << ending_point.y << '\n'
  //           << bad_starting_point.x << ' ' << bad_starting_point.y << '\n';
  auto hunter_distance{std::ranges::max(std::abs(bad_starting_point.x - ending_point.x),
                                        std::abs(bad_starting_point.y - ending_point.y))};
  auto game_distance{std::ranges::max(std::abs(starting_point.x - ending_point.x),
                                      std::abs(starting_point.y - ending_point.y))
                         * 2
                     + starting_point.layer - ending_point.layer};
  // std::cout << hunter_distance << ' ' << game_distance << '\n';
  std::cout << (game_distance < hunter_distance ? "delightful\n" : "kuyashi\n");
}
int main()
{
  std::freopen("/home/shelpam/in", "r", stdin);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // std::cout.tie(nullptr);

  size_t n{1};
  std::cin >> n;
  for (size_t i{}; i != n; ++i) {
    solve_case();
  }
  return 0;
}
