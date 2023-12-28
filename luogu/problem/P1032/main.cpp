#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <queue>
#include <ranges>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// configs
using ::std::size_t;
using ::std::unordered_map;

namespace impl {
  template<typename value_t> using vec2 = std::vector<std::vector<value_t>>;
  template<typename T> concept is_pair = requires(T t) {
    t.first;
    t.second;
  };
} // namespace impl
template<size_t i, size_t j, typename value_t> using arr2 = std::array<std::array<value_t, j>, i>;
template<size_t i, size_t j> using arr2uz = arr2<i, j, size_t>;
template<size_t i, size_t j> using arr2ll = arr2<i, j, long long>;
template<typename value_t> class vec2 : public impl::vec2<value_t> {
public:
  vec2(size_t const i, size_t const j): impl::vec2<value_t>(i, std::vector<value_t>(j)) {}
};
using vec2uz = vec2<size_t>;
using vec2ll = vec2<long long>;
auto&& operator>>(auto&& is, auto&& t)
{
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      is >> ele;
    }
  }
  else if constexpr (impl::is_pair<decltype(t)>) {
    is >> t.first >> t.second;
  }
  else {
    is >> t;
  }
  return is;
}
auto&& operator<<(auto&& os, auto&& t)
{
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      os << ele << ' ';
    }
    os << '\n';
  }
  else if constexpr (impl::is_pair<decltype(t)>) {
    os << t.first << ": " << t.second << ", ";
  }
  else {
    os << t << ' ';
  }
  return os;
}
void debug([[maybe_unused]] std::string_view const& sv, [[maybe_unused]] auto&& t)
{
#ifdef DEBUG
  std::cout << sv << ": " << t << '\n';
#endif
}
void solve_case()
{
  std::string x;
  std::string y;
  std::cin >> x >> y;
  std::unordered_multimap<std::string, std::string> mapping;
  std::string lhs;
  std::string rhs;
  while (std::cin >> lhs >> rhs) {
    mapping.emplace(lhs, rhs);
  }

  struct pos_t {
    std::string s;
    size_t depth;
  };

  auto transformed{[&](std::string_view const s) {
    std::vector<std::string> ret;
    for (size_t i{}; i != s.size(); ++i) {
      for (auto&& [src, dest]: mapping) {
        if (auto idx{s.find(src, i)}; idx != std::string::npos) {
          std::string copy{s};
          copy.replace(idx, src.size(), dest);
          ret.emplace_back(copy);
        }
      }
    }
    return ret;
  }};

  std::unordered_set<std::string> visited;
  std::queue<pos_t> q;
  q.push({x, 0});
  while (!q.empty()) {
    if (q.front().s == y) {
      std::cout << q.front().depth;
      return;
    }
    if (!visited.contains(q.front().s)) {
      visited.emplace(q.front().s);
      // std::cout << "From " << q.front().s << '\n';
      for (auto&& ele: transformed(q.front().s)) {
        // std::cout << "\tTo " << ele << '\n';
        q.push({ele, q.front().depth + 1});
      }
    }
    q.pop();
  }
  std::cout << "NO ANSWER!";
}
int main()
{
  // std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // std::cout.tie(nullptr);

  size_t t{1};
  // std::cin >> t;
  for (size_t i{}; i != t; ++i) {
    solve_case();
  }
  return 0;
}
