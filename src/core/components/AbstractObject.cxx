/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : AbstractObject.cxx
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "AbstractObject.h"

using namespace unreal_fluid;

AbstractObject::~AbstractObject() {
  // delete _physicsObject;
  delete _renderObject;
}

physics::PhysicsObject *AbstractObject::getPhysicsObject() const {
  return _physicsObject;
}

render::RenderObject *AbstractObject::getRenderObject() const {
  return _renderObject;
}

// end of AbstractObject.cxx
