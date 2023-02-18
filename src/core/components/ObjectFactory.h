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
#include "..//physics//PhysicsObject.h"

using namespace unreal_fluid;

class ObjectFactory {

  friend class AbstractObject;

  enum class object_type{FluidObject, GasObject, StaticObject};
  AbstractObject create(physics::PhysicsObject *type, render::RenderObject *renderObject);
};

// end of ObjectFactory.h