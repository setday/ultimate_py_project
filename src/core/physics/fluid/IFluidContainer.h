/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : FluidContainer.h
 * PURPOSE   : abstract fluid container
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include <vector>
#include "../PhysObject.h"
#include "Particle.h"

namespace unreal_fluid::physics::fluid {

  struct FluidDescriptor {
    std::string name;
    double particleRadius;
    double particleMass;
  };

  class IFluidContainer : public PhysObject {

  protected:
    std::vector<Particle> particles;

  public:
    IFluidContainer() = default;
    virtual ~IFluidContainer() = default;

    std::vector<Particle> *getParticles() {
      return &particles;
    }
  };

} // namespace unreal_fluid::physics::fluid
