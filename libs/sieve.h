#pragma once
#include "../templates/main.cpp"

struct Sieve {
  Sieve(std::size_t const upper_bound) : min_factor(upper_bound + 1, 0)
  {
    for (size_t i = 2; i != min_factor.size(); ++i) {
      if (min_factor[i] == 0) {
        primes.push_back(i);
        min_factor[i] = i;
      }
      for (auto const p : primes) {
        if (i * p > upper_bound || p > min_factor[i]) {
          break;
        }
        min_factor[i * p] = p;
      }
    }
  }

  // Time complexity: O(sqrt(x))
  [[nodiscard]] std::map<u64, u64> factorize(u64 x) const
  {
    std::map<u64, u64> res;
    assert(x <= (min_factor.size() - 1) * (min_factor.size() - 1));
    for (auto const p : primes) {
      if (p > x) {
        break;
      }
      while (x % p == 0) {
        x /= p;
        ++res[p];
      }
    }
    if (x >= min_factor.size()) {
      ++res[x];
    }
    return res;
  }

  vu primes;
  vu min_factor;
};
