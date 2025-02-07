#pragma once
#include <cassert>
#include <cstdint>
#include <memory>
#include <vector>

namespace math {
// Time complexity:
// - initialization: O(upper_bound)
// - query:          O(1)
class Combinatorics {
  public:
    /// @param  upper_bound  Maximum number whose inverse can be queried.
    /// @param  mod          Modulos of the results.
    Combinatorics(int const upper_bound, std::int_least64_t const mod)
        : _inverse(upper_bound + 1), _factorial(upper_bound + 1),
          _prefix_inverse(upper_bound + 1), _upper_bound(upper_bound), _mod{mod}
    {
        _inverse[0] = _inverse[1] = _factorial[0] = _factorial[1] =
            _prefix_inverse[0] = _prefix_inverse[1] = 1;
        for (int i{2}; i != upper_bound + 1; ++i) {
            _inverse[i] = (mod - mod / i) * _inverse[mod % i] % mod;
            _factorial[i] = _factorial[i - 1] * i % mod;
            _prefix_inverse[i] = _prefix_inverse[i - 1] * _inverse[i] % mod;
        }
    }

    [[nodiscard]] std::int_least64_t inverse(int const n) const
    {
        return _inverse[n];
    }

    [[nodiscard]] std::int_least64_t factorial(int const n) const
    {
        assert(n >= 0);
        assert(n <= _upper_bound);
        return _factorial[n];
    }

    [[nodiscard]] std::int_least64_t prefix_inverse(int const n) const
    {
        assert(n >= 0);
        assert(n <= _upper_bound);
        return _prefix_inverse[n];
    }

    [[nodiscard]] std::int_least64_t combination(int const n, int const m) const
    {
        assert(n >= 0);
        assert(n <= _upper_bound);
        if (n < m) {
            return 0;
        }
        return _factorial[n] * _prefix_inverse[m] % _mod *
               _prefix_inverse[n - m] % _mod;
    }

    [[nodiscard]] std::int_least64_t arrangement(int const n, int const m) const
    {
        assert(n >= 0);
        assert(n <= _upper_bound);
        if (m < 0 || n < m) {
            return 0;
        }
        return _factorial[n] * _prefix_inverse[n - m] % _mod;
    }

  private:
    std::vector<std::int_least64_t> _inverse;
    std::vector<std::int_least64_t> _factorial;
    std::vector<std::int_least64_t> _prefix_inverse;
    int _upper_bound;
    std::int_least64_t _mod;
};

} // namespace math
