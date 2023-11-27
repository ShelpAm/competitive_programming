#include <array>
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
size_t second_min_i(auto&& v)
{
  int min = v[0];
  int second_min_v = v[0];
  size_t second_min_index{0};
  for (int i = 1; i != v.size(); i++) {
    if (v[i] < min) {
      second_min_v = min;
      second_min_index = i;
      min = v[i];
    }
    else if (v[i] < second_min_v && v[i] != min) {
      second_min_v = v[i];
      second_min_index = i;
    }
  }
  return second_min_index;
}
void dfs(auto&& v, auto&& dis, size_t const from)
{
  if (from == v.size() - 1) {
    return;
  }
  size_t to{second_min_i(v[from])};
  std::cout << to << ' ';
  dis[to] = std::ranges::min(dis[to], v[from][to]);
  dfs(v, dis, to);
}
void solve_case()
{
  size_t n{};
  size_t a{};
  size_t b{};
  size_t c{};
  std::cin >> n >> a >> b >> c;
  vec2uz v(n, n);
  input(v);
  std::vector<size_t> dis(n, 0xffffffff);
  dfs(v, dis, 0);
}
int main()
{
  auto n{1UZ};
  // n = read<size_t>();
  for (size_t i{}; i != n; ++i) {
    solve_case();
  }
  return 0;
}
