#include <algorithm>
#include <iostream>
#include <map>

using namespace std;
int main()
{
  size_t n{}, m{};
  cin >> n >> m;
  map<long long, long long> mp;
  map<long long, long long> s;
  for (size_t i{}; i != n; ++i) {
    long long x;
    long long c;
    cin >> x >> c;
    mp[x] += c;
  }

  for (long long sum{}; auto const& p: s) {
    sum += mp[p.first];
    s[p.first] = sum;
  }

  for (size_t i{}; i != m; ++i) {
    long long l, r;
    cin >> l >> r;
    cout << s.upper_bound(r)->second - s.lower_bound(l)->second << '\n';
  }
}
