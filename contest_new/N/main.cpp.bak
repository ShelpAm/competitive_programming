#include <bit>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string_view>

using ::std::size_t;

// constexpr bool debug{false};

template<typename T> T read()
{
  T tmp;
  std::cin >> tmp;
  return tmp;
}

constexpr std::string_view yes{"Yes\n"};
constexpr std::string_view no{"No\n"};

bool pf(long long x, long long m)
{
  long long product{m};
  for (size_t i{}; i != 10000; ++i) {
    if (product == x) {
      return true;
    }
    if (product > x) {
      return false;
    }
    product *= m;
  }
}

void solve_case()
{
  long long n, m;
  scanf("%lld%lld", &n, &m);
  long long x;
  for (size_t i{}; i != n; ++i) {
    scanf("%lld", &x);
    if (m == 1) {
      if (x == 1) {
        printf(yes.data());
      }
      else {
        printf(no.data());
      }
    }
    else {
      printf(pf(x, m) ? yes.data() : no.data());
    }
  }
}
int main()
{
  solve_case();
  return 0;
}
