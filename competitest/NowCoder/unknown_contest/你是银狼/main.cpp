#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1000006;
int a[N];
int b[N];
priority_queue<int> q;
signed main()
{
  int n, m, s;
  cin >> n >> m >> s;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  int cost = 0, hp = m, ans = 0, maxx = 0;
  for (int i = 1; i <= n; i++) {
    // cout<<i-1<<" "<<hp<<" "<<cost<<endl;
    cin >> b[i];
    if (b[i] == 2) {
      hp += a[i];
      ans++;
      continue;
    }
    if (b[i] == 1) {
      hp -= a[i];
      cost += a[i];
      ans++;
      q.push(a[i]);
    }
    if (b[i] == 3) {
      hp -= a[i];
      cost += a[i];
      ans++;
    }
    if (hp < 0 || cost > s) {
      maxx = max(maxx, ans - 1);
    }
    while (hp < 0 || cost > s) {
      ans--;
      if (!q.empty()) {
        int cep = q.top();
        hp += cep;
        cost -= cep;
        q.pop();
      }
      else {
        break;
      }
    }
  }
  // cout<<n<<" "<<hp<<" "<<cost<<endl;
  cout << max(maxx, ans);
  return 0;
}
