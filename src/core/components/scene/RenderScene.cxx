/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : RenderScene.cxx
 * PURPOSE   : Class that realizes render of scene.
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "RenderScene.h"

using namespace unreal_fluid;

void RenderScene::render() {
  for (const AbstractObject *object : objects) {
    compositor->getRenderer()->RenderObject(object->getRenderObject());
  }
}

// end of RenderScene.cxx
