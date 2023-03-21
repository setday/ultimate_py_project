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
#include "../IPhysicalObject.h"
#include "Particle.h"

namespace unreal_fluid::physics::fluid {

  struct FluidDescriptor {
    double particleRadius;
    double particleMass;
  };

  class IFluidContainer : public IPhysicalObject {
  protected:
    std::vector<Particle *> particles;

  public:
    IFluidContainer() = default;
    ~IFluidContainer() override = default;
  };

} // namespace unreal_fluid::physics::fluid

// end of FluidContainer.h
