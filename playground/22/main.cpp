#include <bits/stdc++.h>
using namespace std;
int main()
{
  vector<vector<size_t>> win(16, vector<size_t>(16));
  win[2] for (size_t i{1}; i != 16; ++i)
  {
    for (size_t j{1}; j != 16; ++j) {
      for (size_t k{1}; k < min(i / 3, j + 1); ++k) {
        win[i][j] |= win[i - 1][j - k];
      }
    }
    for (auto const t: win[i]) {
      cout << t << ' ';
    }
    cout << '\n';
  }
}
