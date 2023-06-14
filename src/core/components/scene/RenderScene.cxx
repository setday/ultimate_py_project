/***************************************************************
* Copyright (C) 2023
*    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
*    HSE SPb (Higher school of economics in Saint-Petersburg).
***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : RenderScene.cxx
 * FILE AUTHORS            : Serkov Alexander.
 * PURPOSE                 : Class that realizes render of scene.
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#include "RenderScene.h"

using namespace unreal_fluid;

void RenderScene::render() {
  for (AbstractObject *object : objects) {
    compositor->getRenderer()->renderObjects(object->getRenderObjects());
  }
}

// end of RenderScene.cxx
