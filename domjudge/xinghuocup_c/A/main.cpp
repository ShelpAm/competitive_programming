#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
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
auto solve_case()
{
  size_t n{};
  long long t{};
  long long k{};
  std::cin >> n >> t >> k;
  std::vector<long long> v(n);
  for (auto&& e: v) {
    std::cin >> e;
  }
  long long free{};
  for (auto const i: v) {
    if (t < i) {
      if (0 >= i - k) {
        std::cout << "NO\n";
        return;
      }
      free += (t - i - k + 1) / k;
    }
    else {
      free += (t - i) / k;
    }
  }
  std::cout << "YES\n";
}
int main()
{
  impl::io_accelerator accelerator;
  solve_case();
  return 0;
}
