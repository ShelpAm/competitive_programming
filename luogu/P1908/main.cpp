#include <algorithm>
#include <iostream>
#include <vector>

using ::std::size_t;

void merge_sort(std::vector<size_t>& v, size_t const l, size_t const r,
                size_t& cnt)
{
  if (l >= r) {
    return;
  }
  size_t const m{(l + r) >> 1};
  merge_sort(v, l, m, cnt);
  merge_sort(v, m + 1, r, cnt);
  size_t i{l};
  size_t j{m + 1};
  size_t k{};
  static std::vector<size_t> tmp(5e5 + 3);
  while (i != m + 1 && j != r + 1) {
    tmp[k++] = v[i] <= v[j] ? v[i++] : (cnt += m - i + 1, v[j++]);
  }
  while (i != m + 1) {
    tmp[k++] = v[i++];
  }
  while (j != r + 1) {
    tmp[k++] = v[j++];
  }
  std::ranges::copy(tmp.begin(), tmp.begin() + k, v.begin() + l);
}
void solve_case()
{
  size_t n{};
  std::cin >> n;
  std::vector<size_t> v(n);
  for (size_t i{}; i != n; ++i) {
    std::cin >> v[i];
  }

  size_t cnt{};
  merge_sort(v, 0, v.size() - 1, cnt);
  std::cout << cnt;
}
int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // std::cout.tie(nullptr);

  size_t n{1};
  // std::cin >> n;
  for (size_t i{}; i != n; ++i) {
    solve_case();
  }
  return 0;
}
