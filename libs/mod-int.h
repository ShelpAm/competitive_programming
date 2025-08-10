#pragma once

#include "../templates/main.cpp"
#include <cstdint>

namespace shelpam {

// mod需与n互质，否则没有模逆。
constexpr std::int_least64_t modular_inverse(std::int_least64_t n,
                                             std::int_least64_t mod)
{
    return pow(n % mod, mod - 2, mod);
}

template <std::int_least64_t mod> class Mod_int {
    static_assert(mod > 0, "Modulus must be positive");

  public:
    constexpr Mod_int() : value_{} {}

    constexpr Mod_int(std::int_least64_t n) : value_{(n % mod + mod) % mod} {}

    constexpr Mod_int &operator+=(Mod_int rhs)
    {
        value_ += rhs.value_;
        if (value_ >= mod) {
            value_ -= mod;
        }
        return *this;
    }

    constexpr Mod_int &operator-=(Mod_int rhs)
    {
        value_ -= rhs.value_;
        if (value_ < 0) {
            value_ += mod;
        }
        return *this;
    }

    constexpr Mod_int &operator*=(Mod_int rhs)
    {
        value_ *= rhs.value_;
        value_ %= mod;
        return *this;
    }

    constexpr Mod_int &operator/=(Mod_int rhs)
    {
        value_ *= modular_inverse(rhs.value_, mod); // modular_inverse
        value_ %= mod;
        return *this;
    }

    friend constexpr Mod_int operator+(Mod_int lhs, Mod_int rhs)
    {
        return lhs += rhs;
    }

    friend constexpr Mod_int operator-(Mod_int lhs, Mod_int rhs)
    {
        return lhs -= rhs;
    }

    friend constexpr Mod_int operator*(Mod_int lhs, Mod_int rhs)
    {
        return lhs *= rhs;
    }

    friend constexpr Mod_int operator/(Mod_int lhs, Mod_int rhs)
    {
        return lhs /= rhs;
    }

    friend std::ostream &operator<<(std::ostream &os, Mod_int rhs)
    {
        return os << rhs.value_;
    }

    friend std::istream &operator>>(std::istream &is, Mod_int &rhs)
    {
        is >> rhs.value_;
        rhs.value_ %= mod;
        if (rhs.value_ < 0) {
            rhs.value_ += mod;
        }
        return is;
    }

    friend constexpr bool operator==(Mod_int lhs, Mod_int rhs)
    {
        return lhs.value_ == rhs.value_;
    }

    friend constexpr bool operator!=(Mod_int lhs, Mod_int rhs)
    {
        return !(lhs == rhs);
    }

  private:
    std::int_least64_t value_; // n_ is guarenteed to be normalized.
};

template <std::int_least64_t mod>
Mod_int<mod> pow(Mod_int<mod> base, std::int_least64_t exp)
{
    if (exp < 0) {
        exp = -exp;
        base = modular_inverse(base, exp);
    }
    Mod_int<mod> res{1};
    while (exp != 0) {
        if ((exp & 1) == 1) {
            res = res * base;
        }
        base = base * base;
        exp >>= 1;
    }
    return res;
}

} // namespace shelpam
