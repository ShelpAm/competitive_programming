#include <algorithm>
#include <array>
#include <cstddef>
#include <exception>
#include <iostream>
#include <memory>
#include <numeric>
#include <ranges>
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
struct segment_tree {
public:
  segment_tree(size_t const left_bound, size_t const right_bound)
      : left_bound(left_bound), right_bound(right_bound)
  {
    left = std::make_unique<segment_tree>(left_bound,
                                          (left_bound + right_bound) / 2);
    right = std::make_unique<segment_tree>((left_bound + right_bound) / 2,
                                           right_bound);
  }
  [[nodiscard]] bool contains(size_t const pos) const
  {
    return pos >= left_bound && pos < right_bound;
  }
  size_t& at(size_t const pos)
  {
    if (!contains(pos)) {
      throw std::exception{};
    }
    if (is_leaf()) {
      return max_value;
    }
    if (pos < left->right_bound) {
      return left->at(pos);
    }
    return right->at(pos);
  }
  size_t max(size_t const left_bound, size_t const right_bound) const
  {
    if (is_leaf()) {
      return max_value;
    }
    if (!contains(left_bound) || !contains(right_bound - 1)) {
      throw std::exception{};
    }
    auto related_to_left{left_bound < left->right_bound};
    auto related_to_right{right_bound > right->left_bound};
    if (related_to_left == related_to_right) {
      return std::ranges::max(left->max(left_bound, left->right_bound),
                              right->max(right->left_bound, right_bound));
    }
    if (related_to_left) {
      return left->max(left_bound, right_bound);
    }
    if (related_to_right) {
      return right->max(left_bound, right_bound);
    }
    // Never reaches here
    return 0;
  }
  void emplace(size_t const pos, size_t const val)
  {
    if (contains(pos)) {
      at(pos) = val;
    }
    // Remains coding
  }
private:
  void destroy();
  [[nodiscard]] bool is_leaf() const { return right_bound == left_bound + 1; }

  std::unique_ptr<segment_tree> left{};
  std::unique_ptr<segment_tree> right{};
  // bound's range: [l, r)
  size_t left_bound{};
  size_t right_bound{};
  size_t max_value{};
  size_t min_value{};
};
bool can_go_on(segment_tree& st, size_t beg, size_t end, long long m)
{
  for (size_t i{beg}; i != end; ++i) {
    st.emplace(i, st.at(i) + 1);
  }
  return st.max(beg, end) < m;
}
void solve_case()
{
  input_value<size_t> n;
  input_value<size_t> m;
  input_value<size_t> k;
  // std::vector<long long> d(n + 1);
  // size_t beg{}, end{};
  // for (size_t i{}; i != k; ++i) {
  //   std::cin >> beg >> end;
  //   if (can_go_on(d, beg, end, m)) {
  //     ++d[beg];
  //     --d[end];
  //     std::cout << "Ticket " << i + 1 << ": ACCEPT";
  //   }
  //   else {
  //     std::cout << "Ticket " << i + 1 << ": REJECT";
  //   }
  // }
  segment_tree st(0, n + 1);
  for (size_t i{}; i != k; ++i) {
    size_t beg{};
    size_t end{};
    std::cin >> beg >> end;
    if (can_go_on(st, beg, end, m)) {
      std::cout << "Ticket " << i + 1 << ": ACCEPT";
    }
    else {
      std::cout << "Ticket " << i + 1 << ": REJECT";
    }
  }
}
int main()
{
  auto n{1};
  // n = read<size_t>();
  for (size_t i{}; i != n; ++i) {
    solve_case();
  }
  return 0;
}
