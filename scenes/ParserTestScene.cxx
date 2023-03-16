/***************************************************************
* Copyright (C) 2023
*    HSE SPb (Higher school of economics in Saint-Petersburg).
***************************************************************/

/* PROJECT   : ultimate_py_project
* AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
* FILE NAME : ParserTestScene.cxx
* PURPOSE   : demonstrate how basic fluid simulation works
*
* No part of this file may be changed and used without agreement of
* authors of this project.
*/


#pragma once
#include "../src/core/Core.h"
#include "../src/core/components/AbstractObject.h"
#include "../src/core/components/Scene.h"
#include "../src/core/render/components/material/MaterialFactory.h"
#include "../src/core/render/components/mesh/presets/Sphere.h"

using namespace unreal_fluid;

class ParserTestScene : public Scene {
public:
  render::RenderObject *sphere;
  const compositor::Compositor *compositor;
  AbstractObject *abstractObject;

  explicit ParserTestScene(const compositor::Compositor *compositor) : Scene(compositor),
                                                                       compositor(compositor) {
    abstractObject = new AbstractObject({}); // TODO: which descriptor should we use?
  }

  void Update() override {
    //    abstractObject->update(0.1);
  }

  void Render() override {
    static int timer = 0;
    timer++;

    compositor->GetRenderer()->RenderAllObjects(abstractObject->getRenderObjects());

    if (timer % 200 == 0) {
      compositor->GetRenderer()->GetShaderManager()->ReloadShaders();

      Logger::logInfo("All shaders have been reloaded");
    }
  }

  ~ParserTestScene() override = default;
};
