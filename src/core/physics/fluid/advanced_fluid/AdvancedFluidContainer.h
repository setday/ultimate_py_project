/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : AdvancedFluidContainer.h
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "../../PhysicsDefinitions.h"
#include "../CellsDistributor.h"
#include "../IFluidContainer.h"
#include "InteractionSolver.h"

namespace unreal_fluid::physics::fluid {
  class AdvancedFluidContainer : public IFluidContainer {
  private:
    double k;
    InteractionSolver interactionSolver;

  public:
    explicit AdvancedFluidContainer(FluidDescriptor descriptor);
    ~AdvancedFluidContainer() override;
    void simulate(double dt) override;
    Type getType() override;
    void *getData() override;

  private:
    void flows();
    void advect(double dt);
    void addExternalForces(double dt);
    void interact();
    void addParticle(vec3 position, vec3 velocity, double radius, double mass);
  };
} // namespace unreal_fluid::physics::fluid

// end of AdvancedFluidContainer.h