#include <bits/stdc++.h>
using namespace std;
#define ios ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#define debug(x) cerr << #x << ": " << x << '\n';
typedef long long ll;
const int mod = 1e9 + 7;
const int N = 2e5 + 10, M = 1e6 + 10;
#define y1 abcd
#define int long long
int a[N];
void solve() {
  int n, p, q, r, sum = 0, cnt = 0;
  cin >> n >> p >> q >> r;
  for (int i = 1; i <= n; i++)
    cin >> a[i], sum += a[i];
  for (int i = 1; i <= n; i++)
    if (a[i] < 0)
      cnt++;
  sort(a + 1, a + 1 + n);
  int ans = 0;
  if (sum >= 0) {
    cout << 0;
    return;
  }
  if (n == 1) {
    cout << abs(sum) * p;
    return;
  }
  for (int i = 1; i <= n; i++) {
    if (i == n && cnt == n) {
      ans += abs(sum) * p;
      break;
    }
    if (sum - a[i] >= 0) {
      ans += min(q, abs(sum) * p);
      break;
    } else {
      ans += min(q, abs(a[i]) * p);
      sum -= a[i];
    }
  }
  cout << ans;
}
/*

*/
signed main() {
  //    ios;
  //    int T;
  //    cin >> T;
  //    while(T--)
  solve();
  //    cout << fixed << setprecision(6) << ans << endl;
  return 0;
}
