#include <bits/stdc++.h>
using namespace std;
int main()
{
  unordered_map<char, string> mp{{'0', "零"}, {'1', "壹"}, {'2', "贰"}, {'3', "叁"}, {'4', "肆"},
                                 {'5', "伍"}, {'6', "陆"}, {'7', "柒"}, {'8', "捌"}, {'9', "玖"}};
  vector<string> name{"", "拾", "佰", "仟"};
  vector<string> block_name{"元", "万", "亿", "兆"};
  vector<string> float_name{"角", "分"};
  string_view zero{"零"};

  auto basic_convert{[&](string_view s) {
    string res;
    auto p{s.size()};
    queue<string> pending;
    for (size_t i{}; i != p; ++i) {
      auto bit{p - i - 1};
      if (s[i] == '0') {
        if (pending.empty()) {
          pending.emplace(zero);
        }
      }
      else {
        while (!pending.empty()) {
          res += pending.front();
          pending.pop();
        }
        res += mp[s[i]];
        res += name[bit];
      }
    }
    return res;
  }};

  string s;
  while (cin >> s) {
    while (!s.empty() && s.back() == '0') {
      s.pop_back();
    }
    string res;
    auto p{s.find('.')};
    if (p == string::npos) {
      p = s.size();
      s.push_back('.');
    }
    auto const blocks{p / 4};
    auto const remainder{p % 4};
    if (remainder != 0) {
      res += basic_convert(s.substr(0, remainder)) + block_name[blocks];
    }
    for (size_t i{blocks - 1}; i != -1; --i) {
      auto begin{(blocks - 1 - i) * 4 + remainder};
      res += basic_convert(s.substr(begin, 4)) + block_name[i];
    }
    if (p == s.size() - 1) {
      res += "整";
    }
    else {
      for (size_t i{p + 1}; i != s.size(); ++i) {
        res += mp[s[i]];
        if (s[i] != '0') {
          res += float_name[i - p - 1];
        }
      }
    }
    cout << res << '\n';
  }
}
