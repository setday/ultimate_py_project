/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : IPhysicalObject.h
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include <vector>

#include "../../Definitions.h"

namespace unreal_fluid::physics {
  class Simulator;

  class IPhysicalObject {
    friend class Simulator;

  public:
    enum class Type {
      SIMPLE_FLUID_CONTAINER,
      SOLID_SPHERE,
      SOLID_MESH,
      PLANE
    };

    virtual ~IPhysicalObject() = default;

    /// @brief returns type of an accessor
    virtual Type getType() = 0;

    /// @brief returns data stored in a physical container
    virtual void *getData() = 0;

  private:
    virtual void simulate(double dt) = 0;
  };
} // namespace unreal_fluid::physics
