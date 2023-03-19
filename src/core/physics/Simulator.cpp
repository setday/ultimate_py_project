/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Simulator.cpp
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "Simulator.h"

using namespace unreal_fluid::physics;

void Simulator::addPhysObject(PhysObject *physObject) {
  physObjects.push_back(physObject);
}

void Simulator::simulate(double dt) {
    /// TODO: simulate solids and fluids
    for (auto & physObject : physObjects) {
        physObject->simulate(dt);
    }
}

void Simulator::clearData() {
  physObjects.clear();
}

// end of Simulator.cpp
