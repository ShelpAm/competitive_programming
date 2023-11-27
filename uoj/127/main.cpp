#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <map>
#include <numeric>
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
    std::cerr << t << ' ';
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
  dsu(size_t size_): pa(size_), size(size_, 1)
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
  }
  bool is_together(size_t const x, size_t const y)
  {
    return find(x) == find(y);
  }
  std::vector<size_t> pa;
  std::vector<size_t> size;
};
void discretize(std::vector<size_t>& a)
{
  auto t{a};
  std::ranges::sort(t);
  auto const m{std::unique(t.begin(), t.end()) - t.begin()};
  for (size_t i{}; i != a.size(); ++i) {
    a[i] = std::ranges::lower_bound(t.begin(), t.begin() + m, a[i]) - t.begin();
  }
}
void solve_case()
{
  size_t n{};
  std::cin >> n;
  std::vector<size_t> ij(2 * n);
  std::vector<size_t> e(n);
  for (size_t i{}; i != n; ++i) {
    std::cin >> ij[2 * i] >> ij[2 * i + 1] >> e[i];
  }
  discretize(ij);

  std::vector<size_t> idx(n);
  std::iota(idx.begin(), idx.end(), 0);
  std::ranges::sort(idx, [&e](size_t l, size_t r) { return e[l] > e[r]; });

  // print(idx);
  // print(ij);
  dsu d(2 * n);

  auto succussful{[&idx, &e, &ij, &d]() {
    for (auto const i: idx) {
      if (e[i] == 1) {
        d.unite(ij[2 * i], ij[2 * i + 1]);
      }
      else {
        if (d.is_together(ij[2 * i], ij[2 * i + 1])) {
          return false;
        }
      }
    }
    return true;
  }()};
  std::cout << (succussful ? "YES" : "NO") << '\n';
}
int main()
{
  // freopen("/mnt/c/Users/11785/Downloads/in.in", "r", stdin);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // std::cout.tie(nullptr);

  size_t n{1};
  n = read<size_t>();
  for (size_t i{}; i != n; ++i) {
    solve_case();
  }
  return 0;
}
