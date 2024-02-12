#include <bits/stdc++.h>
using namespace std;
namespace impl {
  template<typename value_t> using vec2 = std::vector<std::vector<value_t>>;
  template<typename T> concept is_pair = requires(T t) {
    t.first;
    t.second;
  };
} // namespace impl
auto&& operator<<(auto&& os, auto&& t)
{
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      os << ele << ' ';
    }
    os << '\n';
  }
  else if constexpr (impl::is_pair<decltype(t)>) {
    os << t.first << ": " << t.second << ", ";
  }
  else {
    os << t << ' ';
  }
  return os;
}
size_t n;
size_t k;
void work(auto const& a, auto const& cmp)
{
  deque<long long> dq;
  auto push{[&](auto const x) {
    while (!dq.empty() && (cmp(x, dq.back()) || x == dq.back())) {
      dq.pop_back();
    }
    dq.push_back(x);
  }};
  auto pop{[&](auto const x) {
    if (x == dq.front()) {
      dq.pop_front();
    }
  }};

  for (size_t i{}; i != k; ++i) {
    push(a[i]);
  }

  vector<long long> ans;
  ans.reserve(n - k);
  ans.emplace_back(dq.front());
  for (size_t i{}, j{k}; j != n; ++i, ++j) {
    push(a[j]);
    pop(a[i]);
    ans.emplace_back(dq.front());
  }

  cout << ans;
}
int main()
{
  cin >> n >> k;

  vector<long long> a(n);
  for (size_t i{}; i != n; ++i) {
    cin >> a[i];
  }

  work(a, ranges::less());
  work(a, ranges::greater());
}
