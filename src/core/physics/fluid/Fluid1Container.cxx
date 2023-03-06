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
 * authors of this pressureSolving.
 */

#include "Fluid1Container.h"

using namespace unreal_fluid::fluid;

Fluid1Container::Fluid1Container(){
  //init fluid
};

Fluid1Container::~Fluid1Container(){
  //destroy fluid
};

std::vector<Particle *> *Fluid1Container::getParticles() {
  return &particles;
}

void Fluid1Container::addExternalForces(double dt){

}

void Fluid1Container::advect(double dt) {

}

void Fluid1Container::interact(double dt) {

}

void Fluid1Container::simulate(double dt) {
  interact(dt);
  addExternalForces(dt);
  advect(dt);
}