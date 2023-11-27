#include <algorithm>
#include <array>
#include <bitset>
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
struct item {
  auto operator<=>(item const& other) const = default;
  size_t host;
  size_t price;
  size_t value;
};
// size_t count{};
size_t search(auto&& items, size_t const state, size_t const i,
              size_t const money_left)
{
  static unsigned int* note = new unsigned int[0x7fff'ffff];
  // if (++count >= 100) {
  //   exit(0);
  // }
  if (i == items.size()) {
    return 0;
  }
  std::cout << "Buying " << i << " with state: " << std::bitset<60>(state)
            << " leaving " << money_left << " money\n";
  if (note[state >> 31] != 0) {
    return note[state >> 31];
  }
  // 判断钱是否足够
  if (money_left < items[i].price) {
    return /* note[state >> 31] = */ search(items, state, i + 1, money_left);
  }
  // 判断是否因是附件而不能买
  if (items[i].host != 0 && (state >> (items[i].host - 1) & 1) == 0) {
    // The host wasn't bought.
    return /* note[state >> 31] = */ search(items, state, i + 1, money_left);
  }
  return note[state >> 31]
         = std::ranges::max(items[i].price * items[i].value
                                + search(items, state ^ (1 << i), i + 1,
                                         money_left - items[i].price),
                            search(items, state, i + 1, money_left));
}
void solve_case()
{
  size_t n{};
  size_t m{};
  std::cin >> n >> m;
  std::vector<item> items(m);
  for (size_t i{}; i != m; ++i) {
    std::cin >> items[i].price >> items[i].value >> items[i].host;
  }

  // std::ranges::sort(items);
  size_t total_price{};
  for (auto const& item: items) {
    total_price += item.price;
  }
  if (total_price <= n) {
    size_t ans{};
    for (auto const& item: items) {
      ans += item.price * item.value;
    }
    std::cout << ans;
    return;
  }

  std::cout << search(items, 0, 0, n);
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
