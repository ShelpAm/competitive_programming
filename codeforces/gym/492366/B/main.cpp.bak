#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <map>
#include <ranges>
#include <string_view>
#include <unordered_map>
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
// auto&& operator<<(auto&& os, auto&& t)
// {
//   if constexpr (std::ranges::range<decltype(t)>) {
//     for (auto&& ele: t) {
//       os << ele << ' ';
//     }
//     os << '\n';
//   }
//   else if constexpr (impl::is_pair<decltype(t)>) {
//     os << t.first << ": " << t.second << ", ";
//   }
//   else {
//     os << t << ' ';
//   }
//   return os;
// }
void debug([[maybe_unused]] std::string_view const& sv, [[maybe_unused]] auto&& t)
{
#ifdef DEBUG
  std::cout << sv << ": " << t << '\n';
#endif
}
struct player_t {
  static size_t head;
  long long score{};
  size_t id{};
};
constexpr size_t initial_num_player{5};
size_t player_t::head{2 * initial_num_player};
void solve_case()
{
  using team_t = std::unordered_map<std::string, player_t>;
  std::unordered_map<std::string, team_t> activated;
  std::unordered_map<std::string, team_t> deactivated;
  for (size_t i{}; i != 2; ++i) {
    std::string team;
    std::cin >> team;
    for (size_t j{}; j != initial_num_player; ++j) {
      std::string name;
      std::cin >> name;
      // DESIGNATED INITIALIZER
      activated[team].emplace(name, player_t{.score = 0, .id = i * initial_num_player + j});
    }
  }
  size_t q{};
  std::cin >> q;
  while (q-- != 0) {
    std::string s;
    std::string t;
    std::cin >> s >> t;
    std::cin >> s;
    if (s == "scored") {
      long long score{};
      std::cin >> score;
      for (auto&& [team_name, team]: activated) {
        if (team_name == t) {
          for (auto&& [player_name, info]: team) {
            info.score += score;
          }
        }
        else {
          for (auto&& [player_name, info]: team) {
            info.score -= score;
          }
        }
      }
    }
    else {
      // s == "replaced"
      std::string from;
      std::string to;
      std::cin >> from >> s >> to;
      if (!deactivated[t].contains(to)) {
        deactivated[t][to].id = player_t::head++;
      }
      deactivated[t].emplace(from, activated[t][from]);
      activated[t].emplace(to, deactivated[t][to]);
      deactivated[t].erase(to);
      activated[t].erase(from);
      // std::swap(deactivated[t][to], activated[t][from]);
    }
  }

  std::vector<std::tuple<std::string, std::string, player_t>> p;
  for (auto const& [team_name, team]: activated) {
    for (auto const& [player_name, info]: team) {
      p.emplace_back(player_name, team_name, player_t{info.score, info.id});
    }
  }
  for (auto const& [team_name, team]: deactivated) {
    for (auto const& [player_name, info]: team) {
      p.emplace_back(player_name, team_name, player_t{info.score, info.id});
    }
  }
  std::ranges::sort(
      p, [](auto&& lhs, auto&& rhs) { return std::get<2>(lhs).id < std::get<2>(rhs).id; });
  for (auto&& [player_name, team_name, info]: p) {
    std::cout << player_name << " (" << team_name << ") " << (info.score > 0 ? "+" : "")
              << info.score << '\n';
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
