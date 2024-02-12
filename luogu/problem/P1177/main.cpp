#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <string_view>
#include <vector>

using ::std::size_t;
using namespace std::ranges;

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
void bubble_sort(auto&& coll, auto&& cmp)
{
  for (size_t i{}; i != coll.size(); ++i) {
    for (auto it{coll.begin()}; it != coll.end() - 1; ++it) {
      auto next{it + 1};
      if (!cmp(*it, *next)) {
        std::ranges::swap(*it, *next);
      }
    }
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
size_t height(auto&& v)
{
  return std::ceil(std::log2(v.size() + 1));
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
  if (v[father] < v[greater_son]) {
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
void quick_sort(auto&& coll, long long const l, long long const r)
{
  if (l >= r) {
    return;
  }
  auto const pivot{coll[(l + r) >> 1]};
  long long i{l - 1};
  long long j{r + 1};
  while (i < j) {
    while (coll[++i] < pivot) {
    }
    while (coll[--j] > pivot) {
    }
    if (i < j) {
      swap(coll[i], coll[j]);
    }
  }
  // debug("i", i);
  // debug("j", j);
  quick_sort(coll, l, j);
  quick_sort(coll, j + 1, r);
}
void merge_sort(random_access_range auto&& coll, size_t const l, size_t const r)
{
  if (l >= r) {
    return;
  }
  auto m{(l + r) >> 1};
  merge_sort(coll, l, m);
  merge_sort(coll, m + 1, r);
  std::remove_cvref_t<decltype(coll)> copy;
  copy.reserve(r - l + 1);
  size_t i{l};
  size_t j{m + 1};
  while (i != m + 1 && j != r + 1) {
    copy.emplace_back(coll[i] < coll[j] ? coll[i++] : coll[j++]);
  }
  while (i != m + 1) {
    copy.emplace_back(coll[i++]);
  }
  while (j != r + 1) {
    copy.emplace_back(coll[j++]);
  }
  std::ranges::copy(copy, coll.begin() + l);
}
void my_sort(auto&& coll)
{
  merge_sort(coll, 0, coll.size() - 1);
  // quick_sort(coll, 0, coll.size() - 1);
  // heap_sort(coll);
}
void solve_case()
{
  size_t n{};
  std::cin >> n;
  std::vector<size_t> v(n);
  for (auto&& e: v) {
    std::cin >> e;
  }
  my_sort(v);
  print(v);
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
