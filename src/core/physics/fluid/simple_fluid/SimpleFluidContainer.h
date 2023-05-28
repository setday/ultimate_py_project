/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : SimpleFluidContainer.h
 * PURPOSE   : Simple fluid simulation class, which implements ASS collision
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "../../PhysicsDefinitions.h"
#include "../../PhysicsSimulator.h"
#include "../CellsDistributor.h"
#include "../IFluidContainer.h"

namespace unreal_fluid::physics::fluid {
  class SimpleFluidContainer : public IFluidContainer {
  private:
    double k;
    CellsDistributor distributor;

  public:
    explicit SimpleFluidContainer(FluidDescriptor descriptor);
    ~SimpleFluidContainer() override;
    void simulate(double dt) override;

    IPhysicalObject::Type getType() override;
    void *getData() override;

  private:
    /// @brief adds particles
    /// @details adds fluid particles from external sources
    void flows();

    /// @brief changes particles positions
    /// @details for each particle chang its position regarding to its velocity
    void advect(double dt);

    /// @brief change particles velocities
    /// @details adds external forces to change each particle velocity
    void addExternalForces(double dt);

    /// @brief runs through particles interaction stage
    /// @details updates distributor, for each pair collides particles
    void interact();

    void addParticle(vec3 position, vec3 velocity, double radius, double mass);
  };
} // namespace unreal_fluid::physics::fluid

// end of FluidContainer.h
