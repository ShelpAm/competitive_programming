#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <string_view>
#include <unordered_map>
#include <vector>

// configs
using ::std::size_t;

size_t num_substrings(std::string_view const s, size_t const k)
{
  size_t ret{};
  std::unordered_map<char, size_t> num_char;
  size_t i{};
  size_t j{};
  size_t distinct_chars{};

  while (j != s.size()) {
    while (distinct_chars != k) {
      ++j;
      if (j == s.size()) {
        return ret;
      }
      if (++num_char[s[j]] == 1) {
        ++distinct_chars;
      }
    }
    while (num_char[s[i + 1]] != 1) {
      if (--num_char[s[i]] == 0) {
        --distinct_chars;
      }
      ++i;
      if (i == s.size()) {
        return ret;
      }
    }
    ret += i;
  }
  return ret;
}
void solve_case()
{
  std::string s;
  size_t k{};
  std::cin >> s >> k;
  std::cout << num_substrings(s, k) << '\n';
}
int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // std::cout.tie(nullptr);

  size_t t{1};
  std::cin >> t;
  for (size_t i{}; i != t; ++i) {
    solve_case();
  }
  return 0;
}
