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

int main()
{
    auto replace_all = [&](string& s, string_view from, string_view to) {
        // return;
        auto p = s.find(from, 0);
        while (p != string::npos) {
            s.replace(p, from.size(), to);
            p = s.find(from, p);
        }
    };
    string charset = " !?',\"./\\;:[]{}()-_=+*&^%$#@`~|";

    u64 n;
    cin >> n;
    cin.ignore();
    for (u64 i = 0; i != n; ++i) {
        string s;
        getline(cin, s, '\n');
        cout << s << '\n';

        while (!s.empty() && s.back() == ' ') {
            s.pop_back();
        }
        auto first_not_space = s.find_first_not_of(' ');
        if (first_not_space != string::npos) {
            s = s.substr(first_not_space);
        }

        for (auto ch: charset) {
            replace_all(s, string{" "} + ch, string{ch});
        }
        for (auto& ch: s) {
            if (isalpha(ch) && ch != 'I') {
                ch = tolower(ch);
            }
            else if (ch == '?') {
                ch = '!';
            }
        }
        s = ' ' + s;
        vector<pair<string, string>> mp{{"i", "I"}, {"me", "you"}, {"I", "you"}, {"can you", "I can"}, {"could you", "I could"}};
        for (auto l: charset) {
            for (auto r: charset) {
                for (auto const& [from, to]: mp) {
                    replace_all(s, string{l} + from + r, string{l} + to + r);
                }
            }
        }
        s = s.substr(1);
        cout << "AI: " << s << '\n';
    }
}

