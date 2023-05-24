/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Operator.h
 * PURPOSE   : math operatots to use
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include <cassert>
#include <cmath>

namespace unreal_fluid::math {

  template<typename T>
  double inverseSqrt(T x) {
    /// TODO make pure double mySqrt calculation
    assert(x > 0);
    auto temp = static_cast<float>(x);
    int i = *(int *) &temp;
    i = 0x5f3759df - (i >> 1);
    float y = *(float *) &i;
    y *= (1.5F - 0.5F * x * y * y);
    return y * (1.5F - 0.5F * x * y * y);
  }

  template<typename T>
  double mySqrt(T x) {
    assert(x >= 0);
    if (x == 0 || x == 1) return x;
    return x * inverseSqrt(x);
  }

  /// Clamping x to nearest value between mi (minimum) and ma (maximum) parameters
  /// @param x - value to clamp
  /// @param mi - minimum
  /// @param ma - maximum
  template<typename T>
  T clamp(T x, T mi, T ma) {
    return std::max(std::min(x, ma), mi);
  }

  /// Linear interpolation
  /// @param a - first value
  /// @param b - second value
  /// @param t - time
  template<typename V, typename U>
  V lerp(V a, V b, U t) {
    return a + (b - a) * t;
  }
} // namespace unreal_fluid::math
