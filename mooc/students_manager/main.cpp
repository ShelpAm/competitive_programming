#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <ranges>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// configs
using ::std::array;
using ::std::cin;
using ::std::cout;
using ::std::size_t;
template<typename value_type> using vec1 = ::std::vector<value_type>;
using ::std::string;
using ::std::string_view;
using ::std::ranges::max;
using ::std::ranges::min;
using ::std::ranges::sort;
using namespace ::std::string_view_literals;

namespace impl {
  template<typename value_t> using vec2 = std::vector<std::vector<value_t>>;
  template<typename T> concept is_pair = requires(T t) {
    t.first;
    t.second;
  };
  class io_accelerator {
  public:
    io_accelerator()
    {
      std::ios::sync_with_stdio(false);
      std::cin.tie(nullptr);
      // The following line needn't to be executed because the above line actually had done this.
      // std::cout.tie(nullptr);
    }
    io_accelerator(const io_accelerator&) = delete;
    io_accelerator(io_accelerator&&) = delete;
    io_accelerator& operator=(const io_accelerator&) = delete;
    io_accelerator& operator=(io_accelerator&&) = delete;
    ~io_accelerator()
    {
      std::ios::sync_with_stdio(true);
      std::cin.tie(&std::cout);
    }
  };
} // namespace impl
template<size_t i, size_t j, typename value_t> using arr2 = std::array<std::array<value_t, j>, i>;
template<size_t i, size_t j> using arr2uz = arr2<i, j, size_t>;
template<size_t i, size_t j> using arr2ll = arr2<i, j, long long>;
template<typename value_t> class vec2 : public impl::vec2<value_t> {
public:
  vec2(size_t const i, size_t const j, value_t const& value = {})
      : impl::vec2<value_t>(i, std::vector<value_t>(j, value))
  {}
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
void print(auto const& t)
{
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      print(ele);
    }
    std::cout << '\n';
  }
  else if constexpr (impl::is_pair<decltype(t)>) {
    std::cout << t.first << ": " << t.second << ',';
  }
  else {
    std::cout << t << ' ';
  }
}
void debug([[maybe_unused]] std::string_view const& sv, [[maybe_unused]] auto&& t)
{
#ifdef DEBUG
  std::cout << sv << ": ";
  print(t);
  std::cout << '\n';
#endif
}
class student {
public:
  student(size_t const id, string_view const name, size_t const score)
      : id_{id}, name_{name}, score_{score}
  {}
  student(student const&) = default;
  student(student&&) = delete;
  student& operator=(const student&) = default;
  student& operator=(student&&) = delete;
  ~student() = default;
  [[nodiscard]] auto id() const { return id_; }
  [[nodiscard]] auto name() const { return name_; }
  [[nodiscard]] auto score() const { return score_; }
private:
  size_t id_{};
  string name_;
  size_t score_{};
};
std::ostream& operator<<(std::ostream& os, student const& s)
{
  return os << std::setw(3) << s.id() << ' ' << s.name() << string(50 - s.name().size(), ' ')
            << std::setw(3) << s.score();
}
class myclass {
public:
  void add(student const& st)
  {
    students_by_id_.emplace(st.id(), st);
    students_by_score_.emplace(st.score(), st);
  }
  student* fetch_by_id(size_t const id)
  {
    if (students_by_id_.contains(id)) {
      return &students_by_id_.at(id);
    }
    return nullptr;
  }
  student* fetch_by_score(size_t const score)
  {
    if (students_by_score_.contains(score)) {
      return &students_by_score_.at(score);
    }
    return nullptr;
  }
  auto& by_id() { return students_by_id_; }
  auto& by_score() { return students_by_score_; }
private:
  std::map<size_t, student> students_by_id_;
  std::map<size_t, student, std::ranges::greater> students_by_score_;
};
auto solve_case()
{
  myclass cla;
  size_t num_students{};
  cout << "Input the number of students: ";
  cin >> num_students;
  cout << "Please input every student by the order of id, name, score (Keep a space between each "
          "datum)\n";
  for (size_t i{}; i != num_students; ++i) {
    size_t id{};
    string name;
    size_t score{};
    cin >> id >> name >> score;
    cla.add(student{id, name, score});
  }
  cout << "Sorted by score:\n";
  cout << " id  " << string(22, ' ') << "name" << string(22, ' ') << "score\n";
  for (auto const& [id, s]: cla.by_score()) {
    cout << s << '\n';
  }
  cout << '\n';
  cout << "Sorted by id:\n";
  cout << " id  " << string(22, ' ') << "name" << string(22, ' ') << "score\n";
  for (auto const& [id, s]: cla.by_id()) {
    cout << s << '\n';
  }
}
void solve_all_cases(auto&& solve_case_f)
{
  size_t t{1};
  // std::cin >> t;
  for (size_t i{}; i != t; ++i) {
    if constexpr (std::is_same_v<decltype(solve_case_f()), void>) {
      solve_case_f();
    }
    else {
      print(solve_case_f());
    }
  }
}
int main()
{
  impl::io_accelerator accelerator;
  solve_all_cases(solve_case);
  return 0;
}
