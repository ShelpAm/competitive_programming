#include <bits/stdc++.h>
using namespace std;
void solve()
{
  size_t n, z;
  cin >> n >> z;
  vector<vector<char>> v(n, vector<char>(n));
  for (auto&& e: v)
    for (auto&& i: e)
      cin >> i;
  if (n * z % 100 != 0) {
    cout << "error\n";
    return;
  }
  size_t new_size{n * z / 100};
  size_t g{gcd(new_size, n)};
  auto origin{n / g}, dest{new_size / g};
  vector<vector<char>> res(new_size, vector<char>(new_size));
  for (size_t i{}; i != g; ++i) {
    for (size_t j{}; j != g; ++j) {
      char standard{v[i][j]};
      for (size_t p{}; p != origin; ++p) {
        for (size_t q{}; q != origin; ++q) {
          if (v[i * origin + p][j * origin + q] != standard) {
            cout << "error\n";
            return;
          }
        }
      }
      for (size_t p{}; p != new_size; ++p) {
        for (size_t q{}; q != new_size; ++q) {
          res[i * new_size + p][j * new_size + q] = standard;
        }
      }
    }
  }

  for (size_t i{}; i != new_size; ++i) {
    for (size_t j{}; j != new_size; ++j) {
      cout << res[i][j];
    }
    cout << endl;
  }
}
int main()
{
  size_t T;
  cin >> T;
  while (T--) {
    solve();
  }
}
