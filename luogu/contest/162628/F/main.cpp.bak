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
using u64 = ::std::uint_fast64_t;
using vu = ::std::vector<u64>;
using vvu = ::std::vector<vu>;

auto solve_case()
{
    u64 n;
    cin >> n;
    vu a(n);
    for (auto& e: a) {
        cin >> e;
    }
    std::vector<long double> p(n);
    for (auto& e: p) {
        cin >> e;
    }

    vvu adj(n);
    for (u64 i = 0; i != n - 1; ++i) {
        u64 t;
        cin >> t;
        adj[t - 1].push_back(i + 1);
    }
    priority_queue<std::tuple<long double, long double, u64>> q;
    q.push({p[0] * a[0], p[0], 0});
    vu order;
    while (!q.empty()) {
        auto const [_, poss, u] = q.top();
        q.pop();
        order.push_back(u);
        for (auto const v: adj[u]) {
            q.push({poss * p[v] * a[v], poss * p[v], v});
        }
    }
    long double ans = 0;
    long double m = 1;
    for (auto i: order) {
        ans += a[i] * (m *= p[i]);
    }
    return ans;
}

int main()
{
    cout.precision(16);
    cout << fixed;
    cout << solve_case() << '\n';
    return 0;
}
