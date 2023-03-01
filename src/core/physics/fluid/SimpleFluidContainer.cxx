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

using namespace unreal_fluid::fluid;

std::vector<Particle> *SimpleFluidContainer::getParticles() {
  return &particles;
}

void SimpleFluidContainer::simulate(double dt) {
  sort();
//  advect(dt);
  addExternalForces(dt);
//  project(dt);
}

void SimpleFluidContainer::sort() {
  ceils.clear();
  for (const auto &particle: particles) {
    ceils[getCell(particle)].push_back(particle);
  }
}

int SimpleFluidContainer::getCell(Particle particle) {
  return int(particle.getX()) + int(particle.getY()) * 2 * particleSize
         + int(particle.getZ()) * 4 * particleSize * particleSize;
}

//void SimpleFluidContainer::advect(double dt) {
//
//}

void SimpleFluidContainer::addExternalForces(double dt) const {
  for (auto particle: particles) {
    particle.advect(dt);
  }
}

//void SimpleFluidContainer::project(double dt) {
//
//}