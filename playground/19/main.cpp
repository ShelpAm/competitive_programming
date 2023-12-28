#include <iostream>
#include <vector>
using namespace std;
void solve_case()
{
  size_t n{};
  std::cin >> n;
  std::vector<size_t> a(n);
  for (auto&& e: a) {
    cin >> e;
  }

  for (size_t i{}, j{}; i != n; ++i) {
    j = i + 2;
    if (a[j] >= a[i]) {
      break;
    }
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
