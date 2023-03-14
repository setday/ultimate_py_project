/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Vector3.h
 * PURPOSE   : usable vec3 realization
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include <cassert>
#include <cmath>
#include <string>

namespace unreal_fluid::math {

  template<typename T>
  class Vector3 {
  public:
    T x;
    T y;
    T z;

    Vector3() = default;
    ~Vector3() = default;

    Vector3(T a) : x(a),
                   y(a),
                   z(a) {}

    Vector3(T x, T y, T z) : x(x),
                             y(y),
                             z(z) {}

    template<typename G>
    Vector3(const Vector3<G> &v) : x(static_cast<T>(v.x)),
                                   y(static_cast<T>(v.y)),
                                   z(static_cast<T>(v.z)) {
    }

    Vector3 operator+(const Vector3 &v) const {
      return Vector3(x + v.x, y + v.y, z + v.z);
    }

    Vector3 *operator+=(const Vector3 &v) {
      x += v.x;
      y += v.y;
      z += v.z;
      return this;
    }

    Vector3 operator-(const Vector3 &v) const {
      return Vector3(x - v.x, y - v.y, z - v.z);
    }

    Vector3 *operator-=(const Vector3 &v) {
      x -= v.x;
      y -= v.y;
      z -= v.z;
      return this;
    }


    double distanceTo(Vector3<T>& v){
      return (v - *this).len();
    }

    template<typename R>
    Vector3 operator*(R c) const {
      return Vector3(x * c, y * c, z * c);
    }

    template<typename R>
    Vector3 *operator*=(R c) {
      x *= c;
      y *= c;
      z *= c;
      return this;
    }

    template<typename R>
    Vector3 operator/(R c) const {
      return Vector3(x / c, y / c, z / c);
    }

    template<typename R>
    Vector3 *operator/=(R c) {
      x /= c;
      y /= c;
      z /= c;
      return this;
    }

    Vector3 operator-() const {
      return Vector3(-x, -y, -z);
    }

    [[nodiscard]] T len2() const { return x * x + y * y + z * z; }

    [[nodiscard]] double len() const { return sqrt(len2()); }

    [[nodiscard]] double operator!() const { return len(); }

    Vector3 normalize() const {
      assert(len() > 0);
      return *this / len();
    }

    void normalizeSelf() {
      assert(len() > 0);
      *this /= len();
    }

    Vector3 operator*(const Vector3 &vec) const {
      return Vector3(x * vec.x, y * vec.y, z * vec.z);
    }

    T dot(const Vector3 &v) const {
      return x * v.x + y * v.y + z * v.z;
    }

    Vector3 cross(const Vector3 &v) const {
      return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }

    T project(const Vector3 &v) {
      assert(v.len() > 0);
      return this->dot(v) / v.len();
    }

    [[nodiscard]] std::string to_string() const {
      return std::string("{" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + "}");
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector3 &v) {
      os << v.to_string();
      return os;
    }

    friend Vector3<T> operator/(const Vector3 &vec, T c) {
      return Vector3(vec.x / c, vec.y / c, vec.z / c);
    }

    friend Vector3<T> operator*(float c, const Vector3<T> &vec) {
      return Vector3(vec.x * c, vec.y * c, vec.z * c);
    }
  };
} // namespace unreal_fluid::math