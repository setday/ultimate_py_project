/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Vector3.h
 * PURPOSE   : usable vec3 realization
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "Particle.h"

fluid::Particle::Particle(const vec3 &velocity, const vec3 &position, double radius, double mass, void *metaData)
        : _v(velocity),
          _c(position),
          _r(radius),
          _m(mass),
          metaData(metaData) {}


vec3 &fluid::Particle::v() {
  return _v;
}

vec3 &fluid::Particle::c() {
  return _c;
}

double fluid::Particle::r() {
  return _r;
}

double fluid::Particle::m() {
  return _m;
}