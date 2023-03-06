/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : FluidContainer.h
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this pressureSolving.
 */

#pragma once

#include <unordered_map>

#include "IFluidContainer.h"

///Fluid1Container - Fluid simulating class, which implements FLIP simulation method (ITS NOT ABSOLUTELY RIGHT)
namespace unreal_fluid::fluid {
  class Fluid1Container : IFluidContainer {
  private:
    std::unordered_map<int, std::vector<Particle *>> cells;
    void collide(Particle& p1, Particle& p2);

  public:
    Fluid1Container();
    ~Fluid1Container();
    void simulate(double dt) override;
    std::vector<Particle> *getParticles() override;
  private:
    void advect(double dt);
    void addExternalForces(double dt);
    void interact(double dt);
  };
} // namespace unreal_fluid::fluid

// end of FluidContainer.h