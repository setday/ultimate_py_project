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

using namespace unreal_fluid;

class ParserTestScene : public Scene {
public:
  const compositor::Compositor *compositor;
  std::vector<AbstractObject *>abstractObjects;
  double dt;

  explicit ParserTestScene(const compositor::Compositor *compositor) : Scene(compositor),
                                                                       compositor(compositor) {
    abstractObjects.push_back(new AbstractObject({})); // TODO: which descriptor should we use?
     for (auto & abstractObject : abstractObjects) {
         compositor->getSimulator()->addPhysObject(const_cast<physics::PhysObject*>(abstractObject->getPhysObject()));
     }
     dt = 0.01;
  }

  void Update() override {
      compositor->getSimulator()->simulate(dt);
  }

  void Render() override {
      static int timer = 0;
      timer++;
      for (auto & abstractObject : abstractObjects) {
          abstractObject->parse();
          auto& ro = abstractObject->getRenderObjects();
          for (int i = 0; i < ro.size(); ++i) {
              /// TODO: this should be done in parse()
              ro[i]->shaderProgram = compositor->getRenderer()->GetShaderManager()->GetDefaultProgram();
          }
          compositor->getRenderer()->RenderAllObjects(abstractObject->getRenderObjects());
      }
      if (timer % 200 == 0) {
          compositor->getRenderer()->GetShaderManager()->ReloadShaders();

          Logger::logInfo("All shaders have been reloaded");
      }
  }

  ~ParserTestScene() override = default;
};
