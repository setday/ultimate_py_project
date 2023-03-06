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

#include "Fluid1Container.h"

using namespace unreal_fluid::fluid;

Fluid1Container::Fluid1Container(double particleSize) : particleSize(particleSize) {
};

std::vector<Particle *> *Fluid1Container::getParticles() {
  return &particles;
}

void Fluid1Container::simulate(double dt) {
  sort();
//  advect(dt);
  addExternalForces(dt);
//  project(dt);
}

void Fluid1Container::sort() {
  cells.clear();
  for (const auto &particle: particles) {
    cells[getCell(*particle)].push_back(particle);
  }
}

int Fluid1Container::getCell(Particle particle) {
  /// TODO: return what's needed
  return 0;
}

//void SimpleFluidContainer::advect(double dt) {
//
//}

void Fluid1Container::addExternalForces(double dt) const {
  for (auto particle: particles) {
    particle->advect(dt);
  }
}

//void SimpleFluidContainer::project(double dt) {
//
//}