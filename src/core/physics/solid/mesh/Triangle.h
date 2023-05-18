/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Triangle.h
 * PURPOSE   : triangle class used in mesh
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */
#pragma once

#include "../../../../Definitions.h"

namespace unreal_fluid::physics::solid {
  struct Triangle {
    vec3f v1, v2, v3;

    Triangle() = default;

    Triangle(vec3f v1, vec3f v2, vec3f v3) : v1(v1),
                                             v2(v2),
                                             v3(v3) {}

    ~Triangle() = default;
  };
} // namespace unreal_fluid::physics::solid

// end of Triangle.h
