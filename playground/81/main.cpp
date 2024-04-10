#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
using i64 = ::std::ptrdiff_t;
using u64 = ::std::size_t;
using vi = ::std::vector<i64>;
using vvi = ::std::vector<vi>;
using vvvi = ::std::vector<vvi>;
using vvvvi = ::std::vector<vvvi>;
using vu = ::std::vector<u64>;
using vvu = ::std::vector<vu>;
using vvvu = ::std::vector<vvu>;
using vvvvu = ::std::vector<vvvu>;
using vb = ::std::vector<bool>;
using vvb = ::std::vector<vb>;
using vc = std::vector<char>;
using vvc = std::vector<vc>;
using pii = ::std::pair<i64, i64>;
using puu = ::std::pair<u64, u64>;
using triplei = ::std::tuple<i64, i64, i64>;
using tripleu = ::std::tuple<u64, u64, u64>;

constexpr u64 mod = 1e9 + 7;
constexpr u64 base = 101;
vu pow_base;
struct myhash {
    myhash(vu const& a): value(a.size() + 1)
    {
        for (u64 i = 0; i != a.size(); ++i) {
            value[i + 1] = (value[i] * base + a[i]) % mod;
        }
    }
    // starts from 1
    u64 query_range(u64 l, u64 r) { return value[r] - value[l - 1] * pow_base[r - l + 1]; }

    vu value;
};

int main()
{
    u64 N;
    cin >> N;
    pow_base.resize(N + 1, 1);
    for (u64 i = 1; i != pow_base.size(); ++i) {
        pow_base[i] = pow_base[i - 1] * base % mod;
    }
    vu h(N);
    for (auto& e: h) {
        cin >> e;
    }
    u64 M;
    cin >> M;
    map<u64, vu> begin_from;
    map<u64, vu> avail;
    vvu papers(M);
    u64 _i = 0;
    for (auto& paper: papers) {
        u64 K;
        cin >> K;
        paper.resize(K);
        for (auto& e: paper) {
            cin >> e;
        }
        begin_from[paper.front()].push_back(_i++);
        avail[paper.front()].push_back(avail[paper.front()].size());
    }
    myhash hash(h);
    vector<myhash> paper_hash;
    paper_hash.reserve(M);
    for (auto const& paper: papers) {
        paper_hash.push_back(paper);
    }

    vu ans;
    bool ok = false;
    vu cur;
    auto dfs = [&](auto self, u64 i) -> void {
        if (i == N) {
            ok = true;
            assert(cur.size() == N);
            ans = cur;
            return;
        }
        auto& can_use = avail[papers[i].front()];
        for (u64 j = 0; j != can_use.size(); ++j) {
            if (can_use[j] && paper_hash) {
                can_use[j] = false;
                cur.push_back(begin_from[papers[i].front()][j]);
                self(self, i + 1);
                if (ok) {
                    return;
                }
                cur.pop_back();
                can_use[j] = true;
            }
        }
    };
    dfs(dfs, 0);
    for (u64 i = 0; i != ans.size(); ++i) {
        cout << ans[i];
        if (i != ans.size() - 1) {
            cout << ' ';
        }
    }
}
