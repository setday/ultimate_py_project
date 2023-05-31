/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : AdvancedFluidContainer.cxx
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "AdvancedFluidContainer.h"
#include <random>

using namespace unreal_fluid::physics::fluid;

AdvancedFluidContainer::AdvancedFluidContainer(FluidDescriptor descriptor) {
  k = 0.1;
  for (int j = 0; j < 1000; ++j) {
    for (int i = 0; i < 4; ++i) {
      addParticle({double(rand() % 100) / 10000, 1 + j * 0.07, double(rand() % 100) / 10000}, {0, -1, 0}, 0.03, 2);
    }
  }
  //addParticle({double(rand() % 100) / 100000, 1, double(rand() % 100) / 100000}, {0.2, 0, 0}, 0.1, 2);
}

AdvancedFluidContainer::~AdvancedFluidContainer() {
  for (auto &particle: particles)
    delete particle;
}

unreal_fluid::physics::IPhysicalObject::Type AdvancedFluidContainer::getType() {
  return Type::FLUID_CONTAINER_ADVANCED;
}

void *AdvancedFluidContainer::getData() {
  return &particles;
}

void AdvancedFluidContainer::simulate(double dt) {
  //flows();
  interact();
  addExternalForces(dt);
  advect(dt);
}

void AdvancedFluidContainer::addParticle(vec3 position, vec3 velocity, double radius, double mass) {
  auto particle = new Particle;
  particle->position = position;
  particle->mass = mass;
  particle->radius = radius;
  particle->velocity = velocity;
  particles.push_back(particle);
}

void AdvancedFluidContainer::flows() {
  addParticle({double(rand() % 100) / 100000, 1, double(rand() % 100) / 100000}, {0, 0, 0}, 0.05, 2);
}

void AdvancedFluidContainer::interact() {
  interactionSolver.interact(particles, k);
}

void AdvancedFluidContainer::addExternalForces(double dt) {
  for (auto &particle: particles) {
    particle->velocity += G * dt;
  }
}

void AdvancedFluidContainer::advect(double dt) {
  for (auto &particle: particles) {
    particle->velocity += particle->a * dt;
    particle->a = 0;
    particle->position += particle->velocity * dt;
  }
}
