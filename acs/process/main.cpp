#include <array>
#include <cstddef>
#include <fstream>
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
auto namelist_map(std::istream& is)
{
  std::map<std::string, std::string> mapping;

  std::string nickname;
  std::string real_name;
  std::string misc;
  std::set<std::string_view> misc_list{"管理员", "所有者", " 管理成员"};
  size_t state{0}; // 0 represents new person
  std::getline(is, nickname);
  while (!is.eof()) {
    if (state == 0) {
      // 这里的第一个nickname被上一次循环最后读掉了
      std::getline(is, nickname);
      std::getline(is, real_name);
      mapping.emplace(nickname, real_name);
      std::getline(is, misc);
      while (true) {
        if (!misc_list.contains(misc)) {
          break;
        }
      }
    }
  }

  return mapping;
}
void solve_case()
{
  std::ifstream ifs_namelist("namelist.txt");
  auto real_name_by_nickname{namelist_map(ifs_namelist)};

  std::fstream fs("input.txt");
  std::ofstream ofs("output.txt");
  std::string buf;
  std::string ranking;
  std::string name;
  std::string score;
  fs >> buf;
  while (!fs.eof()) {
    ranking = buf;
    fs >> name >> score;
    while (fs >> buf) {
      if (buf[0] == '#') {
        break;
      }
    }
    std::cout << ranking << ',' << name << ',' << real_name_by_nickname[name]
              << ',' << score << '\n';
  }
  print(real_name_by_nickname);
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
