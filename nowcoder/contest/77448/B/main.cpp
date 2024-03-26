#include <algorithm>
#include <climits>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using vi = vector<i64>;
using vvi = vector<vi>;
using pii = pair<i64, i64>;
constexpr i64 inf = 1e18;
void solve();
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i64 t = 1;
    cin >> t;
    for (i64 tc = 0; tc != t; ++tc) {
        solve();
    }
}

void solve()
{
    u64 n, x;
    cin >> n >> x;
    vi a(n);
    for (auto& e: a) {
        cin >> e;
    }

    // vi pref(n + 1);
    // for (u64 i = 1; i != n + 1; ++i) {
    //     pref[i] = pref[i - 1] + a[i - 1];
    // }

    u64 sum = 0;
    for (u64 i = 0, j = 0; j != n; ++j) {
        sum += a[j];
        while (sum > x) {
            sum -= a[i++];
        }
    }
}
