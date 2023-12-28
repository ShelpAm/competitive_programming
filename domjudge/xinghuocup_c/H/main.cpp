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

using namespace std;

using LL = long long;

int qmi(int a, int k, int p)
{
  LL res = 1;
  while (k) {
    if (k & 1)
      res = (LL)res * a % p;
    k >>= 1;
    a = (LL)a * a % p;
  }
  return res;
}
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
    size_t n, k;
    std::cin >> n >> k;
    if (n == 2 * k) {
      cout << 2 << '\n';
    }
    else {
      cout << 1 << '\n';
    }
  }
}
int main()
{
  // impl::io_accelerator accelerator;

  // string s(4, '\0');
  // // vector<map<string, size_t>> num_str(s.size() + 1);
  // while (cin >> s) {
  //   vector<bool> v(s.size());
  //   for (size_t k{}; k != s.size() + 1; ++k) {
  //     cout << "k = " << k << ' ';
  //     ranges::fill_n(v.begin(), k, true);
  //     auto copy{v};
  //     vector<string> strings;
  //     do {
  //       string res;
  //       for (size_t i{}; i != copy.size(); ++i) {
  //         res += (s[i]) ^ copy[i];
  //       }
  //       strings.emplace_back(res);
  //       // ++num_str[k][res];
  //       ranges::next_permutation(copy);
  //     }
  //     while (copy != v);
  //     sort(strings.begin(), strings.end());
  //     for (auto const& s: strings) {
  //       cout << s << ' ';
  //     }
  //   }
  //   cout << endl;
  // }
  // // for (size_t k{}; k != s.size() + 1; ++k) {
  // //   cout << "FOR k as " << k << '\n';
  // //   for (auto const& [s, n]: num_str[k]) {
  // //     cout << s << " has shown up for " << n << " times\n";
  // //   }
  // // }
  // return 0;

  solve_case();
  return 0;
}
