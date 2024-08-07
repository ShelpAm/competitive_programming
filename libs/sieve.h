#pragma once
#include "../templates/main.cpp"

class Sieve {
public:
  Sieve(int const upper_bound) : _min_factor(upper_bound + 1, 0)
  {
    for (int i = 2; i != upper_bound + 1; ++i) {
      if (_min_factor[i] == 0) {
        _primes.push_back(i);
        _min_factor[i] = i;
      }
      for (auto const p : _primes) {
        if (i * p > upper_bound || p > _min_factor[i]) {
          break;
        }
        _min_factor[i * p] = p;
      }
    }
  }

  // Time complexity: O(sqrt(x))
  [[nodiscard]] auto factorize(std::uint_fast64_t x) const
      -> std::map<std::uint_fast64_t, std::uint_fast64_t>
  {
    std::map<std::uint_fast64_t, std::uint_fast64_t> res;
    assert(x <= (_min_factor.size() - 1) * (_min_factor.size() - 1));
    for (auto const p : _primes) {
      if (p > x) {
        break;
      }
      while (x % p == 0) {
        x /= p;
        ++res[p];
      }
    }
    if (x >= _min_factor.size()) {
      ++res[x];
    }
    return res;
  }

  [[nodiscard]] auto is_prime(int x) const -> bool
  {
    return _min_factor[x] == x;
  }

  [[nodiscard]] auto primes() const -> std::vector<int> const &
  {
    return _primes;
  }

private:
  std::vector<int> _primes;
  std::vector<int> _min_factor;
};
