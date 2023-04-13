/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : CollisionSolver.h
 * PURPOSE   : Implements collision between different objects
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "fluid/Particle.h"
#include "solid/sphere/SolidSphere.h"

namespace unreal_fluid::physics {
  class CollisionSolver {
  public:
    /// @brief collides two particles
    /// @details takes two particles p1, p2 and uses k - coefficient of restitution - to collide them
    static void particleWithParticleCollision(fluid::Particle *p1, fluid::Particle *p2, double k);

    /// @brief collides particle with sphere
    /// @details takes particle p, static sphere s and uses k - coefficient of restitution - to collide them
    static void particleWithSphereCollision(fluid::Particle *p, solid::SolidSphere *s, double k);
  };

} // namespace unreal_fluid::physics::fluid

// end of CollisionSolver.h
