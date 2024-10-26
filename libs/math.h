#include <bits/stdc++.h>

[[maybe_unused]] constexpr auto gcd(std::int_fast64_t a,
                                    std::int_fast64_t b) noexcept
    -> std::int_fast64_t
{
  assert(a >= 0 && b >= 0);
  while (b != 0) {
    auto t = b;
    b = a % b;
    a = t;
  }
  return a;
}
[[maybe_unused]] constexpr auto lcm(std::int_fast64_t a,
                                    std::int_fast64_t b) noexcept
    -> std::int_fast64_t
{
  return a * b / gcd(a, b);
}
