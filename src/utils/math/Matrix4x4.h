/***************************************************************
* Copyright (C) 2023
*    HSE SPb (Higher school of economics in Saint-Petersburg).
***************************************************************/

/* PROJECT   : UnrealFluidPhysics
* AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
* FILE NAME : Matrix4x4.h
* PURPOSE   : usable matrix 4x4 realization
*
* No part of this file may be changed and used without agreement of
* authors of this project.
*/

#pragma once

#include <vector>
#include <string>

#include "Vector3.h"

namespace unreal_fluid::math {

template<typename T>
  class Matrix4x4 {
  public:
    T matrix[16];
    T inverse_matrix[16];

    bool has_inverse = false;

    Matrix4x4() : matrix{1, 0, 0, 0,
                         0, 1, 0, 0,
                         0, 0, 1, 0,
                         0, 0, 0, 1} {
    }

    ~Matrix4x4() = default;

    Matrix4x4(T matrix[16]) : matrix{matrix[0], matrix[1], matrix[2], matrix[3],
                                     matrix[4], matrix[5], matrix[6], matrix[7],
                                     matrix[8], matrix[9], matrix[10], matrix[11],
                                     matrix[12], matrix[13], matrix[14], matrix[15]} {
    }

    Matrix4x4(std::vector<T> matrix) : matrix{matrix[0], matrix[1], matrix[2], matrix[3],
                                              matrix[4], matrix[5], matrix[6], matrix[7],
                                              matrix[8], matrix[9], matrix[10], matrix[11],
                                              matrix[12], matrix[13], matrix[14], matrix[15]} {
    }

    Matrix4x4(T m00, T m01, T m02, T m03,
              T m10, T m11, T m12, T m13,
              T m20, T m21, T m22, T m23,
              T m30, T m31, T m32, T m33) : matrix{m00, m01, m02, m03,
                                                   m10, m11, m12, m13,
                                                   m20, m21, m22, m23,
                                                   m30, m31, m32, m33} {
    }

    const T *data() const {
      return matrix;
    }

    Matrix4x4 operator*(const Matrix4x4 &m) const {
      Matrix4x4 result;

      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
          result.matrix[i * 4 + j] = 0;
          for (int k = 0; k < 4; k++) {
            result.matrix[i * 4 + j] += matrix[i * 4 + k] * m.matrix[k * 4 + j];
          }
        }
      }

