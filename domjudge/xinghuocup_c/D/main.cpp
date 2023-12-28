#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// configs
using ::std::size_t;
namespace impl {
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
void solve_case()
{
  size_t n{};
  std::cin >> n;
  std::array<size_t, 1000001> num{};
  std::priority_queue<size_t> q;
  for (size_t i{}; i != n; ++i) {
    size_t v{};
    std::cin >> v;
    ++num[v];
  }
  for (size_t i{}; i != num.size(); ++i) {
    if (num[i] != 0) {
      q.emplace(i);
    }
  }

  size_t ans{};
  for (size_t i{1}; i != n; ++i) {
    size_t x{};
    std::cin >> x;
    --num[x];
    while (num[q.top()] == 0) {
      q.pop();
    }
    ans += i * q.top();
  }
  std::cout << ans;
}
int main()
{
  impl::io_accelerator accelerator;
  solve_case();
  return 0;
}
