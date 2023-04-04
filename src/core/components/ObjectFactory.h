/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : ObjectFactory.h
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "AbstractObject.h"

namespace unreal_fluid {

  class ObjectFactory {
  public:
    enum class Type {
      FluidObject,
      GasObject,
      StaticObject
    };

    static AbstractObject *create(Type type);
  };

} // namespace unreal_fluid

// end of ObjectFactory.h