#pragma once
#include <algorithm>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

template <int Base> class Multiprecision {
public:
  Multiprecision() : _bits{0} {}

  Multiprecision(std::string_view const s) : _bits(s.begin(), s.end())
  {
    std::reverse(_bits.begin(), _bits.end());
    for (auto &e : _bits) {
      e -= '0';
    }
  }

  Multiprecision(std::int_fast64_t n)
  {
    while (n != 0) {
      _bits.push_back(n % Base);
      n /= Base;
    }
  }

  auto operator+=(Multiprecision const &rhs) -> Multiprecision &
  {
    auto const sz{std::max(_bits.size(), rhs._bits.size()) + 1};
    _bits.resize(sz);
    for (int i{}; i != sz - 1; ++i) {
      _bits[i] += rhs._bits[i];
      _bits[i + 1] += _bits[i] / Base;
      _bits[i] %= Base;
    }
    trim_zero();
    return *this;
  }

  auto operator*=(Multiprecision const &rhs) -> Multiprecision &
  {
    auto const sz{_bits.size() * rhs._bits.size() + 1};
    Multiprecision result(sz, 0);
    for (int i{}; i != _bits.size(); ++i) {
      for (int j{}; j != rhs._bits.size(); ++j) {
        result._bits[i + j] += _bits[i] * rhs._bits[j];
      }
    }
    _bits = std::move(result._bits);
    for (int i{}; i != sz - 1; ++i) {
      _bits[i + 1] += _bits[i] / Base;
      _bits[i] %= Base;
    }
    trim_zero();
    return *this;
  }

  auto operator+(Multiprecision const &rhs) -> Multiprecision
  {
    return Multiprecision{*this} += rhs;
  }

  operator std::string() const
  {
    static_assert(Base <= 10, "Only for 10 and lower");
    std::string s{_bits.begin(), _bits.end()};
    std::reverse(s.begin(), s.end());
    for (auto &e : s) {
      e += '0';
    }
    return s;
  }

private:
  // Buffered constructor
  Multiprecision(int const size, int _) : _bits(size) {}

  void trim_zero()
  {
    while (!_bits.empty() && _bits.back() == 0) {
      _bits.pop_back();
    }
    if (_bits.empty()) {
      _bits.push_back(0);
    }
  }

  std::vector<int> _bits; // Stored by little-endian.
};

using Int = Multiprecision<10>;
