#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <string>
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
void solve_case()
{
  size_t n{};
  size_t m{};
  std::cin >> n >> m;
  std::vector<size_t> a(m);
  for (size_t i{}; i != m; ++i) {
    std::cin >> a[i];
    // a[i] += i;
  }
  std::vector<size_t> scores(n);
  for (size_t i{}; i != n; ++i) {
    scores[i] = i;
  }
  std::vector<std::vector<size_t>> remainders(n);
  // calculates scores
  for (size_t i{}; i != n; ++i) {
    std::string s;
    std::cin >> s;
    for (size_t j{}; j != m; ++j) {
      if (s[j] == 'o') {
        scores[i] += a[j];
      }
      else {
        remainders[i].push_back(j);
      }
    }
    std::ranges::sort(remainders[i], [&scores](auto lhs, auto rhs) {
      return scores[lhs] > scores[rhs];
    });
  }

  auto best{std::ranges::max(scores)};
  size_t i{};
  for (auto score: scores) {
    if (score == best) {
      std::cout << 0 << '\n';
      continue;
    }
    // if found lower
    size_t count{};
    for (auto&& remainder: remainders[i]) {
      score += a[remainder];
      ++count;
      if (score >= best) {
        break;
      }
    }
    std::cout << count << '\n';
    ++i;
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
