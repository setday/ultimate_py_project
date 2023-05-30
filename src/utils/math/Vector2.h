/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Vector2.h
 * PURPOSE   : usable vec3 realization
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include <string>

namespace unreal_fluid::math {
  /// Vector2 class
  /// @tparam T - type of vector components
  template<typename T>
  class Vector2 {
  public:
    T x;
    T y;

    Vector2() = default;
    ~Vector2() = default;

    /// create a vector with all components equal to a
    /// @param a - value
    Vector2(T a) : x(a),
                   y(a) {}
    /// create a vector with components x and y
    /// @param x - x component
    /// @param y - y component
    Vector2(T x, T y) : x(x),
                        y(y) {}
    /// create a vector from another vector with different type
    /// @tparam G - type of another vector
    /// @param v - vector
    template<typename G>
    explicit Vector2(const Vector2<G> &v) : x(dynamic_cast<T>(v.x)),
                                            y(dynamic_cast<T>(v.y)) {
    }

    /// Add a vector to this vector
    /// @param v - vector
    /// @return this vector added by v
    Vector2 operator+(const Vector2 &v) const {
      return Vector2(x + v.x, y + v.y);
    }
    /// Add a vector to this vector
    /// @param v - vector
    /// @return this vector added by v
    /// @attention this vector is changed
    Vector2 *operator+=(const Vector2 &v) {
      x += v.x;
      y += v.y;
      return this;
    }

    /// Subtract a vector from this vector
    /// @param v - vector
    /// @return this vector subtracted by v
    Vector2 operator-(const Vector2 &v) const {
      return Vector2(x - v.x, y - v.y);
    }
    /// Subtract a vector from this vector
    /// @param v - vector
    /// @return this vector subtracted by v
    /// @attention this vector is changed
    Vector2 *operator-=(const Vector2 &v) {
      x -= v.x;
      y -= v.y;
      return this;
    }

    /// Multiply this vector by a scalar
    /// @param c - scalar
    /// @return this vector multiplied by c
    template<typename R>
    Vector2 operator*(R c) const {
      return Vector2(x * c, y * c);
    }
    /// Multiply this vector by a scalar
    /// @param c - scalar
    /// @return this vector multiplied by c
    /// @attention this vector is changed
    template<typename R>
    Vector2 *operator*=(R c) {
      x *= c;
      y *= c;
      return this;
    }

    /// Divide this vector by a scalar
    /// @param c - scalar
    /// @return this vector divided by c
    template<typename R>
    Vector2 operator/(R c) const {
      return Vector2(x / c, y / c);
    }
    /// Divide this vector by a scalar
    /// @param c - scalar
    /// @return this vector divided by c
    /// @attention this vector is changed
    template<typename R>
    Vector2 *operator/=(R c) {
      x /= c;
      y /= c;
      return this;
    }

    /// Negate this vector
    /// @return negated vector
    Vector2 operator-() const {
      return Vector2(-x, -y);
    }

    /// Length of this vector squared
    /// @return length of this vector squared
    [[nodiscard]] T len2() const { return x * x + y * y; }
    /// Length of this vector
    /// @return length of this vector
    [[nodiscard]] double len() const { return mySqrt(len2()); }
    /// Alternative to len()
    /// @return length of this vector
    [[nodiscard]] double operator!() const { return len(); }

    /// Normalize this vector
    /// @return normalize vector
    /// @attention this vector is not changed
    Vector2 normalize() const {
      return this / len();
    }
    /// Normalize this vector
    /// @return this vector
    /// @attention this vector is changed
    Vector2 *normalizeSelf() {
      return this /= len();
    }

    /// Multiply two vectors
    /// @param vec - vector
    /// @return vector with components multiplied
    Vector2 operator*(const Vector2 &vec) const {
      return Vector2(x * vec.x, y * vec.y);
    }

    /// Dot product
    /// @param v - vector
    /// @return dot product of this and v
    T dot(const Vector2 &v) const {
      return x * v.x + y * v.y;
    }

    /// Cross product
    /// @param v - vector
    /// @return cross product of this and v
    T cross(const Vector2 &v) const {
      return x * v.y - y * v.x;
    }

    /// Clamp vector to the given range
    /// @param min - minimum value
    /// @param max - maximum value
    Vector2 clampSelf(const Vector2 &min, const Vector2 &max) {
      x = std::min(std::max(x, min.x), max.x);
      y = std::min(std::max(y, min.y), max.y);
      return *this;
    }
    /// Clamp vector to the given range
    /// @param min - minimum value
    /// @param max - maximum value
    Vector2 clamp(const Vector2 &min, const Vector2 &max) const {
      return Vector2(std::min(std::max(x, min.x), max.x),
                     std::min(std::max(y, min.y), max.y));
    }

    /// Get maximum component
    /// @return maximum component
    T max() const {
      return std::max(x, y);
    }

    /// Get minimum component
    /// @return minimum component
    T min() const {
      return std::min(x, y);
    }

    [[nodiscard]] std::string to_string() const {
      return std::string("{" + std::to_string(x) + ", " + std::to_string(y) + "}");
    }

    friend std::istream &operator>>(std::istream &is, Vector2 &v) {
      is >> v.x >> v.y;
      return is;
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector2 &v) {
      os << v.to_string();
      return os;
    }

    friend Vector2<T> operator/(const Vector2 &vec, float c) {
      return Vector2(vec.x / c, vec.y / c);
    }

    friend Vector2<T> operator*(float c, const Vector2<T> &vec) {
      return Vector2(vec.x * c, vec.y * c);
    }
  };
} // namespace unreal_fluid::math

// end of Vector2.h
