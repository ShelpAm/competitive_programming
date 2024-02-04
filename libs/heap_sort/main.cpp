#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iomanip>
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
size_t height(auto&& v)
{
  return std::ceil(std::log2(v.size() + 1));
}
void print_tree(auto&& v)
{
  size_t h = height(v);
  size_t n{};
  for (size_t i{}; i != h; ++i) {
    std::cout << std::string(std::pow(2, h - i - 1), ' ');
    for (size_t j{}; j != std::pow(2, i); ++j) {
      std::cout << /* std::setw(3) << */ v[n++]
                << std::string(std::pow(2, h - i) - 1, ' ');
      if (n == v.size()) {
        std::cout << '\n';
        return;
      }
    }
    std::cout << '\n';
  }
}
void swap_node(auto&& v, size_t const son)
{
  // std::cout << "Swapping\n";
  size_t father{(son - 1) / 2};
  if (son < v.size() && v[father] < v[son]) {
    std::ranges::swap(v[father], v[son]);
  }
  // std::cout << "Swapped\n";
}
void heapify(auto&& v, size_t const begin, size_t const end)
{
  for (size_t j{end}; j != begin - 1; --j) {
    swap_node(v, j);
    // print_tree(v);
  }
}
void adjust(auto&& v, size_t const last_activated, size_t const father)
{
  if (last_activated == -1UZ) {
    return;
  }
  std::array<size_t, 2> sons{father * 2 + 1, father * 2 + 2};
  if (sons[0] > last_activated) {
    return;
  }
  size_t greater_son{sons[0]};
  if (sons[1] <= last_activated) {
    greater_son = std::ranges::max(
        greater_son, sons[1],
        [&v](auto const l, auto const r) { return v[l] < v[r]; });
  }
  if (v[greater_son] > v[father]) {
    std::ranges::swap(v[greater_son], v[father]);
    // print_tree(v);
    adjust(v, last_activated, greater_son);
  }
  // std::cout << "Adjusted\n";
}
void heap_sort(auto&& v)
{
  for (size_t i{}; i != height(v); ++i) {
    heapify(v, 1, v.size() - 1);
  }
  // std::cout << "Heapified: \n";
  // print_tree(v);

  for (auto const i:
       std::ranges::views::iota(0UZ, v.size()) | std::ranges::views::reverse) {
    std::ranges::swap(v[0], v[i]);
    // std::cout << "The top has been adjusted.\n";
    // print_tree(v);
    adjust(v, i - 1, 0);
    // std::cout << '\n';
  }
}
void solve_case()
{
  std::vector<size_t> v{1, 5, 3, 7, 9, 9, 1, 5};
  heap_sort(v);
  // std::cout << "The result: ";
  print(v);
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
