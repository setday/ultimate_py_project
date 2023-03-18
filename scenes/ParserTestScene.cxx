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
      for (auto & abstractObject : abstractObjects) {
          abstractObject->parse();
          compositor->getRenderer()->RenderAllObjects(abstractObject->getRenderObjects());
      }
  }

  ~ParserTestScene() override = default;
};
