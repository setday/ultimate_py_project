/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Simulator.cxx
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "Simulator.h"

using namespace unreal_fluid::physics;

void Simulator::addPhysicalObject(PhysicalObject *physicalObject) {
  _physicalObjects.push_back(physicalObject);
}

void Simulator::simulate(double dt) {
  /// TODO simulate interaction between solids and fluids
  for (auto &physObject: _physicalObjects) {
    physObject->simulate(dt);
  }
}

void Simulator::clearData() {
  _physicalObjects.clear();
}

// end of Simulator.cpp
