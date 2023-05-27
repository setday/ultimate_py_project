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


    double distanceTo(const Vector3<T>& v){
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

    [[nodiscard]] double len() const { return mySqrt(len2()); }

    [[nodiscard]] double operator!() const { return len(); }

    Vector3 normalized() const {
      assert(len2() != 0);
      return *this / len();
    }

    void normalizeSelf() {
      assert(len2() != 0);
      *this /= len();
    }

    Vector3 operator*(const Vector3 &vec) const {
      return Vector3(x * vec.x, y * vec.y, z * vec.z);
    }

    [[deprecated("Use static dot function instead")]]
    T dot(const Vector3 &v) const {
      return x * v.x + y * v.y + z * v.z;
    }

    [[deprecated("Use static cross function instead")]]
    Vector3 cross(const Vector3 &v) const {
      return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }

    [[deprecated("Use static project function instead")]]
    T project(const Vector3 &v) {
      if (len() == 0) return 0;
      return this->dot(v) / v.len();
    }
    
    /// Linear interpolation between two vectors
    /// @param v - vector to interpolate to
    /// @param t - interpolation coefficient
    /// @attention This is experimental and may be removed in future
    Vector3 lerped(const Vector3 &v, float t) const {
      return *this * (1 - t) + v * t;
    }

    /// Clamp vector to the given range
    /// @param min - minimum value
    /// @param max - maximum value
    Vector3 clamp(const Vector3 &min, const Vector3 &max) const {
      return Vector3(std::min(std::max(x, min.x), max.x),
                     std::min(std::max(y, min.y), max.y),
                     std::min(std::max(z, min.z), max.z));
    }

    /// Get maximum value of vector
    /// @return maximum value
    T max() const {
      return std::max(std::max(x, y), z);
    }

    /// Get minimum value of vector
    /// @return minimum value
    T min() const {
      return std::min(std::min(x, y), z);
    }

    [[nodiscard]] std::string to_string() const {
      return std::string("{" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + "}");
    }

    friend std::istream &operator>>(std::istream &is, Vector3 &v) {
      is >> v.x >> v.y >> v.z;
      return is;
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

    friend bool operator==(const Vector3 &vec, const Vector3 &other) {
      return vec.x == other.x && vec.y == other.y && vec.z == other.z;
    }

    friend bool operator!=(const Vector3 &vec, const Vector3 &other) {
      return !(vec == other);
    }

    /* static functions */

    /// @brief Get vector with all components set to 0
    static Vector3 zero() {
      return Vector3(0, 0, 0);
    }

    /// @brief Get vector with all components set to 1
    static Vector3 one() {
      return Vector3(1, 1, 1);
    }

    /// Check if vector is zero
    /// @return true if vector is zero, false otherwise
    bool isZero() const {
      return x == 0 && y == 0 && z == 0;
    }

    /// @brief Dot product of two vectors
    /// @param first - first vector
    /// @param second - second vector
    /// @return dot product of two vectors
    /// @attention (first * second)
    static T dot(const Vector3 &first, const Vector3 &second) {
      return first.x * second.x + first.y * second.y + first.z * second.z;
    }

    /// @brief Cosine of angle between two vectors
    /// @param first - first vector
    /// @param second - second vector
    /// @return cosine of angle between two vectors
    /// @attention cos(angle) = (first * second) / (|first| * |second|)
    static double cos(const Vector3 &first, const Vector3 &second) {
      assert(!first.isZero() && !second.isZero());

      return dot(first, second) / (first.len() * second.len());
    }

    /// @brief Project vector to another vector
    /// @param from - vector to project
    /// @param to - vector to project to
    /// @return projection of vector to another vector
    /// @attention projection = (from * to) / (|to| * |to|) * to
    static Vector3 project(const Vector3 &from, const Vector3 &to) {
      assert(!to.isZero());

      return to * (dot(from, to) / to.len2());
    }

    /// @brief Cross product of two vectors
    /// @param forward - first vector
    /// @param left - second vector
    /// @return cross product of two vectors
    /// @attention (forward x left = up)
    static Vector3 cross(const Vector3 &forward, const Vector3 &left) {
      return Vector3(forward.y * left.z - forward.z * left.y,
                     forward.z * left.x - forward.x * left.z,
                     forward.x * left.y - forward.y * left.x);
    }

    /// @brief Normalized cross product of two vectors
    /// @param forward - first vector
    /// @param left - second vector
    /// @return normalized cross product of two vectors
    /// @attention normalized(forward x left = up)
    static Vector3 normalizedCross(const Vector3 &forward, const Vector3 &left) {
      Vector3 result = cross(forward, left);

      assert(!result.isZero());

      return result.normalizeSelf();
    }

    /// @brief Linear interpolation between two vectors
    /// @param from - vector to interpolate from
    /// @param to - vector to interpolate to
    /// @param t - interpolation coefficient
    /// @return interpolated vector
    /// @attention (1 - t) * from + t * to
    static Vector3 lerp(const Vector3 &from, const Vector3 &to, float t) {
      return from * (1 - t) + to * t;
    }

    /// @brief Clamp vector to the given range
    /// @param vec - vector to clamp
    /// @param min - minimum value
    /// @param max - maximum value
    /// @return clamped vector
    static Vector3 clamp(const Vector3 &vec, const Vector3 &min, const Vector3 &max) {
      return Vector3(std::min(std::max(vec.x, min.x), max.x),
                     std::min(std::max(vec.y, min.y), max.y),
                     std::min(std::max(vec.z, min.z), max.z));
    }

    /// @brief Get maximum value of vector
    /// @param vec - vector to get maximum value from
    /// @return maximum value
    static T max(const Vector3 &vec) {
      return std::max(std::max(vec.x, vec.y), vec.z);
    }

    /// @brief Get minimum value of vector
    /// @param vec - vector to get minimum value from
    /// @return minimum value
    static T min(const Vector3 &vec) {
      return std::min(std::min(vec.x, vec.y), vec.z);
    }

    /// @brief Get vector with maximum values from two vectors
    /// @param first - first vector
    /// @param second - second vector
    /// @return vector with maximum values from two vectors
    static Vector3 max(const Vector3 &first, const Vector3 &second) {
      return Vector3(std::max(first.x, second.x),
                     std::max(first.y, second.y),
                     std::max(first.z, second.z));
    }

    /// @brief Get vector with minimum values from two vectors
    /// @param first - first vector
    /// @param second - second vector
    /// @return vector with minimum values from two vectors
    static Vector3 min(const Vector3 &first, const Vector3 &second) {
      return Vector3(std::min(first.x, second.x),
                     std::min(first.y, second.y),
                     std::min(first.z, second.z));
    }

    /// @brief Get vector with absolute values
    /// @param vec - vector to get absolute values from
    /// @return vector with absolute values
    static Vector3 abs(const Vector3 &vec) {
      return Vector3(std::abs(vec.x), std::abs(vec.y), std::abs(vec.z));
    }

    /// @brief Get vector with sign values
    /// @param vec - vector to get sign values from
    /// @return vector with sign values
    static Vector3 sign(const Vector3 &vec) {
      return Vector3(std::signbit(vec.x), std::signbit(vec.y), std::signbit(vec.z));
    }
  };
} // namespace unreal_fluid::math