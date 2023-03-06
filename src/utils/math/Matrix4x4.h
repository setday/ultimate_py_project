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

namespace unreal_fluid::math {

template<typename T>
  class Matrix4x4 {
  public:
    T matrix[16];

    Matrix4x4() = default;
    ~Matrix4x4() = default;

    Matrix4x4(T matrix[16]) {
      for (int i = 0; i < 16; i++) {
        this->matrix[i] = matrix[i];
      }
    }
  };
} // namespace unreal_fluid::math

// end of Matrix4x4.h
