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

AbstractObject ObjectFactory::create(physics::PhysicsObject *type, render::RenderObject *renderObject) {
  return AbstractObject(type, renderObject);
}
