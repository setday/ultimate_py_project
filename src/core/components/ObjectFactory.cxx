/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : ObjectFactory.cxx
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "ObjectFactory.h"

using namespace unreal_fluid;

AbstractObject *ObjectFactory::Create(Type type) {
  auto *object = new AbstractObject();

  object->_renderObject = new render::RenderObject();
  switch (type) {
    case Type::FluidObject:
      // object->physicsObject = new physics::FluidObject();
      //      break;
    case Type::GasObject:
      // object->physicsObject = new physics::GasObject();
      //    break;
    case Type::StaticObject:
      // object->physicsObject = new physics::StaticObject();
      break;
  }

  return object;
}
