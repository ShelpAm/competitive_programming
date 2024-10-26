#pragma once

#include "../templates/main.cpp"

namespace shelpam {

template <std::int_fast64_t p> struct modint {
  modint() = default;
  modint(int const value) : value(value) {}
  modint(std::int_fast64_t const value) : value(value) {}
  modint(modint &&) = default;
  auto operator=(const modint &) -> modint & = default;
  auto operator=(modint &&) -> modint & = default;
  modint(modint const &) = default;
  ~modint() = default;
  operator std::int_fast64_t()
  {
    return value;
  }
  auto operator+=(modint other) -> modint &
  {
    (value += other.value) %= p;
    return *this;
  }
  auto operator+(modint other) const -> modint
  {
    return modint{*this} += other;
  }
  auto operator-=(modint other) -> modint &
  {
    (((value -= other.value) %= p) += p) %= p;
    return *this;
  }
  auto operator-(modint other) const -> modint
  {
    return modint{*this} -= other;
  }
  auto operator*=(modint other) -> modint &
  {
    (value *= other.value) %= p;
    return *this;
  }
  auto operator*(modint other) const -> modint
  {
    return modint{*this} *= other;
  }

  std::int_fast64_t value{};
};

using modint998244353 = modint<mod998244353>;
using modint1e9p7 = modint<mod1e9p7>;

template <std::int_fast64_t p>
auto operator>>(std::istream &is, modint<p> &x) -> std::istream &
{
  is >> x.value;
  return is;
}

template <std::int_fast64_t p>
auto operator<<(std::ostream &os, modint<p> x) -> std::ostream &
{
  os << x.value;
  return os;
}

} // namespace shelpam
