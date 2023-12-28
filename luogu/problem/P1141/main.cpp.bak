#include <iostream>
#include <queue>
#include <set>
#include <vector>

// configs
using ::std::size_t;

namespace impl {
  template<typename value_t> using vec2 = std::vector<std::vector<value_t>>;
} // namespace impl
template<size_t i, size_t j, typename value_t> using arr2 = std::array<std::array<value_t, j>, i>;
template<size_t i, size_t j> using arr2uz = arr2<i, j, size_t>;
template<size_t i, size_t j> using arr2ll = arr2<i, j, long long>;
template<typename value_t> class vec2 : public impl::vec2<value_t> {
public:
  vec2(size_t const i, size_t const j): impl::vec2<value_t>(i, std::vector<value_t>(j)) {}
};
using vec2uz = vec2<size_t>;
auto&& operator>>(auto&& is, auto&& t)
{
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      is >> ele;
    }
  }
  else {
    is >> t;
  }
  return is;
}
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
void solve_case()
{
  size_t n{};
  size_t m{};
  std::cin >> n >> m;
  vec2<char> v(n, n);
  std::cin >> v;
  vec2uz ans(n, n);
  vec2<bool> visited(n, n);
  for (size_t i{}; i != m; ++i) {
    size_t x{};
    size_t y{};
    std::cin >> x >> y;
    --x;
    --y;
    if (ans[x][y] != 0) {
      std::cout << ans[x][y] << '\n';
      continue;
    }
    size_t head{};
    size_t tail{};
    std::vector<std::pair<size_t, size_t>> q;
    q.emplace_back(x, y);
    visited[x][y] = true;
    ++tail;
    while (head != tail) {
      auto x{q[head].first};
      auto y{q[head].second};
      if (x < n - 1 && v[x + 1][y] != v[x][y] && !visited[x + 1][y]) {
        visited[x + 1][y] = true;
        q.emplace_back(x + 1, y);
        ++tail;
      }
      if (x >= 1 && v[x - 1][y] != v[x][y] && !visited[x - 1][y]) {
        visited[x - 1][y] = true;
        q.emplace_back(x - 1, y);
        ++tail;
      }
      if (y < n - 1 && v[x][y + 1] != v[x][y] && !visited[x][y + 1]) {
        visited[x][y + 1] = true;
        q.emplace_back(x, y + 1);
        ++tail;
      }
      if (y >= 1 && v[x][y - 1] != v[x][y] && !visited[x][y - 1]) {
        visited[x][y - 1] = true;
        q.emplace_back(x, y - 1);
        ++tail;
      }
      ++head;
    }
    for (auto [x, y]: q) {
      ans[x][y] = q.size();
    }
    // print(q);
    std::cout << q.size() << '\n';
  }
}
int main()
{
  // freopen("/home/shelpam/in", "r", stdin);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve_case();
  return 0;
}
