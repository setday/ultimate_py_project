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
 * authors of this pressureSolving.
 */

#pragma once
#include <assert.h>

namespace unreal_fluid::math {

  template<typename T>
  double inverseSqrt(T x) {
    assert(x > 0);
    //TODO make pure double sqrt calculation
    auto temp = static_cast<float>(x);
    int i = *(int*)&temp;
    i = 0x5f3759df - (i >> 1);
    float y = *(float*)&i;
    y *= (1.5F - 0.5F * x * y * y);
    return y * (1.5F - 0.5F * x * y * y);
  }

  template<typename T>
  double sqrt(T x){
    if (x == 0) return 0;
    return 1.0/ inverseSqrt(x);
  }

} // namespace maths
