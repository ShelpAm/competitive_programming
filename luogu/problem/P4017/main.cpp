#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <map>
#include <ranges>
#include <set>
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
template<typename value_t> class input_value {
public:
  input_value(): value_(read<value_t>()) {}
  input_value(const input_value&) = delete;
  input_value(input_value&&) = delete;
  input_value& operator=(const input_value&) = delete;
  input_value& operator=(input_value&&) = delete;
  ~input_value() = default;
  operator value_t&() { return value(); }
  value_t& value() { return value_; }
private:
  value_t value_;
};
template<size_t i, size_t j, typename value_type> using arr2
    = std::array<std::array<value_type, j>, i>;
template<size_t i, size_t j> using arr2uz = arr2<i, j, size_t>;
template<size_t i, size_t j> using arr2ll = arr2<i, j, long long>;
template<typename value_type> using vec2_impl
    = std::vector<std::vector<value_type>>;
template<typename value_t> class vec2 : public vec2_impl<value_t> {
public:
  vec2(size_t const i, size_t const j)
      : vec2_impl<value_t>(i, std::vector<value_t>(j, {}))
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
void input(auto&& t)
{
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      input(ele);
    }
  }
  else if constexpr (is_pair<decltype(t)>) {
    std::cin >> t.first >> t.second;
  }
  else {
    std::cin >> t;
  }
}
// size_t search(auto&& chain, size_t const hunter)
// {
//   static std::array<size_t, 5002> length{};
//   if (length[hunter] != 0) {
//     return length[hunter];
//   }
//   size_t res{};
//   auto foods{chain[hunter]};
//   for (auto&& food: foods) {
//     res = std::ranges::max(res, search(chain, food));
//   }
//   return length[hunter] = res + 1;
// }
// size_t max_length(auto&& chain)
// {
//   size_t res{};
//   for (auto&& mapping: chain) {
//     res = std::ranges::max(res, search(chain, mapping.first));
//   }
//   return res;
// }
size_t search(auto&& chain, size_t const hunter)
{
  static std::array<size_t, 5002> ans{};
  if (ans[hunter] != 0) {
    return ans[hunter];
  }
  // std::cout << "Searching hunter " << hunter << '\n';
  if (!chain.contains(hunter)) {
    return ans[hunter] = 1;
  }
  size_t res{};
  for (auto foods{chain[hunter]}; auto&& food: foods) {
    res += search(chain, food);
  }
  return ans[hunter] = res % 80112002;
}
void solve_case()
{
  size_t n{};
  size_t m{};
  std::cin >> n >> m;
  std::vector<bool> has_father(n + 1, false);
  std::map<size_t, std::set<size_t>>
      food_chain; // food_chain[a] represents what
  // should be eated by a. food_chain[a] being 0 means 'a' have no food to eat,
  // that is, it is the end of a food chain.
  for (size_t i{}; i != m; ++i) {
    size_t food{};
    size_t hunter{};
    std::cin >> food >> hunter;
    food_chain[hunter].emplace(food);
    has_father[food] = true;
  }

  size_t res{};
  for (auto&& mapping: food_chain) {
    if (!has_father[mapping.first]) {
      res += search(food_chain, mapping.first) % 80112002;
    }
  }
  std::cout << res % 80112002;
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