#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <numeric>
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
struct player_t {
  size_t id;
  size_t score;
  size_t strength;
  bool operator<(player_t const& other) const
  {
    if (score != other.score) {
      return score < other.score;
    }
    return id > other.id;
  }
  bool operator>(player_t const& other) const
  {
    if (score != other.score) {
      return score > other.score;
    }
    return id < other.id;
  }
};
void solve_case()
{
  size_t n{};
  size_t r{};
  size_t q{};
  std::cin >> n >> r >> q;
  std::vector<player_t> v(2 * n);
  for (size_t i{}; auto&& e: v) {
    std::cin >> e.score;
    e.id = ++i;
  }
  for (auto&& e: v) {
    std::cin >> e.strength;
  }

  std::ranges::sort(v, std::greater<>());
  for (size_t i{}; i != r; ++i) {
    decltype(v) winners;
    decltype(v) losers;
    winners.reserve(n);
    losers.reserve(n);
    // std::cout << "List of players:\n";
    // for (auto const& e: v) {
    //   std::cout << e.id << ' ' << e.score << ' ' << e.strength << '\n';
    // }
    for (size_t j{}; j != n; ++j) {
      if (v[2 * j].strength < v[2 * j + 1].strength) {
        ++v[2 * j + 1].score;
        winners.emplace_back(v[2 * j + 1]);
        losers.emplace_back(v[2 * j]);
      }
      else {
        ++v[2 * j].score;
        winners.emplace_back(v[2 * j]);
        losers.emplace_back(v[2 * j + 1]);
      }
    }
    // merge_sort(v, 0, v.size() - 1);
    std::ranges::merge(winners, losers, v.begin(), std::greater<>());
  }
  std::cout << v[q - 1].id;
}
int main()
{
  // std::freopen("/mnt/c/Users/11785/Downloads/in", "r", stdin);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // std::cout.tie(nullptr);

  size_t n{1};
  // n = read<size_t>();
  for (size_t i{}; i != n; ++i) {
    solve_case();
  }
  return 0;
}
