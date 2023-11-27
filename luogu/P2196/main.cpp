#include <algorithm>
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
std::vector<size_t> best_path;
std::vector<size_t> curr_path;
size_t best_val{};
size_t curr_val{};
void search(auto&& values, auto&& is_connected, size_t const visited,
            size_t const src)
{
  curr_path.push_back(src);
  curr_val += values[src];
  if (curr_val > best_val) {
    best_val = curr_val;
    best_path = curr_path;
  }
  // print(curr_path);
  for (size_t dst{}; dst != values.size(); ++dst) {
    if (is_connected[src][dst] == 0) {
      continue;
    }
    if ((visited >> dst & 1) == 1) {
      continue;
    }
    search(values, is_connected, visited ^ (1ULL << dst), dst);
  }
  curr_path.pop_back();
  curr_val -= values[src];
}
void solve_case()
{
  size_t n{};
  std::cin >> n;
  std::vector<size_t> nums_of_landmines(n);
  input(nums_of_landmines);
  vec2<size_t> connectivities(n, n);
  // By default, connectivity[i][i] equals 0;
  for (size_t i{0}; i != n - 1; ++i) {
    for (size_t j{i + 1}; j != n; ++j) {
      std::cin >> connectivities[i][j];
      // The following is wrong because it is an one-way graph
      // connectivities[j][i] = connectivities[i][j];
    }
  }

  for (size_t i{}; i != n; ++i) {
    search(nums_of_landmines, connectivities, 1UZ << i, i);
  }
  print(best_path
        | std::ranges::views::transform([](auto const t) { return t + 1; }));
  std::cout << best_val;
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
