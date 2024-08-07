#pragma once

#include "../templates/main.cpp"

template <std::int_fast64_t p> struct modint {
  modint() = default;
  modint(int const value) : value(value) {}
  modint(std::int_fast64_t const value) : value(value) {}
  modint(modint &&) = default;
  modint &operator=(const modint &) = default;
  modint &operator=(modint &&) = default;
  modint(modint const &) = default;
  ~modint() = default;
  operator std::int_fast64_t()
  {
    return value;
  }
  modint &operator+=(modint const other)
  {
    (value += other.value) %= p;
    return *this;
  }
  modint operator+(modint const other) const
  {
    return modint{*this} += other;
  }
  modint &operator-=(modint const other)
  {
    (((value -= other.value) %= p) += p) %= p;
    return *this;
  }
  modint operator-(modint const other) const
  {
    return modint{*this} -= other;
  }
  modint &operator*=(modint const other)
  {
    (value *= other.value) %= p;
    return *this;
  }
  modint operator*(modint const other) const
  {
    return modint{*this} *= other;
  }

  std::int_fast64_t value{};
};
using modint998244353 = modint<mod<int>>;
using modint1e9 = modint<mod1e9>;
template <std::int_fast64_t p>
std::istream &operator>>(std::istream &is, modint<p> &x)
{
  is >> x.value;
  return is;
}
template <std::int_fast64_t p>
std::ostream &operator<<(std::ostream &os, modint<p> x)
{
  os << x.value;
  return os;
}
