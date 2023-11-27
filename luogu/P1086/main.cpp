#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <queue>
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
      : vec2_impl<value_t>(i, std::vector<value_t>(j))
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
auto&& operator>>(auto&& is, auto&& t)
{
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      is >> ele;
    }
  }
  else if constexpr (is_pair<decltype(t)>) {
    is >> t.first >> t.second;
  }
  else {
    is >> t;
  }
  return is;
}
struct pos_t {
  auto operator<=>(pos_t const& o) const { return val <=> o.val; }
  long long i, j;
  size_t val;
};
size_t distance(pos_t a, pos_t b)
{
  return std::abs(a.i - b.i) + std::abs(a.j - b.j);
}
void solve_case()
{
  long long m{};
  long long n{};
  size_t k{};
  std::cin >> m >> n >> k;
  std::priority_queue<pos_t> q;
  for (long long i{}; i != m; ++i) {
    for (long long j{}; j != n; ++j) {
      size_t v{};
      std::cin >> v;
      q.push({i, j, v});
    }
  }
  std::vector<pos_t> path;
  size_t len{static_cast<size_t>(q.top().i + 1)};
  size_t val{};
  pos_t last{q.top()};
  size_t d{};
  while (!q.empty()
         && q.top().i + 1 + len + (d = (distance(q.top(), last) + 1)) <= k) {
    len += d;
    val += q.top().val;
    last = q.top();

    path.push_back(q.top());
    q.pop();
  }
  len += last.i + 1;
  // for (auto const& ele: path) {
  //   std::cout << ele.i << ' ' << ele.j << '\n';
  // }
  std::cout << /* "len: " << len << " val: " << */ val << '\n';
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
