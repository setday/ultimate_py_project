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

#include "FluidContainer.h"

using namespace unreal_fluid::fluid;

std::vector<Particle> *FluidContainer::getParticles() {
  return &particles;
}

void FluidContainer::simulate(double dt) {
  sort();
//  advect(dt);
  addExternalForces(dt);
//  project(dt);
}

void FluidContainer::sort() {
  ceils.clear();
  for (const auto & particle : particles) {
    ceils[getCeil(particle)].push_back(particle);
  }
}

int FluidContainer::getCeil(Particle particle) {
  return int(particle.getX()) + int(particle.getY()) * 2 * particle.radius()
         + int(particle.getZ()) * 4 * particle.radius() * particle.radius();
}

//void FluidContainer::advect(double dt) {
//
//}

void FluidContainer::addExternalForces(double dt) const {
  for (auto particle : particles) {
    particle.advect(dt);
  }
}

//void FluidContainer::project(double dt) {
//
//}