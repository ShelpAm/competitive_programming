#include<bits/stdc++.h> 

using namespace std;

int main( )
{
    int n,k;cin>>n>>k;
    vector<vector<int>> a(n+1, vector<int>(n+1));
    for (int i{}; i!=n; ++i) {
        for (int j{}; j!=n; ++j) {
            cin >> a[i+1][j+1];
            a[i+1][j+1] += a[i][j+1] + a[i+1][j] - a[i][j];
        }
    }
    auto sum{[&](int u, int v, int x, int y) {
        return a[x][y] - a[x][v-1] - a[u-1][y] + a[u-1][v-1];
    }};
    auto check{[&](auto s) {
        cout << "FUCK" << (1<<(n-1));
        for (int mask{}; mask!=(1<<(n-1)); ++mask) {
            auto cnt{__builtin_popcount(mask)};
            cout << bitset<10>(mask) << ' ' << cnt << '\n';
            if (cnt > k) {
                continue;
            }
            vector<int> p;
            for (int i{}; i!=n-1; ++i) {
                if (mask & 1 << i) {
                    p.push_back(i+1);
                }
            }
            p.insert(p.begin(), 1);
            // for (auto e : p)cout<<e<< ' ';
            auto left{k - cnt};
            auto ok{[&] {
                int c{};
                int prevx{1};
                for (int i{1}; i!=n+1; ++i) {
                    for (int j{1}; j!=p.size(); ++j) {
                        auto t{sum(p[j-1], prevx, p[j], i)};
                        cout << "T is " << t << '\n';
                        if (t > s) {
                            ++c;
                            prevx = i;
                            break;
                        }
                    }
                }
                cout << "C is " << c << '\n';
                return c <= left;
            }};
            if (ok()) {
                return true;
            }
        }
        return false;
    }};
    int l{}, r{1000000};
    while (l < r) {
        auto mid{l + r >> 1};
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    cout << l;
    return 0;
}
