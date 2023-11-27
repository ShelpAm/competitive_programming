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
vec2<char> rotate_90(vec2<char> const& data)
{
  vec2<char> result(data.size(), data.size());
  for (size_t i{}; i != data.size(); ++i) {
    for (size_t j{}; j != data.size(); ++j) {
      result[j][data.size() - 1 - i] = data[i][j];
    }
  }
  return result;
}
vec2<char> flip(vec2<char> const& data)
{
  vec2<char> result(data.size(), data.size());
  for (size_t i{}; i != data.size(); ++i) {
    for (size_t j{}; j != data.size(); ++j) {
      result[i][data.size() - 1 - j] = data[i][j];
    }
  }
  return result;
}
vec2<char> transform(size_t const method_id, vec2<char> const& data,
                     size_t const j)
{
  if (method_id <= 3) {
    vec2<char> result{data};
    for (size_t i{}; i != method_id; ++i) {
      result = rotate_90(result);
    }
    return result;
  }
  if (method_id == 4) {
    return flip(data);
  }
  if (method_id == 5) {
    return transform(j, flip(data), 0);
  }
  if (method_id == 6) {
    return data;
  }
  std::cout << 7;
  std::exit(0);
}
void solve_case()
{
  size_t n{};
  std::cin >> n;
  vec2<char> mat(n, n);
  vec2<char> dst(n, n);
  input(mat);
  input(dst);
  for (size_t i{1}; i != 8; ++i) {
    for (size_t j{1}; j != 4; ++j) {
      // std::cout << i << ' ' << j << '\n';
      // print(transform(i, mat, j));
      if (transform(i, mat, j) == dst) {
        std::cout << i;
        return;
      }
    }
  }
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
