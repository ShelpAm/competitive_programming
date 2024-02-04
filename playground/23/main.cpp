#include <bits/stdc++.h>
using namespace std;
int main()
{
  string a, b;
  cin >> a >> b;
  if (a.size() < b.size()) {
    swap(a, b);
  }
  a += a;
  auto p = a.find(b);
  if (p == string::npos)
    cout << "false";
  else
    cout << "true";
}
