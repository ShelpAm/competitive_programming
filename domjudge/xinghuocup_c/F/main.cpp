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
void solve_case()
{
  size_t T{};
  std::cin >> T;
  while (T--) {
    size_t n, m, s;
    std::cin >> n >> m >> s;
    size_t sn{s % (2 * n - 2)};
    size_t sm{s % (2 * m - 2)};
    auto f{[&](size_t const n, size_t const s) { return s < n ? s : 2 * n - 2 - s; }};
    std::cout << f(n, sn) << ' ' << f(m, sm) << '\n';
  }
}
int main()
{
  impl::io_accelerator accelerator;
  solve_case();
  return 0;
}
