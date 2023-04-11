/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : PhysicalScene.cxx
 * PURPOSE   : Class that realizes update of physical scene.
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "PhysicalScene.h"

using namespace unreal_fluid;

void PhysicalScene::update() {
  for (auto object : objects) {
    // object->update();
    /// TODO: add parser and updating order
  }
}

// end of PhysicalScene.cxx
