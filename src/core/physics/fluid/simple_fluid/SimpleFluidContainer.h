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

#include "../../PhysicsDefinitions.h"
#include "../IFluidContainer.h"
#include "CellsDistribution.h"

namespace unreal_fluid::physics::fluid {
  /// SimpleFluidContainer - Fluid simulating class, which implements ASS collision
  class SimpleFluidContainer : public IFluidContainer {
  private:
    double k;

  public:
    explicit SimpleFluidContainer(FluidDescriptor descriptor);
    ~SimpleFluidContainer() override;
    void simulate(double dt) override;

    unreal_fluid::physics::PhysObject::Type getType() override;
    void *getData() override;

  private:
    void collide(Particle &p1, Particle &p2);
    void advect(double dt);
    void addExternalForces(double dt);
    void interact(double dt);
  };
} // namespace unreal_fluid::physics::fluid

// end of FluidContainer.h
