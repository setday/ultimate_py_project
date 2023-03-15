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
      DEFAULT,
      FLUID1_CONTAINER
    };

    virtual void simulate(double dt);

  public:
    virtual Type getType();
    virtual void *getData();
  };
} // namespace unreal_fluid::physics

// end of PhysObject.h
