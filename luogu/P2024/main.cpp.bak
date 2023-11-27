#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
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
struct dsu {
  dsu(size_t const size_): pa(size_), size(size_, 1), hunter(size_, -1UZ)
  {
    std::iota(pa.begin(), pa.end(), 0);
  }
  size_t find(size_t const x) { return pa[x] == x ? x : pa[x] = find(pa[x]); }
  void unite(size_t x, size_t y)
  {
    x = find(x);
    y = find(y);
    if (x == y) {
      return;
    }
    if (size[x] < size[y]) {
      std::ranges::swap(size[x], size[y]);
    }
    pa[y] = x;
    size[x] += size[y];
    set_hunter(y, x);
  }
  void set_hunter(size_t const x, size_t const hunter_)
  {
    if (find(x) == find(hunter_)) {
      std::cout << "find(x) == find(hunter_)\n";
    }
    hunter[find(x)] = find(hunter_);
  }
  size_t get_hunter(size_t const x) { return hunter[find(x)]; }
  bool is_together(size_t const x, size_t const y)
  {
    return find(x) == find(y);
  }
  std::vector<size_t> pa;
  std::vector<size_t> size;
  std::vector<size_t> hunter;
};
bool do_test(size_t const op, size_t const x, size_t const y, size_t const n,
             dsu& d)
{
  if (x > n || y > n) {
    return false;
  }
  if (op == 1) {
    if (x == y) {
      return true;
    }
    // 原来就在一个集合中
    if (d.is_together(x, y)) {
      return true;
    }
    // 不在一个集合中，但是捕食者相同
    if (d.get_hunter(x) == d.get_hunter(y)) {
      d.unite(x, y);
      return true;
    }
    // 只有一个有捕食者
    bool a{d.get_hunter(x) == -1UZ};
    bool b{d.get_hunter(y) == -1UZ};
    if (a && !b) {
      d.unite(x, y);
      return true;
    }
    if (!a && b) {
      d.unite(x, y);
      return true;
    }
    // 都没有捕食者且不在一个集合中（可能是未初始化）
    if (d.find(x) == x || d.find(y) == y) {
      d.unite(x, y);
      return true;
    }
    return false;
  }
  if (op == 2) {
    if (d.is_together(x, y)) {
      std::cout << x << " and " << y
                << " cannot eat each other because they are the same specie\n";
      return false;
    }
    if (d.get_hunter(y) != -1UZ && !d.is_together(d.get_hunter(y), x)) {
      // std::cout << d.get_hunter(y) << " eats " << y
      //           << ", but the given relaton is " << d.find(x) << " eats " <<
      //           y
      //           << '\n';
      return false;
    }
    d.set_hunter(y, x);
    return true;
  }
  // return false;
}
void solve_case()
{
  size_t n{};
  size_t k{};
  std::cin >> n >> k;
  dsu d(n + 1);
  size_t num_false{};
  // size_t num_existed_type{};
  for (size_t i{}; i != k; ++i) {
    size_t op{};
    size_t x{};
    size_t y{};
    std::cin >> op >> x >> y;
    if (!do_test(op, x, y, n, d)) {
      ++num_false;
      // std::cout << i << '\n';
    }
  }
  std::cout << num_false;
  // std::set<size_t> roots;
  // for (size_t i{1}; i != n + 1; ++i) {
  //   // roots.emplace(d.find(i));
  //   std::cout << d.find(i) << ' ';
  // }
  // std::cout << "DUMP ROOTS: ";
  // print(roots);
}
int main()
{
  std::freopen("/mnt/c/Users/11785/Downloads/in.in", "r", stdin);
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
