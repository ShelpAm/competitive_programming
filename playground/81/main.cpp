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

int main()
{
    u64 n, m;
    cin >> n >> m;
    vi pa(n);
    vvu adj(n);
    for (u64 i = 0; i != n; ++i) {
        cin >> pa[i];
        if (pa[i] != -1) {
            adj[pa[i]].push_back(i);
        }
    }

    vu dis(n);
    auto dfs = [&](auto self, u64 u, u64 d) -> void {
        dis[u] = d;
        for (auto v: adj[u]) {
            self(self, v, d + 1);
        }
    };
    dfs(dfs, 0, 0);

    vb vis(n);
    u64 ans = 0;
    vis[0] = true;
    for (u64 i = 0; i != m; ++i) {
        u64 x;
        cin >> x;
        --x;
        u64 d = 0;
        while (!vis[x]) {
            x = pa[x];
            ++d;
            vis[x] = true;
        }
        ans += d;
        cout << ans << '\n';
    }
}
