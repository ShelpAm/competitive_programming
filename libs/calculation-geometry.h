#pragma once

#include <array>
#include <cstdint>

template <typename Value_type, std::size_t Dimension> struct Vector {
  friend auto operator+(Vector lhs, Vector const &rhs)
  {
    return lhs += rhs;
  }

  friend auto operator-(Vector lhs, Vector const &rhs)
  {
    return lhs -= rhs;
  }

  friend auto dot(Vector const &lhs, Vector const &rhs) -> Value_type
  {
    Value_type result{};
    for (std::size_t i{}; i != Dimension; ++i) {
      result += lhs.coordinate[i] * rhs.coordinate[i];
    }
    return result;
  }

  /*friend auto cross(Vector const &lhs, Vector const &rhs) -> Vector {}*/

  auto operator+=(Vector const &rhs) -> Vector &
  {
    for (std::size_t i{}; i != Dimension; ++i) {
      coordinate[i] += rhs.coordinate[i];
    }
    return *this;
  }

  auto operator-=(Vector const &rhs) -> Vector &
  {
    for (std::size_t i{}; i != Dimension; ++i) {
      coordinate[i] -= rhs.coordinate[i];
    }
    return *this;
  }

  std::array<Value_type, Dimension> coordinate{};
};

template <typename Value_type> class Line2d {
  friend auto intersect(Line2d const &lhs,
                        Line2d const &rhs) -> Vector<Value_type, 2>
  {
  }

  std::array<Vector<Value_type, 2>, 2> points;
};
