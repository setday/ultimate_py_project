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
 * authors of this project.
 */

#pragma once
#include "../../maths/MathHeaders"

using namespace unreal_fluid;

namespace unreal_fluid::fluid {
  class Particle {
  private:
    vec3 _velocity, _position;
    double _radius, _mass;

  public:
    void *metaData;

  public:
    Particle(const vec3 &velocity, const vec3 &position, double radius, double mass, void *metaData);
    ~Particle() = default;

    double getX() const;
    double getY() const;
    double getZ() const;
    double getRadius() const;
    void advect(double dt);
  };
} // namespace unreal_fluid::fluid
