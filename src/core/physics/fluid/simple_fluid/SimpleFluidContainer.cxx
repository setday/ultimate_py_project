/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : FluidContainer.cxx
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "SimpleFluidContainer.h"

using namespace unreal_fluid::physics::fluid;

SimpleFluidContainer::SimpleFluidContainer(FluidDescriptor descriptor) {
  /// TODO : write constructor implementation
}

void SimpleFluidContainer::addExternalForces(double dt) {
  for (auto &particle: particles) {
    particle.velocity += G * dt;
  }
}

void SimpleFluidContainer::advect(double dt) {
  for (auto &particle: particles) {
    particle.coords += particle.velocity * dt;
  }
}

void SimpleFluidContainer::interact(double dt) {
  CellsDistribution cells(particles);
  std::pair<Particle *, Particle *> p = cells.nextPair(), end = {nullptr, nullptr};
  while (p != end) {
    collide(*p.first, *p.second);
    p = cells.nextPair();
  }
}

void SimpleFluidContainer::simulate(double dt) {
  interact(dt);
  addExternalForces(dt);
  advect(dt);
}

void SimpleFluidContainer::collide(Particle &p1, Particle &p2) {
  vec3 y = p2.coords - p1.coords;

  double push = (p1.r + p2.r - p1.coords.distanceTo(p2.coords)) / 2;
  p2.coords += y * push;
  p1.coords -= y * push;

  double s = -(1 + k) * (p1.velocity.project(y) - p2.velocity.project(y)) * p1.m * p2.m / (p1.m + p2.m);
  p1.velocity += y * (s / p1.m);
  p2.velocity -= y * (s / p2.m);
}

void *SimpleFluidContainer::getData() {
  return &particles;
}

unreal_fluid::physics::PhysObject::Type SimpleFluidContainer::getType() {
  return physics::PhysObject::Type::SIMPLE_FLUID_CONTAINER;
}
