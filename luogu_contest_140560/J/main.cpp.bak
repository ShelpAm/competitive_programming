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
struct dir {
  dir(long long x, long long y): i(x), j(y) {}
  dir& operator+=(dir const& other)
  {
    i += other.i;
    j += other.j;
    return *this;
  }
  dir operator+(dir const& other) { return (*this) += other; }
  long long i, j;
};
void solve_case()
{
  size_t n{};
  size_t m{};
  std::cin >> n >> m;
  vec2uz v(n, m);
  input(v);

  auto get_room{[&](dir const d) {
    if (d.i >= 0 && d.i < n && d.j >= 0 && d.j < m) {
      return v[d.i][d.j];
    }
    return 0UZ;
  }};

  std::array<dir, 4> const dirs{dir{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

  size_t num_of_normal_hidden_room{};
  size_t num_of_super_hidden_room{};
  for (size_t i{}; i != n; ++i) {
    for (size_t j{}; j != m; ++j) {
      size_t count_of_normal_room{};
      if (get_room(dir(i, j)) != 1) {
        continue;
      }
      for (auto&& curr_dir: dirs) {
        auto curr_pos{dir(i, j) + curr_dir};
        // boss房
        if (get_room(curr_pos) == 3) {
          count_of_normal_room = 0;
          break;
        }
        if (get_room(curr_pos) == 2) {
          ++count_of_normal_room;
        }
      }
      if (count_of_normal_room >= 3) {
        ++num_of_normal_hidden_room;
      }
      if (count_of_normal_room == 1) {
        ++num_of_super_hidden_room;
      }
    }
  }
  std::cout << num_of_normal_hidden_room << ' ' << num_of_super_hidden_room;
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
