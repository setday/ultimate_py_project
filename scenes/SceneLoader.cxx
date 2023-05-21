/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : SceneLoader.cxx
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "../src/core/Core.h"
#include "../src/core/components/scene/IScene.h"

#include "Control.cxx"
#include "TestScene.cxx"
#include "GLTestScene.cxx"
#include "MeshScene.cxx"
#include "GasScene2D.cxx"

using namespace unreal_fluid;

class SceneLoader : public IScene {
public:
  explicit SceneLoader(compositor::SceneCompositor * compositor) {
    Logger::logInfo("Loading scenes...");

    compositor->loadScene<Control>();
    compositor->loadScene<GasScene2D>();

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
