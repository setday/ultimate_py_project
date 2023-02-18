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
#include "../physics/PhysicsObject.h"
#include "AbstractObject.h"

using namespace unreal_fluid;

class ObjectFactory {
public:
  enum class Type {
    FluidObject,
    GasObject,
    StaticObject
  };

  AbstractObject *create(Type type);
};

// end of ObjectFactory.h