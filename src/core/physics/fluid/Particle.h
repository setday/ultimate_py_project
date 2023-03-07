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

#include "../../maths/MathHeaders"

using namespace unreal_fluid;
using namespace math;
namespace unreal_fluid::fluid {
  class Particle {
  private:
    vec3 _v, _c;
    double _r, _m;
  public:
    void *metaData;
  public:
    Particle(const vec3 &velocity, const vec3 &position, double radius, double mass, void *metaData);
    ~Particle() = default;
    vec3 &v();
    vec3 &c();
    double r();
    double m();
  };
} // namespace unreal_fluid::fluid
