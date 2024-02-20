#include <bits/stdc++.h>
using namespace std;
int main()
{
  int q;
  cin >> q;
  vector<pair<int, int>> const dir_list{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
  while (q--) {
    int n, m, h;
    cin >> n >> m >> h;
    vector<string> v(n, string(m, '\0'));
    for (auto& e: v)
      for (auto& w: e)
        cin >> w;

    pair<int, int> s{};
    for (int i = 0; i != n; ++i)
      for (int j = 0; j != m; ++j) {
        if (v[i][j] == 'S') {
          s = {i, j};
        }
      }

    vector<vector<bool>> vis(n, vector<bool>(m));
    auto bfs{[&](pair<int, int> const s) {
      queue<tuple<int, int, int>> q;
      q.push({s.first, s.second, 0});
      while (!q.empty()) {
        //         cout << q.size() << '\n';
        auto const [x, y, cost]{q.front()};
        q.pop();

        if (vis[x][y])
          continue;
        vis[x][y] = true;
        if (v[x][y] == 'T') {
          return true;
        }
        if (cost >= h) {
          cout << x << ' ' << y << ' ' << cost << '\n';
          continue;
        }

        vector<int> dirs;
        for (int i = 0; i != 4; ++i) {
          if (x + dir_list[i].first >= 0 && x + dir_list[i].first < n
              && y + dir_list[i].second >= 0 && y + dir_list[i].second < m)
            dirs.push_back(i);
        }
        sort(dirs.begin(), dirs.end(), [&](auto const d1, auto const d2) {
          return v[dir_list[d1].first][dir_list[d1].second]
                 < v[dir_list[d2].first][dir_list[d2].second];
        });
        for (auto const& i: dirs) {
          auto const& [dx, dy]{dir_list[i]};
          cout << x + dx << ' ' << y + dy << "FUCK" << v[x + dx][y + dy]
               << endl;
          q.push({x + dx, y + dy, cost + v[x + dx][y + dy] - '0'});
        }
      }
      return false;
    }};

    cout << (bfs(s) ? "Yes\n" : "No\n");
  }
}
