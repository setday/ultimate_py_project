/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Collision.h
 * PURPOSE   : Implements collision between different objects
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once
#include "fluid/Particle.h"
#include "solid/sphere/SolidSphere.h"

namespace unreal_fluid::physics {
  class Collision {
  public:
    /// @brief collides two particles
    static void particlesCollision(fluid::Particle *p1, fluid::Particle *p2, double k);

    /// @brief collides particle with sphere
    static void sphereCollision(fluid::Particle *p, solid::SolidSphere *s, double k);
  };

} // namespace unreal_fluid::physics::fluid
