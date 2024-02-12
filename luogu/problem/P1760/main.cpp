#include <algorithm>
#include <cassert>
#include <compare>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

using ::std::size_t;
class number_container_t;
number_container_t operator*(number_container_t const& lhs,
                             number_container_t const& rhs);

class number_container_t {
  friend auto& operator>>(auto& istream, number_container_t& number_container)
  {
    std::string tmp;
    istream >> tmp;
    number_container = tmp;
    return istream;
  }
  friend auto& operator<<(auto& ostream,
                          number_container_t const& number_container)
  {
    return ostream << number_container.to_string();
  }
public:
  number_container_t() = default;
  number_container_t(std::integral auto const num)
      : number_container_t(std::to_string(num))
  {}
  number_container_t(std::string const& s) { *this = s; }
  number_container_t& operator=(std::string s)
  {
    if (s.empty()) {
      return *this;
    }
    std::ranges::reverse(s);
    if (s.back() == '-') {
      s.pop_back();
      sign_ = -1;
    }
    digits_.clear();
    digits_.reserve(s.size());
    for (auto const c: s) {
      digits_.emplace_back(to_number(c));
    }
    trim();
    return *this;
  }
  auto operator<=>(number_container_t const& rhs)
  {
    auto size_order{size() <=> rhs.size()};
    if (size_order == std::strong_ordering::equal) {
      for (size_t i{size() - 1}; i != -1UZ; --i) {
        if (auto digit_order{digits_[i] <=> rhs[i]};
            digit_order != std::strong_ordering::equal) {
          return digit_order;
        }
      }
      return std::strong_ordering::equal;
    }
    return size_order;
  }
  number_container_t& operator+=(number_container_t const& rhs)
  {
    // Todo: remove this
    if (rhs.sign_ == -1 || sign_ == -1) {
      throw "Negetive number isn't supported.";
    }
    size_t new_size{std::ranges::max(size(), rhs.size())};
    digits_.resize(new_size);
    size_t tmp{};
    for (size_t i{}; i != new_size; ++i) {
      if (i < size()) {
        tmp += digits_[i];
      }
      if (i < rhs.size()) {
        tmp += rhs[i];
      }
      digits_[i] = tmp % base;
      tmp /= base;
    }
    if (tmp != 0) {
      digits_.emplace_back(tmp);
    }
    return *this;
  }
  number_container_t& operator-=(number_container_t const& rhs)
  {
    // Todo: remove this
    if (rhs.sign_ == -1 || sign_ == -1 || rhs > *this) {
      throw "Negetive number isn't supported.";
    }

    long long tmp{};
    for (size_t i{}; i != size(); ++i) {
      if (i < size()) {
        tmp += digits_[i];
      }
      if (i < rhs.size()) {
        tmp -= rhs[i];
      }
      if (tmp < 0) {
        tmp += base;
        digits_[i] = tmp % base;
        tmp = -1;
      }
      else {
        digits_[i] = tmp % base;
        tmp /= base;
      }
    }
    trim();
    return *this;
  }
  number_container_t& operator*=(number_container_t const& rhs)
  {
    auto new_size{size() * rhs.size()};
    // First calculate the result without pushing digits.
    std::vector<size_t> buf(new_size);
    for (size_t i{}; i != size(); ++i) {
      for (size_t j{}; j != rhs.size(); ++j) {
        buf[i + j] += digits_[i] * rhs[j];
      }
    }
    // Then we push digits.
    size_t tmp{};
    for (size_t i{}; i != new_size; ++i) {
      tmp += buf[i];
      buf[i] = tmp % base;
      tmp /= base;
    }
    if (tmp != 0) {
      buf.emplace_back(tmp);
    }
    digits_ = buf;
    sign_ *= rhs.sign_;
    trim();
    return *this;
  }
  [[deprecated]] number_container_t& operator/=(number_container_t const& rhs)
  {
    if (*this < rhs) {
      return *this = "0";
    }

    size_t tmp{};
    std::vector<size_t> buf(size());
    for (size_t i{size() - 1}; i != -1UZ; --i) {
      tmp *= base;
      tmp += digits_[i];
      // buf[i]=tmp/;
    }

    trim();
    return *this;
  }
  size_t& operator[](size_t const index) { return digits_[index]; }
  size_t operator[](size_t const index) const
  {
    return (*const_cast<number_container_t*>(this))[index];
  }
  [[nodiscard]] size_t size() const { return digits_.size(); }
  [[nodiscard]] std::vector<char> to_vector() const
  {
    std::vector<char> s;
    s.reserve(digits_.size());
    for (auto const digit: digits_) {
      s.emplace_back(to_char(digit));
    }
    if (sign_ == -1) {
      s.emplace_back('-');
    }
    std::ranges::reverse(s);
    return s;
  }
  [[nodiscard]] std::string to_string() const
  {
    std::string s;
    for (auto const c: to_vector()) {
      s += c;
    }
    return s;
  }
private:
  // [[nodiscard]] char sign_char() const { return sign == 1 ? '\0' : '-'; }
  void adjust_sign()
  {
    if (digits_.size() == 1 && digits_[0] == 0 && sign_ == -1) {
      sign_ = 1;
    }
  }
  void trim()
  {
    while (digits_.size() != 1 && digits_.back() == 0) {
      digits_.pop_back();
    }
    adjust_sign();
  }

  static char to_char(size_t const i)
  {
    return static_cast<char>(i + (i > 9 ? 'A' - 10 : '0'));
  }

  static size_t to_number(char const c)
  {
    return static_cast<size_t>(c - (c >= 'A' ? 'A' - 10 : '0'));
  }

  long long base{10};
  long long sign_{1};
  std::vector<size_t> digits_{0};
};

number_container_t operator+(number_container_t const& lhs,
                             number_container_t const& rhs)
{
  return number_container_t{lhs} += rhs;
}

number_container_t operator-(number_container_t const& lhs,
                             number_container_t const& rhs)
{
  return number_container_t{lhs} -= rhs;
}
number_container_t operator-(number_container_t const& rhs)
{
  return number_container_t{-1} * number_container_t{rhs};
}
number_container_t operator*(number_container_t const& lhs,
                             number_container_t const& rhs)
{
  return number_container_t{lhs} *= rhs;
}
number_container_t operator/(number_container_t const& lhs,
                             number_container_t const& rhs)
{
  return number_container_t{lhs} /= rhs;
}
void solve_case()
{
  size_t n{};
  std::cin >> n;
  number_container_t a(1);
  for (size_t i{}; i != n; ++i) {
    a *= 2;
  }
  a -= 1;
  std::cout << a;
}
int main()
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // std::cout.tie(nullptr);

  size_t n{1};
  // n = read<size_t>();
  for (size_t i{}; i != n; ++i) {
    solve_case();
  }
  return 0;
}
