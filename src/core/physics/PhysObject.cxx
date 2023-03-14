/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : PhysObject.cxx
 *
 * No part of this file may be changed and used without agreement of
 * authors of this pressureSolving.
 */

#include "PhysObject.h"

void unreal_fluid::physics::PhysObject::simulate(double dt) {
}

void *unreal_fluid::physics::PhysObject::getData() {
  return nullptr;
}

unreal_fluid::physics::PhysObject::Type unreal_fluid::physics::PhysObject::getType() {
  return unreal_fluid::physics::PhysObject::Type::DEFAULT;
}
