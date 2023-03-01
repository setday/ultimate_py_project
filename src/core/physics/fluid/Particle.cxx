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
#include "../../physics/PhysicsDefs.h"

fluid::Particle::Particle(const vec3 &velocity, const vec3 &position, double radius, double mass, void *metaData) : _velocity(velocity),
                                                                                                                    _position(position),
                                                                                                                    _radius(radius),
                                                                                                                    _mass(mass),
                                                                                                                    metaData(metaData) {}

double fluid::Particle::getX() const {
  return _position.x;
}

double fluid::Particle::getY() const {
  return _position.y;
}

double fluid::Particle::getZ() const {
  return _position.z;
}

double fluid::Particle::radius() const {
  return _radius;
}

void fluid::Particle::advect(double dt) {
  _velocity += dt * physics::G;
}
