/*Problem: I. Container Scheduling*/
/*Contest: The 2024 Sichuan Provincial Collegiate Programming Contest*/
/*Judge: Codeforces*/
/*URL: https://codeforces.com/gym/105222/problem/I*/
/*Start: Mon 28 Oct 2024 08:59:11 PM CST*/
/*Author: ShelpAm*/

// #include <bits/stdc++.h>
#include <algorithm>
#include <bit>
#include <bitset>
#include <cassert>
#include <chrono>
#include <climits>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numbers>
#include <numeric>
#include <queue>
#include <random>
#include <ranges>
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace {
[[maybe_unused]] constexpr std::uint_fast64_t mod998244353{998'244'353ULL};
[[maybe_unused]] constexpr std::uint_fast64_t mod1e9p7{1'000'000'007ULL};
[[maybe_unused]] constexpr double eps{1e-8};
template <typename T> constexpr T inf{std::numeric_limits<T>::max() / 4};
template <typename T> constexpr T max{std::numeric_limits<T>::max()};

// Concepts.
namespace shelpam::concepts {
template <typename> struct is_pair_t : std::false_type {};
template <typename T, typename U>
struct is_pair_t<std::pair<T, U>> : std::true_type {};
template <typename T>
concept pair = is_pair_t<T>::value;
template <typename> struct is_tuple_t : std::false_type {};
template <typename... Ts>
struct is_tuple_t<std::tuple<Ts...>> : std::true_type {};
template <typename... Ts>
concept tuple = is_tuple_t<Ts...>::value;
} // namespace shelpam::concepts

auto operator>>(auto &istream, auto &&t) -> decltype(istream)
{
  using T = std::remove_cvref_t<decltype(t)>;
  static_assert(!shelpam::concepts::tuple<T>, "tuple: not implemented yet.\n");
  if constexpr (std::ranges::range<T>) {
    for (auto &ele : t) {
      istream >> ele;
    }
  }
  else if constexpr (shelpam::concepts::pair<T>) {
    istream >> t.first >> t.second;
  }
  else {
    istream >> t;
  }
  return istream;
}
#ifndef ONLINE_JUDGE
#include "/home/shelpam/Documents/projects/competitive-programming/libs/debug.h"
#else
#define debug(...)
#endif
auto chmax(auto &value, auto const &other) noexcept -> bool
{
  if (value < other) {
    value = other;
    return true;
  }
  return false;
}
auto chmin(auto &value, auto const &other) noexcept -> bool
{
  if (value > other) {
    value = other;
    return true;
  }
  return false;
}
constexpr auto sum_of(std::ranges::range auto const &coll) noexcept
{
  return std::accumulate(coll.begin(), coll.end(), std::int_fast64_t{});
}
constexpr auto pow(auto a, std::int_fast64_t b, std::uint_fast64_t p)
{
  static_assert(sizeof(a) > sizeof(int), "Use of int is bug-prone.");
  if (b < 0) {
    throw std::invalid_argument{"Invalid exponent. It should be positive."};
  }
  decltype(a) res{1};
  while (b != 0) {
    if ((b & 1) == 1) {
      res = res * a % p;
    }
    a = a * a % p;
    b >>= 1;
  }
  return res;
}
auto binary_search(std::invocable<std::int_fast64_t> auto check,
                   std::int_fast64_t ok, std::int_fast64_t ng,
                   bool check_ok = true) -> std::int_fast64_t
{
  if (check_ok && !check(ok)) {
    throw std::invalid_argument{"check isn't true on 'ok'."};
  }
  while (std::abs(ok - ng) > 1) {
    auto const x{(ok + ng) / 2};
    (check(x) ? ok : ng) = x;
  }
  return ok;
}
constexpr auto lsb(std::signed_integral auto i) noexcept -> decltype(i)
{
  return i & -i;
}
// i mustn't be 0
constexpr auto msb(std::unsigned_integral auto i) -> int
{
  if (i == 0) {
    throw std::invalid_argument{"i must be positive."};
  }
  return sizeof(i) * CHAR_BIT - 1 - std::countl_zero(i);
}
/*[[maybe_unused]] auto gen_rand() noexcept*/
/*{*/
/*  static std::mt19937_64 rng(*/
/*      std::chrono::steady_clock::now().time_since_epoch().count());*/
/*  return rng();*/
/*}*/
void solve_case();
} // namespace
auto main() -> int
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  constexpr auto my_precision{10};
  std::cout << std::fixed << std::setprecision(my_precision);
  int t{1};
  // std::cin >> t;
  for (int i{}; i != t; ++i) {
    try {
      std::cerr << "Test case " << i << '\n';
      solve_case();
    }
    catch (std::exception &e) {
      std::cerr << "Exception: " << e.what() << '\n';
    }
  }
  return 0;
}
namespace {
using i64 = std::int_fast64_t;
using u64 = std::uint_fast64_t;
namespace shelpam::linear_algebra {

[[maybe_unused]] constexpr long double eps{1e-8};

auto square(auto x) -> decltype(x * x)
{
  return x * x;
}

struct Vector {
  [[nodiscard]] auto length() const -> long long
  {
    return std::sqrt((x * x) + (y * y));
  }

