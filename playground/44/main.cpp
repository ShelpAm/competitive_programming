#include <cassert>
#include <iostream>
#include <map>
#include <vector>
struct Sieve {
  std::vector<int> min_factor;
  std::vector<int> primes;
  Sieve(int MAXN): min_factor(MAXN + 1)
  {
    for (int d = 2; d <= MAXN; d++) {
      if (!min_factor[d]) {
        min_factor[d] = d;
        primes.emplace_back(d);
      }
      for (const auto& p: primes) {
        if (p > min_factor[d] or d * p > MAXN)
          break;
        min_factor[d * p] = p;
      }
    }
  }
  // Prime factorization for 1 <= x <= MAXN^2
  // Complexity: O(log x)           (x <= MAXN)
  //             O(MAXN / log MAXN) (MAXN < x <= MAXN^2)
  template<class T> std::map<T, int> factorize(T x) const
  {
    std::map<T, int> ret;
    assert(x > 0
           and x <= ((long long)min_factor.size() - 1)
                        * ((long long)min_factor.size() - 1));
    for (const auto& p: primes) {
      if (x < T(min_factor.size())) {
        // std::cout << "x is " << x << " and x < T(min_factor.size())\n";
        break;
      }
      while (!(x % p))
        x /= p, ret[p]++;
      // std::cout << "After divided by " << p << ", x is " << x << '\n';
    }
    if (x >= T(min_factor.size()))
      ret[x]++, x = 1;
    while (x > 1) {
      // std::cout << "min_factor[" << x << "]: " << min_factor[x] << '\n';
      ret[min_factor[x]]++, x /= min_factor[x];
    }
    return ret;
  }
  // Enumerate divisors of 1 <= x <= MAXN^2
  // Be careful of highly composite numbers https://oeis.org/A002182/list
  // https://gist.github.com/dario2994/fb4713f252ca86c1254d#file-list-txt (n, (#
  // of div. of n)): 45360->100, 735134400(<1e9)->1344,
  // 963761198400(<1e12)->6720
  template<class T> std::vector<T> divisors(T x) const
  {
    std::vector<T> ret{1};
    for (const auto p: factorize(x)) {
      int n = ret.size();
      for (int i = 0; i < n; i++) {
        for (T a = 1, d = 1; d <= p.second; d++) {
          a *= p.first;
          ret.push_back(ret[i] * a);
        }
      }
    }
    return ret; // NOT sorted
  }
  // Euler phi functions of divisors of given x
  // Verified: ABC212 G https://atcoder.jp/contests/abc212/tasks/abc212_g
  // Complexity: O(sqrt(x) + d(x))
  template<class T> std::map<T, T> euler_of_divisors(T x) const
  {
    assert(x >= 1);
    std::map<T, T> ret;
    ret[1] = 1;
    std::vector<T> divs{1};
    for (auto p: factorize(x)) {
      int n = ret.size();
      for (int i = 0; i < n; i++) {
        ret[divs[i] * p.first] = ret[divs[i]] * (p.first - 1);
        divs.push_back(divs[i] * p.first);
        for (T a = divs[i] * p.first, d = 1; d < p.second; a *= p.first, d++) {
          ret[a * p.first] = ret[a] * p.first;
          divs.push_back(a * p.first);
        }
      }
    }
    return ret;
  }
  // Moebius function Table, (-1)^{# of different prime factors} for square-free
  // x return: [0=>0, 1=>1, 2=>-1, 3=>-1, 4=>0, 5=>-1, 6=>1, 7=>-1, 8=>0, ...]
  // https://oeis.org/A008683
  std::vector<int> GenerateMoebiusFunctionTable() const
  {
    std::vector<int> ret(min_factor.size());
    for (unsigned i = 1; i < min_factor.size(); i++) {
      if (i == 1) {
        ret[i] = 1;
      }
      else if ((i / min_factor[i]) % min_factor[i] == 0) {
        ret[i] = 0;
      }
      else {
        ret[i] = -ret[i / min_factor[i]];
      }
    }
    return ret;
  }
  // Calculate [0^K, 1^K, ..., nmax^K] in O(nmax)
  // Note: **0^0 == 1**
  template<class MODINT>
  std::vector<MODINT> enumerate_kth_pows(long long K, int nmax) const
  {
    assert(nmax < int(min_factor.size()));
    assert(K >= 0);
    if (K == 0)
      return std::vector<MODINT>(nmax + 1, 1);
    std::vector<MODINT> ret(nmax + 1);
    ret[0] = 0, ret[1] = 1;
    for (int n = 2; n <= nmax; n++) {
      if (min_factor[n] == n) {
        ret[n] = MODINT(n).pow(K);
      }
      else {
        ret[n] = ret[n / min_factor[n]] * ret[min_factor[n]];
      }
    }
    return ret;
  }
};
Sieve sieve(1e7);
int main()
{
  for (auto const& [p, n]: sieve.factorize(static_cast<long long>(1e14))) {
    std::cout << p << ' ' << n << '\n';
  }
  return 0;
}
