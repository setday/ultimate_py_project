/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : SolidSphere.h
 * PURPOSE   : ISolid class
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "../ISolid.h"

namespace unreal_fluid::physics::solid {
  class SolidSphere : public ISolid {

  private:
    void simulate(double dt) override{};

  public:
    double radius;

    SolidSphere(vec3 position, double radius);

    /// Get type of object
    /// @return type of object
    Type getType() override;
    /// Get data stored in a physical container
    /// @return data stored in a physical container
    void *getData() override;
  };
} // namespace unreal_fluid::physics::solid

// end of SolidSphere.h