  long long x, y;
};
using Point = Vector;

struct Line {
  Line(Point p, Point q) : x{p.x}, y{p.y}, k{(p.y - q.y) / (p.x - q.x)} {}

  long long x, y;
  long long k;
};

struct Line_2 {
  Point p, q;
};

struct Circle {
  long long x, y;
  long long r;
};

// 非相切的相交
// Inaccurate
auto intersect(Line l, Circle c) -> bool
{
  return square((l.k * (c.x - l.x)) - (c.y - l.y)) <
         c.r * c.r * (1 + (l.k * l.k));
}

// 非相切的相交，精度比点斜式表示的直线高
// 注意：此函数涉及到x^4，不要超出数据类型表示范围了。
auto intersect(Line_2 l, Circle c) -> bool
{
  auto const &[p, q]{l};
  return square(((p.y - q.y) * (c.x - p.x)) - ((p.x - q.x) * (c.y - p.y))) <
         (square(p.x - q.x) + square(p.y - q.y)) * (square(c.r));
}

// Inaccurate
auto distance(Point p, Line l) -> long long
{
  return std::abs((l.k * (p.x - l.x)) - (p.y - l.y)) /
         std::sqrt(1 + (l.k * l.k));
}

auto operator==(Vector u, Vector v) -> bool
{
  return std::abs(u.x - v.x) < eps && std::abs(u.y - v.y) < eps;
}

auto operator+(Vector u, Vector v) -> Vector
{
  return {.x = u.x + v.x, .y = u.y + v.y};
}

auto operator-(Vector u, Vector v) -> Vector
{
  return {.x = u.x - v.x, .y = u.y - v.y};
}

auto dot(Vector u, Vector v) -> long long
{
  return (u.x * v.x) + (u.y * v.y);
}

auto cross(Vector u, Vector v) -> long long
{
  return (u.x * v.y) - (u.y * v.x);
}

auto area(Point p, Point q, Point r) -> long long
{
  return std::abs(cross(p - q, p - r)) / 2;
}

using Polygen = std::vector<Point>; // Points in std::vector should be ordered.
auto in_polygen(Polygen const &poly, Point p) -> bool
{
  long long a{};
  for (std::size_t i{}; i != poly.size(); ++i) {
    a += area(poly[0], poly[i], poly[(i + 1) % poly.size()]);
    a -= area(p, poly[i], poly[(i + 1) % poly.size()]);
  }
  return std::abs(a) < eps;
}

struct Rectangle {
  [[nodiscard]] auto width() const -> long long
  {
    return std::abs(p.x - q.x);
  }

  [[nodiscard]] auto height() const -> long long
  {
    return std::abs(p.y - q.y);
  }

  Point p, q;
};

auto intersect(Rectangle const &r1, Rectangle const &r2) -> bool
{
  auto const dx{std::abs(r1.p.x + r1.q.x - r2.p.x - r2.q.x)};
  auto const dy{std::abs(r1.p.y + r1.q.y - r2.p.y - r2.q.y)};
  // std::cerr << r1.p.x << ' ' << r1.p.y << ' ' << r1.q.x << ' ' << r1.q.y
  //           << " | ";
  // std::cerr << r2.p.x << ' ' << r2.p.y << ' ' << r2.q.x << ' ' << r2.q.y
  //           << " intersected? "
  //           << (dx < (r1.width() + r2.width()) &&
  //               dy < (r1.height() + r2.height()))
  //           << '\n';
  return dx < (r1.width() + r2.width()) && dy < (r1.height() + r2.height());
}

} // namespace shelpam::linear_algebra
void solve_case()
{
  using namespace shelpam::linear_algebra;
  int n, l, h;
  std::cin >> n >> l >> h;
  std::unordered_set<int> xs{0}, ys{0};
  std::vector<Rectangle> rects;
  for (int i{}; i != n; ++i) {
    int x, y;
    std::cin >> x >> y;
    std::pair<long long, long long> best{inf<long long>, inf<long long>};
    Rectangle best_rect;
    for (auto const x_ : xs) {
      for (auto const y_ : ys) {
        Point p{x_, y_};
        Point q{x + x_, y + y_};
        Rectangle to{p, q};
        if (to.q.x > l || to.q.y > h) {
          continue;
        }
        if (std::ranges::all_of(
                rects, [&to](auto rect) { return !intersect(rect, to); })) {
          if (best.first > p.x) {
            best = {p.x, p.y};
            best_rect = to;
          }
          else if (best.first == p.x && best.second > p.y) {
            best = {p.x, p.y};
            best_rect = to;
          }
        }
      }
    }
    if (best !=
        std::pair<long long, long long>{inf<long long>, inf<long long>}) {
      xs.insert(best.first);
      xs.insert(best.first + x);
      ys.insert(best.second);
      ys.insert(best.second + y);
      rects.push_back(best_rect);
      std::cout << best.first << ' ' << best.second << '\n';
    }
    else {
      std::cout << -1 << '\n';
    }
  }
}
} // namespace
