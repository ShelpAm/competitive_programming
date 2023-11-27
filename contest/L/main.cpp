#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
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
    std::cout << t + 1 << ' ';
  }
}
bool can_place(auto&& pos_of, std::int8_t const row, std::int8_t const p)
{
  for (std::int8_t i{}; i != row; ++i) {
    if (pos_of[i] == p || abs(pos_of[i] - p) == abs(i - row)) {
      return false;
    }
  }
  return true;
}
size_t search(auto& pos_of, size_t row)
{
  static size_t count{};
  if (row == pos_of.size()) {
    if (count != 3) {
      print(pos_of);
      ++count;
    }
    return 1;
  }
  size_t sum{};
  for (size_t i{}; i != pos_of.size(); ++i) {
    if (can_place(pos_of, row, i)) {
      pos_of[row] = i;
      sum += search(pos_of, row + 1);
    }
  }
  return sum;
}
void solve_case()
{
  size_t a{read<size_t>()};
  //   if (a == 13) {
  //     std::cout << R"(1 3 5 2 9 12 10 13 4 6 8 11 7
  // 1 3 5 7 9 11 13 2 4 6 8 10 12
  // 1 3 5 7 12 10 13 6 4 2 8 11 9
  // 73712)";
  //     return;
  //   }
  std::vector<std::int8_t> pos_vec(a);
  auto count{search(pos_vec, 0)};
  std::cout << count;
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
