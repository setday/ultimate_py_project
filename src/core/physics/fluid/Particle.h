/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Particle.h
 * PURPOSE   : particle realization (ZZZ)
 *
 * No part of this file may be changed and used without agreement of
 * authors of this pressureSolving.
 */

#pragma once

#include "../../../Definitions.h"

using namespace unreal_fluid::math;

namespace unreal_fluid::fluid {
  class Particle {
  public:
    vec3 v, c;
    double r, m;
  public:
    Particle() = default;
    ~Particle() = default;
  };
} // namespace unreal_fluid::fluid
