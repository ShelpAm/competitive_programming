#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
using i64 = ::std::ptrdiff_t;
using u64 = ::std::size_t;
using vi = ::std::vector<i64>;
using vvi = ::std::vector<vi>;
using vvvi = ::std::vector<vvi>;
using vvvvi = ::std::vector<vvvi>;
using vu = ::std::vector<u64>;
using vvu = ::std::vector<vu>;
using vvvu = ::std::vector<vvu>;
using vvvvu = ::std::vector<vvvu>;
using vb = ::std::vector<bool>;
using vvb = ::std::vector<vb>;
using vc = std::vector<char>;
using vvc = std::vector<vc>;
using pii = ::std::pair<i64, i64>;
using puu = ::std::pair<u64, u64>;
using triplei = ::std::tuple<i64, i64, i64>;
using tripleu = ::std::tuple<u64, u64, u64>;
#include <sstream>

int main()
{
  u64 n, q;
  cin >> n >> q;
  vector<map<u64, u64>> to(n);
  for (u64 i = 0; i != n; ++i) {
    to[i][1e9] = i;
  }
  for (u64 i = 0; i != q; ++i) {
    char op;
    u64 x, xx, y;
    cin >> op >> x >> xx >> y;
    --x, --xx;
    if (op == 43) {
      // +
      to[x][y] = xx;
      to[xx][y] = x;
    }
    else {
      // -
      to[x].erase(y);
      to[xx].erase(y);
    }

    u64 sum{};
    for (u64 j = 0; j != n; ++j) {
      u64 y{};
      u64 t{j};
      vu path;
      while (y != 1e9) {
        auto [_, dest]{*to[t].upper_bound(y)};
        y = _;
        t = dest;
      }
      sum += (j + 1) * (t + 1);
      // cout << j + 1 << ' ' << t + 1 << ' ';
    }
    cout << sum << '\n';
  }
}
