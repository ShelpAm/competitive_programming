#include <bits/stdc++.h>
using namespace std;
int main()
{
  size_t n, q;
  cin >> n >> q;
  vector<size_t> a(n + 1), s(n + 1);
  for (size_t i{}; i != n; ++i) {
    cin >> a[i + 1];
  }
  sort(a.begin() + 1, a.end());
  for (size_t i{1}; i != n + 1; ++i) {
    s[i] = s[i - 1] + a[i];
  }
  for (size_t i{}; i != q; ++i) {
    size_t x;
    cin >> x;
    size_t l{0}, r{n};
    while (l < r) {
      auto mid{(l + r + 1) / 2};
      if (a[mid] <= x) {
        l = mid;
      }
      else {
        r = mid - 1;
      }
    }
    cout << ((s[n] - 2 * s[l]) + (2 * l - n) * x) << '\n';
  }
  return 0;
}
