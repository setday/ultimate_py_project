/***************************************************************
* Copyright (C) 2023
*    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
*    HSE SPb (Higher school of economics in Saint-Petersburg).
***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : SceneLoader.cxx
 * FILE AUTHORS            : Serkov Alexander.
 * PURPOSE                 : Class that realizes render of scene.
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#include "../src/core/Core.h"
#include "../src/core/components/scene/IScene.h"

#include "Control.cxx"
#include "TestScene.cxx"
#include "GLTestScene.cxx"
#include "MeshScene.cxx"
#include "ClTestScene.cxx"
#include "d5a9fde3c505f2c80d6d548c3c9a93c5.cxx"

using namespace unreal_fluid;

class SceneLoader : public IScene {
public:
  explicit SceneLoader(compositor::SceneCompositor * compositor) {
    Logger::logInfo("Loading scenes...");

    compositor->loadScene<Control>();
    compositor->loadScene<d5a9fde3c505f2c80d6d548c3c9a93c5>();

    Logger::logInfo("Scenes loaded!");

    compositor->unloadScene(this);
  }

  void update() override {
    // There is no need to update this scene because it is only for loading other scenes and then unloading itself.
  }
  void render() override {
    // There is no need to render this scene because it is only for loading other scenes and then unloading itself.
  }
};

// end of SceneLoader.cxx
