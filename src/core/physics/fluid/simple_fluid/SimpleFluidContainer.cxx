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
  auto particle = new Particle();
  particle->position = {1.5, 0, 0};
  particle->mass = 1;
  particle->radius = 0.5;
  particles.push_back(particle);
  /// TODO : write constructor implementation
}

SimpleFluidContainer::~SimpleFluidContainer() {
  for (auto &particle: particles) {
    delete particle;
  }
}

void SimpleFluidContainer::addExternalForces(double dt) {
  for (auto &particle: particles) {
    particle->velocity += G * dt;
  }
}

void SimpleFluidContainer::advect(double dt) {
  for (auto particle: particles) {
    particle->position += particle->velocity * dt;
  }
}

void SimpleFluidContainer::interact(double dt) {
  CellsDistribution cells(particles);
  std::pair<Particle *, Particle *> p = cells.nextPair();
  while (p != CellsDistribution::terminator) {
    collide(p.first, p.second);
    p = cells.nextPair();
  }
}

void SimpleFluidContainer::simulate(double dt) {
  /// TODO addParticle() method should be used

  auto particle = new Particle();
  particle->position = {0, 0, 0};
  particle->mass = 1;
  particle->radius = 0.02;
  particle->velocity = {3, 0, 0};
  particles.push_back(particle);

  interact(dt);
  addExternalForces(dt);
  advect(dt);
}

void SimpleFluidContainer::collide(Particle *p1, Particle *p2) const {
  vec3 positionDiff = p1->position - p2->position;

  if (positionDiff.len2() == 0)
    return;

  double distance = positionDiff.len();
  double pushValue = (p1->radius + p2->radius - distance) / 2;
  vec3 pushVector = positionDiff * pushValue / distance;

  if (pushValue < 0)
    return;

  p1->position += pushVector;
  p2->position -= pushVector;

  double momentumLength =
          -(1 + k) *
          (p1->velocity.project(positionDiff) - p2->velocity.project(positionDiff)) /
          (p1->mass + p2->mass);
  vec3 momentum = positionDiff * momentumLength / distance;

  p1->velocity += momentum * p1->mass;
  p2->velocity -= momentum * p2->mass;
}

void *SimpleFluidContainer::getData() {
  return &particles;
}

unreal_fluid::physics::PhysicalObject::Type SimpleFluidContainer::getType() {
  return physics::PhysicalObject::Type::SIMPLE_FLUID_CONTAINER;
}

// end of FluidContainer.cxx
