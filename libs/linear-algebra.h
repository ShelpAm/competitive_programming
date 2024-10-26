#include <cmath>
#include <vector>

namespace shelpam::linear_algebra {

[[maybe_unused]] constexpr long double eps{1e-8};

auto square(auto x) -> decltype(x * x)
{
  return x * x;
}

struct Vector {
  [[nodiscard]] auto length() const -> long double
  {
    return std::sqrt((x * x) + (y * y));
  }

  long double x, y;
};
using Point = Vector;

struct Line {
  Line(Point p, Point q) : x{p.x}, y{p.y}, k{(p.y - q.y) / (p.x - q.x)} {}

  long double x, y;
  long double k;
};

struct Line_2 {
  Point p, q;
};

struct Circle {
  long double x, y;
  long double r;
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
auto distance(Point p, Line l) -> long double
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

auto dot(Vector u, Vector v) -> long double
{
  return (u.x * v.x) + (u.y * v.y);
}

auto cross(Vector u, Vector v) -> long double
{
  return (u.x * v.y) - (u.y * v.x);
}

auto area(Point p, Point q, Point r) -> long double
{
  return std::abs(cross(p - q, p - r)) / 2;
}

using Polygen = std::vector<Point>; // Points in std::vector should be ordered.
auto in_polygen(Polygen const &poly, Point p) -> bool
{
  long double a{};
  for (std::size_t i{}; i != poly.size(); ++i) {
    a += area(poly[0], poly[i], poly[(i + 1) % poly.size()]);
    a -= area(p, poly[i], poly[(i + 1) % poly.size()]);
  }
  return std::abs(a) < eps;
}

} // namespace shelpam::linear_algebra
