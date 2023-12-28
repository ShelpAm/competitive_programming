#include <bits/stdc++.h>
using namespace std;
int main()
{
  size_t T;
  cin >> T;
  while (T--) {
    size_t x, y;
    string s;
    cin >> x >> s >> y;
    if (s == "KB") {
      x *= 1024;
    }
    else if (s == "MB") {
      x *= 1024 * 1024;
    }
    else if (s == "GB") {
      x *= 1024 * 1024 * 1024;
    }
    cout << x / y << endl;
  }
  return 0;
}
