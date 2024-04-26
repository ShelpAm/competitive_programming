#include <bits/stdc++.h>

[[maybe_unused]] constexpr std::int_fast64_t gcd(std::int_fast64_t a,
                                                 std::int_fast64_t b) noexcept
{
  assert(a >= 0 && b >= 0);
  while (b != 0) {
    auto t = b;
    b = a % b;
    a = t;
  }
  return a;
}
[[maybe_unused]] constexpr std::int_fast64_t lcm(std::int_fast64_t a,
                                                 std::int_fast64_t b) noexcept
{
  return a * b / gcd(a, b);
}
