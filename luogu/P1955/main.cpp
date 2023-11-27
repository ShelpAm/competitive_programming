#include <array>
#include <cstddef>
#include <iostream>
#include <map>
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
};
using vec2uz = vec2<size_t>;
using vec2ll = vec2<long long>;
template<typename T> concept is_pair = requires(T& t) {
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
void solve_case()
{
  size_t k{1};
  std::map<long long, size_t> mapping;
  std::vector<std::array<long long, 2>> unequals;
  auto allocate{[&mapping, &k](auto&& i) {
    mapping[i] = k;
    ++k;
  }};
  input_value<size_t> n;
  bool test{true};
  for (auto&& t: std::ranges::views::iota(size_t(0), n.value())) {
    input_value<long long> i;
    input_value<long long> j;
    input_value<long long> e;
    if (!test) {
      continue;
    }
    auto contains_i{mapping.contains(i)};
    auto contains_j{mapping.contains(j)};
    if (e == 1) {
      if (!contains_i && !contains_j) {
        allocate(i);
        mapping[j] = mapping[i];
        continue;
      }
      if (!contains_i && contains_j) {
        mapping[i] = mapping[j];
      }
      if (contains_i && !contains_j) {
        mapping[j] = mapping[i];
      }
      if (mapping[i] != mapping[j]) {
        test = false;
      }
    }
    else {
      // e == 0
      // deferring e==0 operations
      unequals.push_back({i, j});
    }
  }
  if (!test) {
    std::cout << "NO\n";
    return;
  }
  for (auto&& e: unequals) {
    auto contains_i{mapping.contains(e[0])};
    auto contains_j{mapping.contains(e[1])};
    if (!contains_i) {
      allocate(e[0]);
    }
    if (!contains_j) {
      allocate(e[1]);
    }
    if (mapping[e[0]] == mapping[e[1]]) {
      std::cout << "NO\n";
      return;
    }
  }
  std::cout << "YES\n";
  // print(mapping);
}
int main()
{
  auto n{1UZ};
  n = read<size_t>();
  for (size_t i{}; i != n; ++i) {
    solve_case();
  }
  return 0;
}
