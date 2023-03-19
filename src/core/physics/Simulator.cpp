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

void unreal_fluid::physics::Simulator::addPhysObject(unreal_fluid::physics::PhysObject *physObject) {
    physObjects.push_back(physObject);
}

void unreal_fluid::physics::Simulator::simulate(double dt) {
    /// TODO: simulate solids and fluids
    for (auto & physObject : physObjects) {
        physObject->simulate(dt);
    }
}

void unreal_fluid::physics::Simulator::clearData() {
    physObjects.clear();
}

// end of Simulator.cpp
