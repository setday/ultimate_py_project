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

#include <unordered_map>

#include "IFluidContainer.h"
#include "Cell.h"

///Fluid1Container - Fluid simulating class, which implements FLIP simulation method (ITS NOT ABSOLUTELY RIGHT)
namespace unreal_fluid::fluid {
  class Fluid1Container : IFluidContainer {
  private:
    const double particleSize;
    std::vector<Particle *> particles;
    std::unordered_map<int, std::vector<Particle *>> cells;

  public:
    Fluid1Container(double particleSize);
    ~Fluid1Container();

    void simulate(double dt) override;
    std::vector<Particle *> *getParticles() override;

  private:
    void sort();
    int getCell(Particle particle);
//    void advect(double dt);
    void addExternalForces(double dt) const;
//    void project(double dt);

  };
} // namespace unreal_fluid::fluid

// end of FluidContainer.h