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
size_t ranking(std::string_view const sv)
{
  size_t ret{};
  if (sv == "BangZhu") {
    return ret;
  }
  ++ret;
  if (sv == "FuBangZhu") {
    return ret;
  }
  ++ret;
  if (sv == "HuFa") {
    return ret;
  }
  ++ret;
  if (sv == "ZhangLao") {
    return ret;
  }
  ++ret;
  if (sv == "TangZhu") {
    return ret;
  }
  ++ret;
  if (sv == "JingYing") {
    return ret;
  }
  ++ret;
  // if (sv == "BangZhong") {
  return ret;
  // }
}
struct player_t {
  std::string name;
  std::string position;
  size_t contribution{};
  size_t level{};
  size_t id{};
  bool operator<(player_t const& other) const
  {
    if (contribution != other.contribution) {
      return contribution > other.contribution;
    }
    return id < other.id;
  }
};
bool cmp(player_t const& lhs, player_t const& rhs)
{
  if (ranking(lhs.position) != ranking(rhs.position)) {
    return ranking(lhs.position) < ranking(rhs.position);
  }
  if (lhs.level != rhs.level) {
    return lhs.level > rhs.level;
  }
  return lhs.id < rhs.id;
}
void change(auto&& coll, size_t const length, std::string_view const sv)
{
  static size_t idx{3};
  for (size_t i{idx}; i < std::ranges::min(coll.size(), length + idx); ++i) {
    coll[i].position = sv;
  }
  idx += length;
}
void solve_case()
{
  size_t n{};
  std::cin >> n;
  std::vector<player_t> players(n);
  for (size_t idx{}; auto&& player: players) {
    player.id = idx++;
    std::cin >> player.name >> player.position >> player.contribution
        >> player.level;
  }
  std::ranges::sort(players | std::ranges::views::drop(3), std::less<>());
  change(players, 2, "HuFa");
  change(players, 4, "ZhangLao");
  change(players, 7, "TangZhu");
  change(players, 25, "JingYing");
  change(players, 0x3f3f, "BangZhong");
  std::ranges::sort(players | std::ranges::views::drop(3), cmp);
  for (auto const& e: players) {
    std::cout << e.name << ' ' << e.position << ' ' << e.level << '\n';
  }
}
int main()
{
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
