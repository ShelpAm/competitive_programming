#include <bits/stdc++.h>
using namespace std;
int main()
{
  constexpr size_t n{6};
  constexpr size_t q{n * (1 << n)};
  cout << n << ' ' << q << '\n';
  for (size_t x{}; x != 1 << n; ++x) {
    for (size_t y{}; y != n; ++y) {
      cout << x << ' ' << y << '\n';
    }
  }
}
