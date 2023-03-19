/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : PhysObject.h
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include <vector>

namespace unreal_fluid::physics {


  class PhysObject {

  public:
    enum class Type {
        SIMPLE_FLUID_CONTAINER,
        SOLID
    };

    virtual void simulate(double dt) = 0;

  public:
    virtual Type getType() = 0;
    virtual void *getData() = 0;
  };
} // namespace unreal_fluid::physics

// end of PhysObject.h
