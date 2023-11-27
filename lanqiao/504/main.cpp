#include<bits/stdc++.h>
using namespace std;
int main()
{
  std::string s;
  std::cin >> s;
  std::vector<size_t> nums;
  for (char const c: s) {
    ++nums[c - 'a'];
  }
  size_t ans{};
  size_t idx{};
  size_t i{};
  for (size_t const num: nums) {
    if (num > ans) {
      ans = num;
      idx = i;
    }
    ++i;
  }
  std::cout << idx+'a' << '\n' << ans;
  return 0;
}
