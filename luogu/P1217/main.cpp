#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

using ::std::size_t;

// constexpr bool debug{false};

template<typename T> T read()
{
  T tmp;
  std::cin >> tmp;
  return tmp;
}
template<typename value_t> class input_value {
public:
  input_value(): value_(read<value_t>()) {}
  input_value(const input_value&) = delete;
  input_value(input_value&&) = delete;
  input_value& operator=(const input_value&) = delete;
  input_value& operator=(input_value&&) = delete;
  ~input_value() = default;
  operator value_t&() { return value(); }
  value_t& value() { return value_; }
private:
  value_t value_;
};
template<size_t i, size_t j, typename value_type> using arr2
    = std::array<std::array<value_type, j>, i>;
template<size_t i, size_t j> using arr2uz = arr2<i, j, size_t>;
template<size_t i, size_t j> using arr2ll = arr2<i, j, long long>;
template<typename value_type> using vec2_impl
    = std::vector<std::vector<value_type>>;
template<typename value_t> class vec2 : public vec2_impl<value_t> {
public:
  vec2(size_t const i, size_t const j)
      : vec2_impl<value_t>(i, std::vector<value_t>(j, {}))
  {}
};
using vec2uz = vec2<size_t>;
using vec2ll = vec2<long long>;
template<typename T> concept is_pair = requires(T t) {
  t.first;
  t.second;
};
void print(auto&& t)
{
  if constexpr (std::ranges::range<decltype(t)>) {
    for (auto&& ele: t) {
      print(ele);
    }
    std::cout << '\n';
  }
  else if constexpr (is_pair<decltype(t)>) {
    std::cout << t.first << ": " << t.second << ", ";
  }
  else {
    std::cout << t << ' ';
  }
}
// bool is_prime(size_t const n)
// {
//   for (size_t i{2}; i != static_cast<size_t>(std::sqrt(n)) + 1; ++i) {
//     if (n % i == 0) {
//       return false;
//     }
//   }
//   return true;
// }

/* std::vector<size_t> */ auto generate_primes(size_t const n)
{
  std::vector<bool> is_prime_vec(n + 1, true);
  std::vector<size_t> primes;
  primes.reserve(2 * n / std::log(n));
  is_prime_vec[1] = false;
  for (size_t i{1}; i != n + 1; ++i) {
    if (is_prime_vec[i]) {
      primes.emplace_back(i);
    }
    for (auto const prime: primes) {
      if (i * prime > n) {
        break;
      }
      is_prime_vec[i * prime] = false;
      if (i % prime == 0) {
        break;
      }
    }
  }
  return is_prime_vec;
  // return primes;
}
bool is_palindrome(size_t const n)
{
  auto s{std::to_string(n)};
  for (size_t i{}; i != (s.size() + 1) / 2; ++i) {
    if (s[i] != s[s.size() - i - 1]) {
      return false;
    }
  }
  return true;
}
bool num_of_digits_test(size_t const n)
{
  if ((n >= 10 && n < 100 && n != 11) || (n >= 1000 && n < 10000)) {
    return false;
  }
  if ((n >= 100000 && n < 1000000) || (n >= 10000000 && n < 100000000)) {
    return false;
  }
  return true;
}
void solve_case()
{
  size_t a{};
  size_t b{};
  std::cin >> a >> b;
  b = std::min(9999999UZ, b);
  auto is_prime{generate_primes(b)};
  for (auto const num: std::ranges::views::iota(a, b + 1)) {
    if (num < a) {
      continue;
    }
    if (num > b) {
      break;
    }
    if (!num_of_digits_test(num)) {
      continue;
    }
    if (is_palindrome(num) && is_prime[num]) {
      // std::cout << prime << '\n';
      printf("%d\n", num);
    }
  }
}
int main()
{
  size_t n{1};
  // n = read<size_t>();
  for (size_t i{}; i != n; ++i) {
    solve_case();
  }
  return 0;
}
