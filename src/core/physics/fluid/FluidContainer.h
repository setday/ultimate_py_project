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
 * authors of this project.
 */

#pragma once
#include "IFluidContainer.h"
#include "Ceil.h"
#include <unordered_map>

namespace unreal_fluid::fluid {
  class FluidContainer : IFluidContainer {
  private:
    std::vector<Particle> particles;
    std::unordered_map<int, std::vector<Particle>> ceils;

  public:
    FluidContainer();
    ~FluidContainer();

    void simulate(double dt) override;
    std::vector<Particle> *getParticles() override;

  private:
    void sort();
    int getCeil(Particle particle);
//    void advect(double dt);
    void addExternalForces(double dt) const;
//    void project(double dt);

  };
} // namespace unreal_fluid::fluid

// end of FluidContainer.h