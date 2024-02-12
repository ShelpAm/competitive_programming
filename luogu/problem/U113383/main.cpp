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
void flip(auto&& v, size_t const i, size_t const j)
{
  if (i >= 0 && i < v.size() && j >= 0 && j < v[0].size()) {
    v[i][j] ^= 1;
  }
}
void operate(auto&& v, size_t const i, size_t const j)
{
  flip(v, i, j);
  flip(v, i + 1, j);
  flip(v, i - 1, j);
  flip(v, i, j + 1);
  flip(v, i, j - 1);
}
auto operated(auto const& v, size_t const i, size_t const j)
{
  auto res{v};
  operate(res, i, j);
  return res;
}
size_t dfs(auto&& v, size_t const pos, size_t const num_of_steps)
{
  if (pos == 5) {
    // std::cout << "There have been " << num_of_steps + 1 << " steps taken\n";
    // print(v);
    // auto sth = [=](auto&& my) {
    //   if (num_of_steps == 1 || (v[0][0] == '1' && v[0][1] == 1)) {
    //     print(my);
    //   }
    // };
    auto copied_v{v};
    auto n{num_of_steps};
    for (size_t i{1}; i != 5; ++i) {
      for (size_t j{}; j != 5; ++j) {
        if (n == 6 && std::ranges::any_of(v, [](auto&& v) {
              return std::ranges::any_of(v, [](auto&& t) { return t == '0'; });
            })) {
          return -1UZ;
        }
        if (copied_v[i - 1][j] == '0') {
          // sth(v);
          operate(copied_v, i, j);
          ++n;
        }
      }
    }
    return n;
  }
  return std::ranges::min(dfs(operated(v, 0, pos), pos + 1, num_of_steps + 1),
                          dfs(v, pos + 1, num_of_steps));
}
void solve_case()
{
  size_t n{};
  std::cin >> n;
  std::vector<vec2<char>> vv(n, vec2<char>(5, 5));
  input(vv);
  for (auto&& v: vv) {
    std::cout << static_cast<long long>(dfs(v, 0, 0)) << '\n';
  }
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
