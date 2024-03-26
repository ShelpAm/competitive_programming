#include <algorithm>
#include <cassert>
#include <climits>
#include <cstddef>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
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
using triplei = tuple<i64, i64, i64>;
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

u64 pow(u64 a, u64 b, u64 p)
{
    u64 res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % p;
        }
        a = a * a % b;
        b /= 2;
    }
    return res;
}
void solve()
{
    u64 t, a, m;
    cin >> t >> a >> m;
    auto d = gcd(a, m);
    a /= d;
    m /= d;
    if (a % m == 0) {
        cout << 0 << '\n';
    }
    else {
        u64 c = a;
        cout << ((c - t + m) % m + m) * pow(a, m - 2, m) % m << '\n';
    }
}
