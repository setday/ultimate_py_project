/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : PhysicalObject.h
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include <vector>

namespace unreal_fluid::physics {
  class PhysicalObject {
  public:
    enum class Type {
        SIMPLE_FLUID_CONTAINER,
        SOLID
    };

    virtual ~PhysicalObject() = default;

    virtual void simulate(double dt) = 0;

    virtual Type getType() = 0;
    virtual void *getData() = 0;
  };
} // namespace unreal_fluid::physics

// end of PhysicalObject.h
