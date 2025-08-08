#include <bits/stdc++.h>
using namespace std;
#define Endl "\n"
#define INF 0x3f3f3f3f
#define PI 3.14159265358979323846 // 20f
const int MOD = 998244353;
// const int MOD = 1e9 + 7;
typedef long long ll;
typedef unsigned long long ull;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
#define int ll

void work()
{
    int n, m, k, w;
    // cout << "S";
    cin >> n >> m >> k >> w;
    vector<int> black(m + 20);
    vector<int> red(n + 10);
    for (int i = 1; i <= n; i++)
        cin >> red[i];
    for (int i = 1; i <= m; i++)
        cin >> black[i];
    sort(red.begin() + 1, red.begin() + n + 1);
    sort(black.begin() + 1, black.begin() + m + 1);
    // pre
    vector<int> l, r;
    vector<vector<int>> duan;
    int j = 1;
    black[0] = 0, black[m + 1] = w + 1;
    for (int i = 0; i <= m; i++) {
        // cout << i << " " << black[i] << "\n";
        if (red[j] > black[i] && red[j] < black[i + 1]) {
            vector<int> ces;
            l.push_back(black[i] + 1);
            r.push_back(black[i + 1] - 1);
            while (j <= n && red[j] > black[i] && red[j] < black[i + 1]) {
                ces.push_back(red[j]);
                j++;
            }
            duan.push_back(ces);
        }
        else {
            continue;
        }
    }

    int siz = l.size();
    cout << "qujian(num): " << siz << '\n';
    vector<int> ans;
    for (int j = 0; j < siz; j++) {
        int zuo = l[j], you = r[j];
        auto vec = duan[j];
        int num = 0;
        int nl, nr;
        vector<int> fangl, fangr;
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i] > nr) {
                num++;
                fangl.push_back(nl);
                fangr.push_back(nr);
                nl = vec[i];
                nr = vec[i] + k - 1;
            }
            else {
                continue;
            }
        }
        if (nr > you) {
            fangr[fangr.size() - 1] = you;
            fangl[fangl.size() - 1] = you - k + 1;
            // cout << fangl.size() << " and " << fangr.size() << "\n";
            // for (int i = fangl.size() - 2; i >= 0; i--) {
            //   if (fangl[i + 1] <= fangr[i]) {
            //     fangr[i] = fangl[i + 1] - 1;
            //     fangl[i] = fangr[i] - k + 1;
            //   } else {
            //     break;
            //   }
            // }
            if (fangl[0] < zuo) {
                cout << -1 << '\n';
                return;
            }
        }
        for (int i = 0; i < fangl.size(); i++) {
            ans.push_back(fangl[i]);
        }
    }
    cout << ans.size() << '\n';
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i] << " ";
    cout << '\n';
}
#undef int
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    // cout << fixed << setprecision(2);
    int T = 1;
    cin >> T;
    while (T--) {
        work();
    }
}
