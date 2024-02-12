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
struct pos_t {
  auto operator<=>(pos_t const&) const = default;
  long long x;
  long long y;
};
auto distance(pos_t const& lhs, pos_t const& rhs)
{
  return std::sqrt(std::pow(lhs.x - rhs.x, 2) + std::pow(lhs.y - rhs.y, 2));
}
void solve_case()
{
  size_t n, k, t;
  std::cin >> n >> k >> t;
  std::vector<pos_t> machine(n);
  std::vector<pos_t> special_machine(k);
  std::vector<pos_t> bad_machine(t);

  for (size_t i{}; i != n; ++i) {
    std::cin >> machine[i].x >> machine[i].y;
  }
  for (size_t i{}; i != k; ++i) {
    std::cin >> special_machine[i].x >> special_machine[i].y;
  }
  for (size_t i{}; i != t; ++i) {
    std::cin >> bad_machine[i].x >> bad_machine[i].y;
  }
  std::ranges::sort(special_machine);

  size_t count{};
  for (auto&& bm: bad_machine) {
    decltype(distance({}, {})) max_distance{};
    pos_t most_distant_pos{};
    for (auto&& m: machine) {
      if (auto new_distance{distance(m, bm)}; new_distance > max_distance) {
        max_distance = new_distance;
        most_distant_pos = m;
      }
    }
    if (std::ranges::binary_search(special_machine, most_distant_pos)) {
      ++count;
    }
  }
  std::cout << count;
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
