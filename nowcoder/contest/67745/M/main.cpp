#include <iostream>
using namespace std;
int main()
{
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (auto& e: a)
      cin >> e;
    for (auto& e: b)
      cin >> e;

    if (n < 3) {
      cout << -1 << '\n';
      continue;
    }

    bool found{};
    for (int i{1}; i != n - 1; ++i) {
      if (a[i] == b[i]) {
        found = true;
        cout << 1 << '\n';
        break;
      }
    }
    if (!found) {
      cout << (n >= 4 ? 2 : -1) << '\n';
    }
  }
}
