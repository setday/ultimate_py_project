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
        : _velocity(velocity),
          _position(position),
          _radius(radius),
          _mass(mass),
          metaData(metaData) {}


vec3 &fluid::Particle::getVelocity() {
  return _velocity;
}

vec3 &fluid::Particle::getPosition() {
  return _position;
}

double fluid::Particle::getRadius() {
  return _radius;
}

double fluid::Particle::getMass() {
  return _mass;
}