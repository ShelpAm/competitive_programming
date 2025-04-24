#pragma once

#include "../templates/main.cpp"
#include <cstdint>

constexpr std::int_least64_t modular_inverse(std::int_least64_t n,
                                             std::int_least64_t mod)
{
    return pow(n % mod, mod - 2, mod);
}

template <std::int_least64_t mod> class Z {
  public:
    constexpr Z() : value_{} {}

    constexpr Z(std::int_least64_t n) : value_{n} {}

    constexpr Z &operator+=(Z rhs)
    {
        value_ += rhs.value_;
        if (value_ >= mod) {
            value_ -= mod;
        }
        return *this;
    }

    constexpr Z &operator-=(Z rhs)
    {
        value_ -= rhs.value_;
        if (value_ < 0) {
            value_ += mod;
        }
        return *this;
    }

    constexpr Z &operator*=(Z rhs)
    {
        value_ *= rhs.value_;
        value_ %= mod;
        return *this;
    }

    constexpr Z &operator/=(Z rhs)
    {
        value_ *= modular_inverse(rhs.value_, mod); // modular_inverse
        value_ %= mod;
        return *this;
    }

    friend constexpr Z operator+(Z lhs, Z rhs)
    {
        return lhs += rhs;
    }

    friend constexpr Z operator-(Z lhs, Z rhs)
    {
        return lhs -= rhs;
    }

    friend constexpr Z operator*(Z lhs, Z rhs)
    {
        return lhs *= rhs;
    }

    friend constexpr Z operator/(Z lhs, Z rhs)
    {
        return lhs /= rhs;
    }

    friend std::ostream &operator<<(std::ostream &os, Z rhs)
    {
        return os << rhs.value_;
    }

    friend std::istream &operator>>(std::istream &is, Z rhs)
    {
        is >> rhs.value_;
        rhs.value_ %= mod;
        if (rhs.value_ < 0) {
            rhs.value_ += mod;
        }
        return is;
    }

  private:
    std::int_least64_t value_; // n_ is guarenteed to be normalized.
};
