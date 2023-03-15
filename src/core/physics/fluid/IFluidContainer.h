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

  struct fluidDescriptor {
    std::string name;
    double particleRadius;
    double particleMass;
  };

  class IFluidContainer : PhysObject {

  protected:
    std::vector<Particle> particles;

  public:
    IFluidContainer() = default;
    virtual ~IFluidContainer() = default;
    virtual std::vector<Particle> *getParticles() = 0;
  };
} // namespace unreal_fluid::physics::fluid
