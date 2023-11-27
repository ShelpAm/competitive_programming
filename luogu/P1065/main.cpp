#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <map>
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
struct span {
  auto operator<=>(span const&) const = default;
  long long l{}, r{};
};
auto&& operator<<(auto&& is, span const& t)
{
  return is << t.l << ' ' << t.r;
}

void solve_case()
{
  size_t m{};
  size_t n{};
  std::cin >> m >> n;
  std::vector<size_t> orders(n * m);
  vec2uz machine_id_of_workpiece(n, m);
  vec2ll time_of_workpiece(n, m);
  std::cin >> orders >> machine_id_of_workpiece >> time_of_workpiece;
  std::ranges::for_each(orders, [](auto&& t) { --t; });
  std::ranges::for_each(machine_id_of_workpiece, [](auto&& t) {
    std::ranges::for_each(t, [](auto&& t) { --t; });
  });

  std::vector<std::set<span>> spans(m);
  std::vector<size_t> steps(n);
  std::vector<long long> latest_time_of_workpiece(n);
  for (auto&& s: spans) {
    s.emplace(0, 0);
  }

  auto insert{[&](size_t const machine_id, long long const duration,
                  long long& latest_time) {
    auto& spans_of_machine{spans[machine_id]};
    // left hand side ************************************************
    if (spans_of_machine.size() == 1) {
      // std::cout << "[left] latest is " << latest_time << ' '
      //           << "And latest_time is " << latest_time << '\n';
      spans_of_machine.emplace(latest_time + 1, latest_time + duration);
      latest_time += duration;
      return;
    }
    // middle ****************************************************
    for (auto it{std::ranges::next(spans_of_machine.begin())};
         it != spans_of_machine.end(); ++it) {
      if (auto latest{std::ranges::max(std::ranges::prev(it)->r, latest_time)};
          latest_time < latest + 1 && latest + duration < it->l) {
        // std::cout << "[middle] latest is " << latest << ' '
        //           << "And latest_time is " << latest_time << '\n';
        spans_of_machine.emplace(latest + 1, latest + duration);
        latest_time = latest + duration;
        return;
      }
    }
    // right hand side ************************************************
    auto latest{
        std::ranges::max(std::ranges::max(spans_of_machine).r, latest_time)};
    // std::cout << "[right] latest is " << latest << ' ' << "And latest_time is
    // "
    //           << latest_time << '\n';
    spans_of_machine.emplace(latest + 1, latest + duration);
    latest_time = latest + duration;
  }};

  for (auto workpiece: orders) {
    insert(machine_id_of_workpiece[workpiece][steps[workpiece]],
           time_of_workpiece[workpiece][steps[workpiece]],
           latest_time_of_workpiece[workpiece]);
    ++steps[workpiece];
  }

  // std::cout << "Here are the spans:\n";
  // print(spans);
  long long ans{};
  for (auto&& span: spans) {
    ans = std::ranges::max(ans, std::ranges::max(span).r);
  }
  std::cout << ans;
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
