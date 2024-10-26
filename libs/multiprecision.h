#pragma once
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

namespace shelpam::multiprecision {
// Only supports positive numbers.
template <int Base> class Multiprecision {
  friend constexpr auto operator<(Multiprecision const &lhs,
                                  Multiprecision const &rhs) -> bool
  {
    if (lhs._bits.size() != rhs._bits.size()) {
      return lhs._bits.size() < rhs._bits.size();
    }
    for (auto i{lhs._bits.size()}; i != 0; --i) {
      if (lhs._bits[i - 1] != rhs._bits[i - 1]) {
        return lhs._bits[i - 1] < rhs._bits[i - 1];
      }
    }
    return false;
  }

  friend constexpr auto operator==(Multiprecision const &lhs,
                                   Multiprecision const &rhs) -> bool
  {
    return lhs._bits == rhs._bits;
  }

  friend constexpr auto operator<=(Multiprecision const &lhs,
                                   Multiprecision const &rhs) -> bool
  {
    return lhs < rhs || lhs == rhs;
  }

  static constexpr auto max_base_for_string{10};

public:
  Multiprecision() : _bits{0} {}

  constexpr Multiprecision(std::string_view const s) : _bits(s.begin(), s.end())
  {
    std::reverse(_bits.begin(), _bits.end());
    for (auto &e : _bits) {
      e -= '0';
    }
  }

  constexpr Multiprecision(std::int_fast64_t n)
  {
    while (n != 0) {
      _bits.push_back(n % Base);
      n /= Base;
    }
    if (_bits.empty()) {
      _bits.push_back(0);
    }
  }

  auto operator+=(Multiprecision const &rhs) -> Multiprecision &
  {
    _bits.resize(std::max(_bits.size(), rhs._bits.size()) + 1);
    for (std::size_t i{}; i != rhs.size(); ++i) {
      _bits[i] += rhs._bits[i];
    }
    push_up();
    normalize();
    return *this;
  }

  auto operator-=(Multiprecision const &rhs) -> Multiprecision &
  {
    assert(rhs <= *this);
    for (std::size_t i{}; i != rhs.size(); ++i) {
      _bits[i] -= rhs._bits[i];
    }
    push_down();
    normalize();
    return *this;
  }

  auto operator*=(Multiprecision const &rhs) -> Multiprecision &
  {
    std::vector<int> result(size() + rhs.size() + 1);

    for (std::size_t i{}; i != size(); ++i) {
      for (std::size_t j{}; j != rhs.size(); ++j) {
        result[i + j] += _bits[i] * rhs._bits[j];
      }
    }

    _bits = std::move(result);
    push_up();

    normalize();
    return *this;
  }

  auto operator/=(Multiprecision const &rhs) -> Multiprecision &
  {
    std::vector<int> quotient(size());
    Multiprecision current;

    for (std::size_t i{_bits.size()}; i != 0; --i) {
      current._bits.insert(current._bits.begin(), _bits[i - 1]);
      current.normalize();
      while (rhs <= current) {
        current -= rhs;
        ++quotient[i - 1];
      }
    }

    _bits = std::move(quotient);
    normalize();
    return *this;
  }

  auto operator%=(Multiprecision const &rhs) -> Multiprecision &
  {
    std::vector<int> quotient(_bits.size());
    Multiprecision current;

    for (std::size_t i{_bits.size()}; i != 0; --i) {
      current._bits.insert(current._bits.begin(), _bits[i - 1]);
      current.normalize();
      while (rhs <= current) {
        current -= rhs;
        ++quotient[i - 1];
      }
    }

    return *this = std::move(current);
  }

  [[nodiscard]] auto size() const -> std::size_t
  {
    return _bits.size();
  }

  [[nodiscard]] auto to_string() const -> std::string
  {
    static_assert(Base <= max_base_for_string, "Only for 10 and lower");
    std::string s{_bits.begin(), _bits.end()};
    std::reverse(s.begin(), s.end());
    for (auto &e : s) {
      e += '0';
    }
    return s;
  }

private:
  // Buffered constructor
  Multiprecision(std::size_t const size, int const _) : _bits(size) {}

  void normalize()
  {
    while (!_bits.empty() && _bits.back() == 0) {
      _bits.pop_back();
    }
    if (_bits.empty()) {
      _bits.push_back(0);
    }
  }

  void push_up()
  {
    for (std::size_t i{}; i != size() - 1; ++i) {
      _bits[i + 1] += _bits[i] / Base;
      _bits[i] %= Base;
    }
  }

  void push_down()
  {
    for (std::size_t i{}; i != size() - 1; ++i) {
      _bits[i + 1] += (_bits[i] - Base + 1) / Base;
      _bits[i] = (_bits[i] % Base + Base) % Base;
    }
  }

  std::vector<int> _bits; // Stored by little-endian.
};

template <int Base>
[[nodiscard]] constexpr auto operator+(Multiprecision<Base> const &lhs,
                                       Multiprecision<Base> const &rhs)
    -> Multiprecision<Base>
{
  return Multiprecision{lhs} += rhs;
}

template <int Base>
[[nodiscard]] constexpr auto operator-(Multiprecision<Base> const &lhs,
                                       Multiprecision<Base> const &rhs)
    -> Multiprecision<Base>
{
  return Multiprecision{lhs} -= rhs;
}

template <int Base>
[[nodiscard]] constexpr auto operator*(Multiprecision<Base> const &lhs,
                                       Multiprecision<Base> const &rhs)
    -> Multiprecision<Base>
{
  return Multiprecision{lhs} *= rhs;
}

template <int Base>
[[nodiscard]] constexpr auto operator/(Multiprecision<Base> const &lhs,
                                       Multiprecision<Base> const &rhs)
    -> Multiprecision<Base>
{
  return Multiprecision{lhs} /= rhs;
}

template <int Base>
[[nodiscard]] constexpr auto operator%(Multiprecision<Base> const &lhs,
                                       Multiprecision<Base> const &rhs)
    -> Multiprecision<Base>
{
  return Multiprecision{lhs} %= rhs;
}

namespace details {
constexpr auto default_base{10};
}
using Int = Multiprecision<details::default_base>;
} // namespace shelpam::multiprecision
