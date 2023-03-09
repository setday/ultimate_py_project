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

  template<typename T>
  class Vector2 {
  public:
    T x;
    T y;

    Vector2() = default;
    ~Vector2() = default;

    Vector2(T x, T y) : x(x),
                        y(y) {}

    template<typename G>
    explicit Vector2(const Vector2<G> &v) : x(dynamic_cast<T>(v.x)),
                                            y(dynamic_cast<T>(v.y)) {
    }

    Vector2 operator+(const Vector2 &v) const {
      return Vector2(x + v.x, y + v.y);
    }

    Vector2 *operator+=(const Vector2 &v) {
      x += v.x;
      y += v.y;
      return this;
    }

    Vector2 operator-(const Vector2 &v) const {
      return Vector2(x - v.x, y - v.y);
    }

    Vector2 *operator-=(const Vector2 &v) {
      x -= v.x;
      y -= v.y;
      return this;
    }

    template<typename R>
    Vector2 operator*(R c) const {
      return Vector2(x * c, y * c);
    }

    template<typename R>
    Vector2 *operator*=(R c) {
      x *= c;
      y *= c;
      return this;
    }

    template<typename R>
    Vector2 operator/(R c) const {
      return Vector2(x / c, y / c);
    }

    template<typename R>
    Vector2 *operator/=(R c) {
      x /= c;
      y /= c;
      return this;
    }

    Vector2 operator-() const {
      return Vector2(-x, -y);
    }

    [[nodiscard]] T len2() const { return x * x + y * y; }

    [[nodiscard]] double len() const { return root(len2()); }

    [[nodiscard]] double operator!() const { return len(); }

    Vector2 normalize() const {
      return this / len();
    }

    Vector2 *normalizeSelf() {
      return this /= len();
    }

    Vector2 operator*(const Vector2 &vec) const {
      return Vector2(x * vec.x, y * vec.y);
    }

    T dot(const Vector2 &v) const {
      return x * v.x + y * v.y;
    }

    [[nodiscard]] std::string to_string() const {
      return std::string("{" + std::to_string(x) + ", " + std::to_string(y) + "}");
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
