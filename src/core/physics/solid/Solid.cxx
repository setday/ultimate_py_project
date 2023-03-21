/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Solid.cxx
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "Solid.h"

using namespace unreal_fluid::physics::solid;

unreal_fluid::physics::PhysicalObject::Type Solid::getType() {
  return unreal_fluid::physics::PhysicalObject::Type::SOLID;
}
