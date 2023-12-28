#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <ranges>
#include <string_view>
#include <vector>

// configs
using ::std::size_t;

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
constexpr size_t hex_base{16};
void solve_case()
{
  std::vector<size_t> bytes;
  std::string s;
  while (std::cin >> s) {
    size_t val{};
    for (size_t i{}; i != 2; ++i) {
      val = hex_base * val + (std::isdigit(s[i]) ? s[i] - '0' : s[i] + 10 - 'a');
    }
    bytes.emplace_back(val);
  }

  bool c{false};
  bool pascal{false};
  for (size_t i{}; i != bytes.size(); ++i) {
    if (bytes[i] == 0) {
      c = true;
      break;
    }
    if (bytes[i] < 0x20 || bytes[i] > 0x7f) {
      c = false;
      break;
    }
  }
  for (size_t i{1}; i != bytes.size(); ++i) {
    if (i == bytes[0] + 1) {
      pascal = true;
      break;
    }
    if (bytes[i] < 0x20 || bytes[i] > 0x7f) {
      pascal = false;
      break;
    }
  }

  if (c && pascal) {
    std::cout << "Both";
  }
  else if (c && !pascal) {
    std::cout << "C";
  }
  else if (!c && pascal) {
    std::cout << "Pascal";
  }
  else {
    std::cout << "None";
  }
}
int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // std::cout.tie(nullptr);

  size_t t{1};
  // std::cin >> t;
  for (size_t i{}; i != t; ++i) {
    solve_case();
  }
  return 0;
}
