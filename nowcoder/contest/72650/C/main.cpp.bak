#include <bits/stdc++.h>
using namespace std;
constexpr size_t mod{998244353};
int main()
{
  array<size_t, 1001> pow2{1};
  for (size_t i{1}; i != pow2.size(); ++i) {
    pow2[i] = pow2[i - 1] * 2;
  }

  size_t n, m;
  cin >> n >> m;
  vector<string> v(n, string(m + 1, '\0'));
  for (auto&& s: v) {
    for (size_t j{1}; j <= m; ++j) {
      cin >> s[j];
    }
  }

  vector<vector<size_t>> sum(n, vector<size_t>(m + 1));
  for (size_t i{}; i != n; ++i) {
    for (size_t j{1}; j <= n; ++j) {
      sum[i][j] = sum[i][j - 1] + static_cast<size_t>(v[i][j] == '7');
    }
  }

  size_t damage_sum{};
  for (size_t i{}; i != n; ++i) {
    for (size_t j{1}; j <= n; ++j) {
      size_t normal{pow2[sum[i].back() - sum[i][j]]}; // Used for case '4'
      switch (v[i][j]) {
      case '1':
        damage_sum += pow2[sum[i].back() - sum[i][j - 1]];
        break;
      case '2':
        damage_sum += 2 * pow2[sum[i].back() - sum[i][j - 1]];
        break;
      case '3':
        if (i != 0) {
          damage_sum += pow2[sum[i - 1].back() - sum[i - 1][j - 1]];
        }
        damage_sum += pow2[sum[i].back() - sum[i][j]];
        if (i != n - 1) {
          damage_sum += pow2[sum[i + 1].back() - sum[i - 1][j - 1]];
        }
        break;
      case '4':
        damage_sum += normal == 1 ? 1 : normal / 2;
        break;
      case '5':
        damage_sum += pow2[sum[i].back() - sum[i][j]];
        damage_sum += 2 * pow2[sum[i][j - 1]];
        break;
      case '6':
        damage_sum += 2 * pow2[sum[i].back() - sum[i][j - 1]];
        break;
      default:
        assert("ASSERT SHELPAM!");
      }
    }
  }
  cout << damage_sum;
}
