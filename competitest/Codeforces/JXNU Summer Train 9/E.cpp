#include <bits/stdc++.h>
template <typename T> constexpr auto count_leading_zeros(T const &i) -> int
{
  assert(i != 0);
  if constexpr (std::is_same_v<T, unsigned long long>) {
    return __builtin_clzll(i);
  }
  if constexpr (std::is_same_v<T, unsigned long>) {
    return __builtin_clzl(i);
  }
  if constexpr (std::is_same_v<T, unsigned int>) {
    return __builtin_clz(i);
  }
  /*static_assert(false, "Unsupported type");*/
  static_assert(!std::is_signed_v<T>,
                "msb is implemented based on unsigned integers");
  return -1; // Unreachable.
}
// i mustn't be 0
template <typename T> constexpr auto msb(T i) -> int
{
  return static_cast<int>(sizeof(T) * CHAR_BIT - 1 - count_leading_zeros(i));
}
int main()
{
  int t;
  std::cin >> t;
  while (t--) {
    int n, k;
    std::string s;
    std::cin >> n >> k >> s;
    auto const x{std::count(s.begin(), s.end(), '1')};
    bool found{};
    for (int i{}; i != k + 1; ++i) {
      auto d{x + i};
      while (d != 0 && msb(unsigned(d)) >= k) {
        d -= 1 << msb(unsigned(d));
      }
      if (__builtin_popcount(d) == i) {
        std::string t;
        while (d != 0) {
          t.push_back((d & 1) + '0');
          d >>= 1;
        }
        while (t.size() != k) {
          t.push_back('0');
        }
        std::reverse(t.begin(), t.end());
        std::cout << t << '\n';
        found = true;
        break;
      }
    }
    if (found) {
      continue;
    }
    std::cout << "None\n";
  }
}