      return result;
    }

    Matrix4x4 *operator*=(const Matrix4x4 &m) {
      Matrix4x4 result = *this * m;

      for (int i = 0; i < 16; i++) {
        matrix[i] = result.matrix[i];
      }

      has_inverse = false;

      return this;
    }

    std::string to_string() const {
      std::string result = "";

      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
          result += std::to_string(matrix[i * 4 + j]) + " ";
        }
        result += "|\n|";
      }

      return result;
    }

    static Matrix4x4 identity() {
      return Matrix4x4(1, 0, 0, 0,
                       0, 1, 0, 0,
                       0, 0, 1, 0,
                       0, 0, 0, 1);
    }

    static Matrix4x4 translation(const Vector3<T> &v) {
      return Matrix4x4(1,     0,   0, 0,
                       0,     1,   0, 0,
                       0,     0,   1, 0,
                       v.x, v.y, v.z, 1);
    }

    Matrix4x4 withTranslation(const Vector3<T> &v) const {
      return this * translation(v);
    }

    static Matrix4x4 scale(const Vector3<T> &v) {
      return Matrix4x4(v.x, 0,   0, 0,
                       0, v.y,   0, 0,
                       0,   0, v.z, 0,
                       0,   0,   0, 1);
    }

    Matrix4x4 withScale(const Vector3<T> &v) const {
      return this * scale(v);
    }

    static Matrix4x4 rotation(T angle, const Vector3<T> &v) {
      T c = cos(angle);
      T s = sin(angle);
      T t = 1 - c;

      return Matrix4x4(t * v.x * v.x + c, t * v.x * v.y + s * v.z, t * v.x * v.z - s * v.y, 0,
                       t * v.x * v.y - s * v.z, t * v.y * v.y + c, t * v.y * v.z + s * v.x, 0,
                       t * v.x * v.z + s * v.y, t * v.y * v.z - s * v.x, t * v.z * v.z + c, 0,
                       0, 0, 0, 1);
    }

    Matrix4x4 withRotation(const Vector3<T> &v, T angle) const {
      return this * rotation(v, angle);
    }

    static Matrix4x4 rotationX(T angle) {
      return Matrix4x4(1, 0, 0, 0,
                       0, cos(angle), sin(angle), 0,
                       0, -sin(angle), cos(angle), 0,
                       0, 0, 0, 1);
    }

    Matrix4x4 withRotationX(T angle) const {
      return this * rotationX(angle);
    }

    static Matrix4x4 rotationY(T angle) {
      return Matrix4x4(cos(angle), 0, sin(angle), 0,
                       0, 1, 0, 0,
                       -sin(angle), 0, cos(angle), 0,
                       0, 0, 0, 1);
    }

    static Matrix4x4 rotationZ(T angle) {
      return Matrix4x4(cos(angle), sin(angle), 0, 0,
                       -sin(angle), cos(angle), 0, 0,
                       0, 0, 1, 0,
                       0, 0, 0, 1);
    }

    Matrix4x4 withRotationZ(T angle) const {
      return this * rotationZ(angle);
    }

    static Matrix4x4 perspective(T fov, T aspect, T near, T far) {
      T f = 1 / tan(fov / 2);

      return Matrix4x4(f / aspect, 0, 0, 0,
                       0, f, 0, 0,
                       0, 0, (far + near) / (near - far), -1,
                       0, 0, (2 * far * near) / (near - far), 0);
    }

    static Matrix4x4 lookAt(const Vector3<T> &eye, const Vector3<T> &center, const Vector3<T> &up) {
      Vector3<T> f = (center - eye).normalize();
      Vector3<T> s = up.cross(f).normalize();
      Vector3<T> u = f.cross(s);

      return Matrix4x4(s.x, u.x, f.x, 0,
                       s.y, u.y, f.y, 0,
                       s.z, u.z, f.z, 0,
                       -s.dot(eye), -u.dot(eye), -f.dot(eye), 1);
    }

    static Matrix4x4 ortho(T left, T right, T bottom, T top, T near, T far) {
      return Matrix4x4(2 / (right - left), 0, 0, 0,
                       0, 2 / (top - bottom), 0, 0,
                       0, 0, -2 / (far - near), 0,
                       -(right + left) / (right - left), -(top + bottom) / (top - bottom), -(far + near) / (far - near), 1);
    }

    static Matrix4x4 transpose(const Matrix4x4 &m) {
      return Matrix4x4(m.matrix[0], m.matrix[4], m.matrix[8], m.matrix[12],
                       m.matrix[1], m.matrix[5], m.matrix[9], m.matrix[13],
                       m.matrix[2], m.matrix[6], m.matrix[10], m.matrix[14],
                       m.matrix[3], m.matrix[7], m.matrix[11], m.matrix[15]);
    }

    Matrix4x4 withTranspose() const {
      return transpose(*this);
    }

    void calculateInverse() {
      int i;

      inverse_matrix[0] = matrix[5] * matrix[10] * matrix[15] -
                          matrix[5] * matrix[11] * matrix[14] -
                          matrix[9] * matrix[6] * matrix[15] +
                          matrix[9] * matrix[7] * matrix[14] +
                          matrix[13] * matrix[6] * matrix[11] -
                          matrix[13] * matrix[7] * matrix[10];

      inverse_matrix[4] = -matrix[4] * matrix[10] * matrix[15] +
                          matrix[4] * matrix[11] * matrix[14] +
                          matrix[8] * matrix[6] * matrix[15] -
                          matrix[8] * matrix[7] * matrix[14] -
                          matrix[12] * matrix[6] * matrix[11] +
                          matrix[12] * matrix[7] * matrix[10];

      inverse_matrix[8] = matrix[4] * matrix[9] * matrix[15] -
                          matrix[4] * matrix[11] * matrix[13] -
                          matrix[8] * matrix[5] * matrix[15] +
                          matrix[8] * matrix[7] * matrix[13] +
                          matrix[12] * matrix[5] * matrix[11] -
                          matrix[12] * matrix[7] * matrix[9];

      inverse_matrix[12] = -matrix[4] * matrix[9] * matrix[14] +
                           matrix[4] * matrix[10] * matrix[13] +
                           matrix[8] * matrix[5] * matrix[14] -
                           matrix[8] * matrix[6] * matrix[13] -
                           matrix[12] * matrix[5] * matrix[10] +
                           matrix[12] * matrix[6] * matrix[9];

      inverse_matrix[1] = -matrix[1] * matrix[10] * matrix[15] +
                          matrix[1] * matrix[11] * matrix[14] +
                          matrix[9] * matrix[2] * matrix[15] -
                          matrix[9] * matrix[3] * matrix[14] -
                          matrix[13] * matrix[2] * matrix[11] +
                          matrix[13] * matrix[3] * matrix[10];

      inverse_matrix[5] = matrix[0] * matrix[10] * matrix[15] -
                          matrix[0] * matrix[11] * matrix[14] -
                          matrix[8] * matrix[2] * matrix[15] +
                          matrix[8] * matrix[3] * matrix[14] +
                          matrix[12] * matrix[2] * matrix[11] -
                          matrix[12] * matrix[3] * matrix[10];

      inverse_matrix[9] = -matrix[0] * matrix[9] * matrix[15] +
                          matrix[0] * matrix[11] * matrix[13] +
                          matrix[8] * matrix[1] * matrix[15] -
                          matrix[8] * matrix[3] * matrix[13] -
                          matrix[12] * matrix[1] * matrix[11] +
                          matrix[12] * matrix[3] * matrix[9];

      inverse_matrix[13] = matrix[0] * matrix[9] * matrix[14] -
                           matrix[0] * matrix[10] * matrix[13] -
                           matrix[8] * matrix[1] * matrix[14] +
                           matrix[8] * matrix[2] * matrix[13] +
                           matrix[12] * matrix[1] * matrix[10] -
                           matrix[12] * matrix[2] * matrix[9];

      inverse_matrix[2] = matrix[1] * matrix[6] * matrix[15] -
                          matrix[1] * matrix[7] * matrix[14] -
                          matrix[5] * matrix[2] * matrix[15] +
                          matrix[5] * matrix[3] * matrix[14] +
                          matrix[13] * matrix[2] * matrix[7] -
                          matrix[13] * matrix[3] * matrix[6];

      inverse_matrix[6] = -matrix[0] * matrix[6] * matrix[15] +
                          matrix[0] * matrix[7] * matrix[14] +
                          matrix[4] * matrix[2] * matrix[15] -
                          matrix[4] * matrix[3] * matrix[14] -
                          matrix[12] * matrix[2] * matrix[7] +
                          matrix[12] * matrix[3] * matrix[6];

      inverse_matrix[10] = matrix[0] * matrix[5] * matrix[15] -
                           matrix[0] * matrix[7] * matrix[13] -
                           matrix[4] * matrix[1] * matrix[15] +
                           matrix[4] * matrix[3] * matrix[13] +
                           matrix[12] * matrix[1] * matrix[7] -
                           matrix[12] * matrix[3] * matrix[5];

      inverse_matrix[14] = -matrix[0] * matrix[5] * matrix[14] +
                           matrix[0] * matrix[6] * matrix[13] +
                           matrix[4] * matrix[1] * matrix[14] -
                           matrix[4] * matrix[2] * matrix[13] -
                           matrix[12] * matrix[1] * matrix[6] +
                           matrix[12] * matrix[2] * matrix[5];

      inverse_matrix[3] = -matrix[1] * matrix[6] * matrix[11] +
                          matrix[1] * matrix[7] * matrix[10] +
                          matrix[5] * matrix[2] * matrix[11] -
                          matrix[5] * matrix[3] * matrix[10] -
                          matrix[9] * matrix[2] * matrix[7] +
                          matrix[9] * matrix[3] * matrix[6];

      inverse_matrix[7] = matrix[0] * matrix[6] * matrix[11] -
                          matrix[0] * matrix[7] * matrix[10] -
                          matrix[4] * matrix[2] * matrix[11] +
                          matrix[4] * matrix[3] * matrix[10] +
                          matrix[8] * matrix[2] * matrix[7] -
                          matrix[8] * matrix[3] * matrix[6];

      inverse_matrix[11] = -matrix[0] * matrix[5] * matrix[11] +
                           matrix[0] * matrix[7] * matrix[9] +
                           matrix[4] * matrix[1] * matrix[11] -
                           matrix[4] * matrix[3] * matrix[9] -
                           matrix[8] * matrix[1] * matrix[7] +
                           matrix[8] * matrix[3] * matrix[5];


      inverse_matrix[15] = matrix[0] * matrix[5] * matrix[10] -
                           matrix[0] * matrix[6] * matrix[9] -
                           matrix[4] * matrix[1] * matrix[10] +
                           matrix[4] * matrix[2] * matrix[9] +
                           matrix[8] * matrix[1] * matrix[6] -
                           matrix[8] * matrix[2] * matrix[5];

      T det = matrix[0] * inverse_matrix[0] + matrix[1] * inverse_matrix[4] + matrix[2] * inverse_matrix[8] +
              matrix[3] * inverse_matrix[12];

      if (det == 0) {
        has_inverse = false;

        return;
      }

      det = 1.0 / det;

      for (int i = 0; i < 16; i++) {
        inverse_matrix[i] = inverse_matrix[i] * det;
      }

      has_inverse = true;
    }
  };
} // namespace unreal_fluid::math

// end of Matrix4x4.h
