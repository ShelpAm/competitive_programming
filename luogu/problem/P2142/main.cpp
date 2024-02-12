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

template<size_t base> class number_container_t {
  friend auto& operator>>(auto& istream,
                          number_container_t<base>& number_container)
  {
    std::string tmp;
    istream >> tmp;
    number_container = tmp;
    return istream;
  }
  friend auto& operator<<(auto& ostream,
                          number_container_t<base> const& number_container)
  {
    return ostream << number_container.to_string();
  }
public:
  number_container_t() = default;
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
    std::ranges::reverse(s);
    if (sign_ == -1) {
      s.emplace_back('-');
    }
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

  void trim()
  {
    while (digits_.size() != 1 && digits_.back() == 0) {
      digits_.pop_back();
    }
  }

  static char to_char(size_t const i)
  {
    return static_cast<char>(i + (i > 9 ? 'A' - 10 : '0'));
  }

  static size_t to_number(char const c)
  {
    return static_cast<size_t>(c - (c >= 'A' ? 'A' - 10 : '0'));
  }

  long long sign_{1};
  std::vector<size_t> digits_{0};
};
template<size_t base>
number_container_t<base> operator+(number_container_t<base> const& lhs,
                                   number_container_t<base> const& rhs)
{
  return number_container_t<base>{lhs} += rhs;
}
template<size_t base>
number_container_t<base> operator-(number_container_t<base> const& lhs,
                                   number_container_t<base> const& rhs)
{
  return number_container_t<base>{lhs} -= rhs;
}
template<size_t base>
number_container_t<base> operator-(number_container_t<base> const& lhs)
{
  return -1 * number_container_t<base>{lhs};
}
template<size_t base>
number_container_t<base> operator*(number_container_t<base> const& lhs,
                                   number_container_t<base> const& rhs)
{
  return number_container_t<base>{lhs} *= rhs;
}
template<size_t base>
number_container_t<base> operator/(number_container_t<base> const& lhs,
                                   number_container_t<base> const& rhs)
{
  return number_container_t<base>{lhs} /= rhs;
}
// template<size_t notation, size_t base> class high_accuracy_number;
// template<size_t notation, size_t base> high_accuracy_number<notation, base>
// trim(high_accuracy_number<notation, base> const& n);
// template<size_t notation, size_t base> class high_accuracy_number {
//   friend std::istream& operator>>(std::istream& istream,
//                                   high_accuracy_number& number);
//   friend std::ostream& operator<<(std::ostream& ostream,
//                                   high_accuracy_number const& number);
// public:
//   high_accuracy_number(): str_("0") {}
//   high_accuracy_number(size_t const i): str_(std::to_string(i)) {}
//   high_accuracy_number(std::string_view const& str): str_(str) {}
//   high_accuracy_number(high_accuracy_number const&) = default;
//   high_accuracy_number& operator=(high_accuracy_number const&) = default;
//   high_accuracy_number(high_accuracy_number&&) = delete;
//   high_accuracy_number& operator=(high_accuracy_number&&) = delete;
//   ~high_accuracy_number() = default;
//   high_accuracy_number operator+(high_accuracy_number const& other) const;
//   high_accuracy_number operator-(high_accuracy_number const& other) const;
//   high_accuracy_number operator*(high_accuracy_number const& other) const;
//   high_accuracy_number operator/(high_accuracy_number const& other) const;
//   high_accuracy_number& operator+=(high_accuracy_number const& other);
//   high_accuracy_number& operator-=(high_accuracy_number const& other);
//   high_accuracy_number& operator*=(high_accuracy_number const& other);
//   high_accuracy_number& operator/=(high_accuracy_number const& other);
//   auto operator<=>(high_accuracy_number const& other) const
//   {
//     auto ordering{str_.size() <=> other.str_.size()};
//     if (ordering == std::strong_ordering::equal) {
//       return str_ <=> other.str_;
//     }
//     return ordering;
//   }
//
//   [[nodiscard]] std::string const& number() const { return str_; }
//   [[nodiscard]] std::string& str() { return digits.to_vector(); }
//   void trim()
//   {
//     auto i{str_.find_first_not_of('0')};
//     str_ = i == std::string::npos ? "0" : str_.substr(i);
//   }
// private:
//   number_container_t<base> digits;
// };
// template<size_t notation, size_t base> high_accuracy_number<notation, base>
// trim(high_accuracy_number<notation, base> const& n)
// {
//   auto tmp{n};
//   tmp.trim();
//   return tmp;
// }
// size_t get(std::string_view const& s, size_t const i)
// {
//   if (i >= s.size()) {
//     return 0UZ;
//   }
//   return s[i] - '0';
// }
// template<size_t notation, size_t base> high_accuracy_number<notation, base>
// high_accuracy_add(std::string a, std::string b)
// {
//   std::ranges::reverse(a);
//   std::ranges::reverse(b);
//   auto size{std::ranges::max(a.size(), b.size())};
//   std::string s(size, ' ');
//   size_t push{0};
//   for (size_t i{0}; i != size; ++i) {
//     size_t sum{get(a, i) + get(b, i) + push};
//     if (sum >= 10) {
//       push = 1;
//       sum -= 10;
//     }
//     else {
//       push = 0;
//     }
//     s[i] = static_cast<char>(sum + '0');
//   }
//   if (push == 1) {
//     s.push_back('1');
//   }
//   std::ranges::reverse(s);
//   return high_accuracy_number<notation, base>{s};
// }
// template<size_t notation, size_t base> high_accuracy_number<notation, base>
// high_accuracy_subtract(std::string a, std::string b)
// {
//   // a must greater than or equal to b!
//   // assert(high_accuracy_number<notation, base>{a}
//   //        >= high_accuracy_number<notation, base>{b});
//
//   if (a == b) {
//     return high_accuracy_number<notation, base>{0};
//   }
//
//   std::ranges::reverse(a);
//   std::ranges::reverse(b);
//   std::string s(a.size(), ' ');
//   long long borrow{0};
//   for (size_t i{0}; i != a.size(); ++i) {
//     long long sub{static_cast<long long>(get(a, i))
//                   - static_cast<long long>(get(b, i)) - borrow};
//     if (sub < 0) {
//       borrow = 1;
//       sub += 10;
//     }
//     else {
//       borrow = 0;
//     }
//     s[i] = static_cast<char>(sub + '0');
//   }
//   // This is impossible if a strictly non-less than b.
//   // if (borrow == 1) {
//   //   s.push_back('1');
//   // }
//   high_accuracy_number<notation, base> result{s};
//   result.trim();
//   std::ranges::reverse(result.str());
//   return result;
// }
// template<size_t notation, size_t base> high_accuracy_number<notation, base>
// high_accuracy_multiply(std::string a, char const b)
// {
//   if (a == "0" || b == '0') {
//     return high_accuracy_number<notation, base>{"0"};
//   }
//   std::ranges::reverse(a);
//   std::string s(a.size(), ' ');
//   size_t push{};
//   for (size_t i{}; i != a.size(); ++i) {
//     size_t sum{get(a, i) * (b - '0') + push};
//     push = sum / 10;
//     sum %= 10;
//     s[i] = static_cast<char>(sum + '0');
//   }
//   if (push != 0) {
//     s.push_back(static_cast<char>(push + '0'));
//   }
//   std::ranges::reverse(s);
//   return high_accuracy_number<notation, base>{s};
// }
// template<size_t notation, size_t base> high_accuracy_number<notation, base>
// high_accuracy_multiply(std::string const& a, std::string b)
// {
//   // Make b.size() less than or equal to a.size(), so that function is
//   faster. if (a.size() < b.size()) {
//     return high_accuracy_multiply<notation, base>(b, a);
//   }
//
//   std::ranges::reverse(b);
//   std::vector<high_accuracy_number<notation, base>> numbers(b.size());
//   for (size_t i{}; i != b.size(); ++i) {
//     numbers[i]
//         = high_accuracy_multiply<notation, base>(a + std::string(i, '0'),
//         b[i]);
//   }
//   return std::accumulate(numbers.begin(), numbers.end(),
//                          high_accuracy_number<notation, base>("0"));
// }
// // Does some small division.
// template<size_t notation, size_t base>
// size_t high_accuracy_divide(std::string const& a, std::string const& b,
//                             int /* placeholder */)
// {
//   for (size_t i{1}; i != -1UZ; ++i) {
//     if (high_accuracy_number<notation, base>{b}
//             * high_accuracy_number<notation, base>{i}
//         > high_accuracy_number<notation, base>{a}) {
//       return i - 1;
//     }
//   }
//   // Normally, the program never reaches here.
//   return -1UZ;
// }
// template<size_t notation, size_t base> high_accuracy_number<notation, base>
// high_accuracy_divide(std::string const& a, std::string const& b)
// {
//   if (a.size() < b.size()) {
//     return high_accuracy_number<notation, base>{0};
//   }
//
//   std::string s;
//   auto j{b.size() - 1};
//   high_accuracy_number<notation, base> sub{a.substr(0, j)};
//   for (;;) {
//     while (true) {
//       if (j == a.size()) {
//         return high_accuracy_number<notation, base>{s};
//       }
//       sub.str() += a[j++];
//       if (sub >= high_accuracy_number<notation, base>{b}) {
//         break;
//       }
//       s.push_back('0');
//     }
//
//     auto t{high_accuracy_divide(sub.str(), b, 0)};
//     s.push_back(static_cast<char>(t + '0'));
//     sub = sub
//           - (high_accuracy_number<notation, base>{t}
//              * high_accuracy_number<notation, base>{b});
//   }
// }
// template<size_t notation, size_t base> high_accuracy_number<notation, base>
// high_accuracy_number<notation, base>::operator+(
//     high_accuracy_number<notation, base> const& other) const
// {
//   return high_accuracy_add<notation, base>(str_, other.str_);
// }
// template<size_t notation, size_t base> high_accuracy_number<notation, base>
// high_accuracy_number<notation, base>::operator-(
//     high_accuracy_number const& other) const
// {
//   return high_accuracy_subtract(str_, other.str_);
// }
// template<size_t notation, size_t base> high_accuracy_number<notation, base>
// high_accuracy_number<notation, base>::operator*(
//     high_accuracy_number const& other) const
// {
//   return high_accuracy_multiply(str_, other.str_);
// }
// template<size_t notation, size_t base> high_accuracy_number<notation, base>
// high_accuracy_number<notation, base>::operator/(
//     high_accuracy_number const& other) const
// {
//   return high_accuracy_divide(str_, other.str_);
// }
// template<size_t notation, size_t base> std::istream&
// operator>>(std::istream& istream, high_accuracy_number<notation, base>&
// number)
// {
//   istream >> number.str_;
//   return istream;
// }
// template<size_t notation, size_t base>
// std::ostream& operator<<(std::ostream& ostream,
//                          high_accuracy_number<notation, base> const& number)
// {
//   ostream << number.str_;
//   return ostream;
// }

// Tester
// int main()
// {
//   number_container_t<10> a;
//   number_container_t<10> b;
//   std::cin >> a >> b;
//   std::cout << "a + b = " << a + b << "\na - b = " << a - b
//             << "\na * b = " << a * b << "\na / b = " << a / b << '\n';
//   return 0;
// }
void solve_case()
{
  number_container_t<10> a;
  number_container_t<10> b;
  std::cin >> a >> b;
  auto sign{a >= b ? "" : "-"};
  std::cout << sign << (a > b ? a - b : b - a) << '\n';
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
