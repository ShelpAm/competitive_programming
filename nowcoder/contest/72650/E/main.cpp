#include <bits/stdc++.h>
using namespace std;
void print_time(size_t t)
{
  size_t s{t % 60};
  t /= 60;
  size_t m{t % 60};
  t /= 60;
  size_t h{t % 24};
  t /= 24;
  cout << setw(2) << h << ':' << setw(2) << ':' << setw(2) << s;
}
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  size_t n;
  cin >> n;
  priority_queue<pair<size_t, size_t>, vector<pair<size_t, size_t>>, less<>> q;
  while (n-- != 0) {
    size_t h, m, s;
    size_t h1, m1, s1;
    char c;
    cin >> h >> c >> m >> c >> s;
    cin >> c;
    cin >> h1 >> c >> m1 >> c >> s1;
    q.emplace(h * 3600 + m * 60 + s, h1 * 3600 + m1 * 60 + s1);
  }

  size_t last{0};
  while (!q.empty()) {
    auto& [l, r]{q.top()};
    q.pop();
    if (last < l) {
      print_time(last);
      cout << " - ";
      print_time(l);
      cout << '\n';
      last = r;
    }
  }
}
