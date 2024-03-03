#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#define int long long
using namespace std;
const int N = 1000005;
int n, m, a[N];
int ans[N], tag[N];

int ls(int p)
{
    return p << 1;
}
int rs(int p)
{
    return p << 1 | 1;
}
void push_up(int p)
{
    ans[p] = ans[ls(p)] + ans[rs(p)];
}
void build(int p, int l, int r)
{
    tag[p] = 0;
    if (l == r) {
        ans[p] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(ls(p), l, mid);
    build(rs(p), mid + 1, r);
    push_up(p);
}
void f(int p, int l, int r, int k)
{
    tag[p] += k;
    ans[p] += k * (r - l + 1);
}
void push_down(int p, int l, int r)
{
    int mid = (l + r) >> 1;
    f(ls(p), l, mid, tag[p]);
    f(rs(p), mid + 1, r, tag[p]);
    tag[p] = 0;
}
void update(int nl, int nr, int l, int r, int p, int k)
{
    if (nl <= l && nr >= r) {
        ans[p] += k * (r - l + 1);
        tag[p] += k;
        return;
    }
    push_down(p, l, r);
    int mid = (l + r) >> 1;
    if (nl <= mid)
        update(nl, nr, l, mid, ls(p), k);
    if (nr > mid)
        update(nl, nr, mid + 1, r, rs(p), k);
    push_up(p);
}
int query(int ql, int qr, int l, int r, int p)
{
    int res = 0;
    if (ql <= l && qr >= r)
        return ans[p];
    int mid = (l + r) >> 1;
    push_down(p, l, r);
    if (ql <= mid)
        res += query(ql, qr, l, mid, ls(p));
    if (qr > mid)
        res += query(ql, qr, mid + 1, r, rs(p));
    return res;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    build(1, 1, n);
    while (m--) {
        int op, x, y, k;
        cin >> op;
        if (op == 1) {
            cin >> x >> y >> k;
            update(x, y, 1, n, 1, k);
        }
        else {
            cin >> x >> y;
            int res = query(x, y, 1, n, 1);
            cout << res << endl;
        }
    }
    return 0;
}
