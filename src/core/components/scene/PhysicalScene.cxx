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
  compositor->getSimulator()->simulate(dt);
  for (auto &object: objects) {
    object->parse();
  }
}

// end of PhysicalScene.cxx
