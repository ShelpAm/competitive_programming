#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <string_view>
#include <unordered_set>
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
template<typename value_type> using vec2_impl = std::vector<std::vector<value_type>>;
template<typename value_t> class vec2 : public vec2_impl<value_t> {
public:
  vec2(size_t const i, size_t const j): vec2_impl<value_t>(i, std::vector<value_t>(j)) {}
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
struct dsu {
  dsu(size_t size_): pa(size_), size(size_, 1) { std::iota(pa.begin(), pa.end(), 0); }
  size_t find(size_t const x) { return pa[x] == x ? x : pa[x] = find(pa[x]); }
  void unite(size_t x, size_t y)
  {
    x = find(x);
    y = find(y);
    if (x == y) {
      return;
    }
    if (size[x] < size[y]) {
      std::ranges::swap(x, y);
    }
    pa[y] = x;
    size[x] += size[y];
  }
  bool united(size_t const x, size_t const y) { return find(x) == find(y); }
  std::vector<size_t> pa;
  std::vector<size_t> size;
};
void solve_case()
{
  size_t n{};
  size_t m{};
  std::cin >> n >> m;
  std::vector<std::array<size_t, 2>> conn_data(m);
  std::cin >> conn_data;
  size_t k{};
  std::cin >> k;
  std::vector<size_t> targets(k);
  std::cin >> targets;

  vec2<size_t> conn(n, 0);
  for (auto&& c: conn_data) {
    conn[c[0]].emplace_back(c[1]);
    conn[c[1]].emplace_back(c[0]);
  }
  std::vector<bool> enabled(n, true);
  for (auto const target: targets) {
    enabled[target] = false;
  }

  dsu d(n);
  std::vector<size_t> ans;
  ans.reserve(k + 1);

  size_t num_of_blocks{n - k};
  // Initialize dsu
  for (size_t i{}; i != n; ++i) {
    if (!enabled[i]) {
      continue;
    }
    for (auto const to: conn[i]) {
      if (enabled[to] && !d.united(i, to)) {
        d.unite(i, to);
        --num_of_blocks;
      }
    }
  }
  ans.emplace_back(num_of_blocks);
  for (auto const target: targets | std::ranges::views::reverse) {
    ++num_of_blocks;
    for (auto const to: conn[target]) {
      if (enabled[to] && !d.united(target, to)) {
        d.unite(target, to);
        --num_of_blocks;
      }
    }
    enabled[target] = true;
    ans.emplace_back(num_of_blocks);
  }

  for (auto const a: ans | std::ranges::views::reverse) {
    std::cout << a << '\n';
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
