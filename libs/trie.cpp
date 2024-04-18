#include <bits/stdc++.h>
using namespace std;

using u64 = ::std::uint_fast64_t;
using vu = ::std::vector<u64>;
using vvu = ::std::vector<vu>;

// TODO: to be implemented
class trie {
 public:
  [[nodiscard]] bool find(string_view s) const
  {
    u64 idx{};
    for (auto const c: s) {
      if (next_[idx][c] == -1UZ) {
        return false;
      }
      idx = next_[idx][c];
      cout << "next: " << idx << '\n';
    }
    return true;
  }
  void emplace(string_view s)
  {
    u64 idx{};
    for (auto const c: s) {
      if (next_[idx][c] == -1UZ) {
        next_.emplace_back(alphabet_size, -1);
        next_[idx][c] = next_.size() - 1;
      }
      idx = next_[idx][c];
    }
  }
 private:
  static constexpr u64 alphabet_size = 26;
  vvu next_{1, vu(alphabet_size, -1UZ)};
};
