#pragma once
#include <cassert>
#include <cstdint>
#include <memory>
#include <vector>

namespace math {
namespace {
// The following are function-like-objects classes.

/// Time complexity:
/// - initialization: O(upper_bound)
/// - query:          O(1)
class Inverse {
public:
  /// @param
  /// upper_bound maximal number whose inverse can be queried.
  Inverse(int upper_bound, std::int_fast64_t const mod)
      : _inverse(upper_bound + 1), _factorial(upper_bound + 1),
        _prefix_inverse(upper_bound + 1), _upper_bound(upper_bound)
  {
    _inverse[0] = _inverse[1] = _factorial[0] = _factorial[1] =
        _prefix_inverse[0] = _prefix_inverse[1] = 1;
    for (std::int_fast64_t i{2}; i != upper_bound + 1; ++i) {
      _inverse[i] = (mod - mod / i) * _inverse[mod % i] % mod;
      _factorial[i] = _factorial[i - 1] * i % mod;
      _prefix_inverse[i] = _prefix_inverse[i - 1] * _inverse[i] % mod;
    }
  }
  auto operator()(int const n) const -> std::int_fast64_t
  {
    assert(n >= 0);
    assert(n <= _upper_bound);
    return _inverse[n];
  }
  [[nodiscard]] auto factorial(int const n) const -> std::int_fast64_t
  {
    assert(n >= 0);
    assert(n <= _upper_bound);
    return _factorial[n];
  }
  [[nodiscard]] auto prefix_inverse(int const n) const -> std::int_fast64_t
  {
    assert(n >= 0);
    assert(n <= _upper_bound);
    return _prefix_inverse[n];
  }
  [[nodiscard]] auto upper_bound() const -> std::int_fast64_t
  {
    return _upper_bound;
  }

private:
  std::vector<std::int_fast64_t> _inverse;
  std::vector<std::int_fast64_t> _factorial;
  std::vector<std::int_fast64_t> _prefix_inverse;
  std::int_fast64_t _upper_bound;
};

class Combination {
public:
  /// @param
  /// upper_bound max(n, m) in `c(n, m)`
  Combination(int const upper_bound, int const mod)
      : _inverse(std::make_shared<Inverse>(upper_bound, mod)), _mod(mod)
  {
  }
  auto operator()(int const n, int const m) -> std::int_fast64_t
  {
    assert(n >= 0);
    assert(n <= _inverse->upper_bound());
    if (n < m) {
      return 0;
    }
    return _inverse->factorial(n) * _inverse->prefix_inverse(m) % _mod *
           _inverse->prefix_inverse(n - m) % _mod;
  }

private:
  std::shared_ptr<Inverse> _inverse;
  std::int_fast64_t _mod;
};

class Arrangement {
public:
  /// @param
  /// upper_bound max(n, m) in `a(n, m)`
  Arrangement(int const upper_bound, int const mod)
      : _combination(std::make_shared<Combination>(upper_bound, mod))
  {
  }
  auto operator()(int const n, int const m) -> std::int_fast64_t
  {
    if (n < m) {
      return 0;
    }
    return _combination(n, m) * _combination->_inverse.factorial(n - m);
  }

private:
  std::shared_ptr<Combination> _combination;
};
class Comb {
public:
  auto arrangement(int const n, int const m) -> std::int_fast64_t
  {
    return _arrangement(n, m);
  }
  auto inverse(int const n) -> std::int_fast64_t
  {
    return _arrangement._combination._inverse(n);
  }
  auto combination(int const n, int const m)
  {
    return _arrangement._combination;
  }

private:
  Arrangement _arrangement;
};
} // namespace
} // namespace math
