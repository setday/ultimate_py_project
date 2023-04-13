/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Particle.h
 * PURPOSE   : particle realization
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "../../../Definitions.h"

namespace unreal_fluid::physics::fluid {
  class Particle {
  public:
    vec3 velocity, position;
    double radius, mass;

    Particle() = default;
    ~Particle() = default;
  };
} // namespace unreal_fluid::physics::fluid

// end of Particle.h
