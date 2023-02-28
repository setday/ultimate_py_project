//
// Created by danie on 2/22/2023.
//

#include "Particle.h"

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
  _velocity.y -= dt * math::G;
}
