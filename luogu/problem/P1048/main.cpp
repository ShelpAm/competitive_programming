#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <ranges>
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
  vec2(size_t const i, size_t const j, value_t const val)
      : vec2_impl<value_t>(i, std::vector<value_t>(j, val))
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
size_t search(long long const pos, size_t const t_left, auto&& costs,
              auto&& values)
{
  static vec2ll mem{103, 1003, -1};
  if (pos == -1) {
    return 0;
  }
  if (mem[pos][t_left] != -1) {
    return mem[pos][t_left];
  }
  if (t_left < costs[pos]) {
    return mem[pos][t_left] = search(pos - 1, t_left, costs, values);
  }
  return mem[pos][t_left] = std::ranges::max(
             search(pos - 1, t_left - costs[pos], costs, values) + values[pos],
             search(pos - 1, t_left, costs, values));
}
void solve_case()
{
  auto t{read<size_t>()};
  auto m{read<size_t>()};
  std::vector<size_t> costs(m);
  std::vector<size_t> values(m);
  for (size_t i{}; i != m; ++i) {
    std::cin >> costs[i] >> values[i];
  }
  std::cout << search(static_cast<long long>(m - 1), t, costs, values);
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
