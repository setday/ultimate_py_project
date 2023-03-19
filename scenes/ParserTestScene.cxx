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

#include "../src/core/Core.h"
#include "../src/core/components/AbstractObject.h"
#include "../src/core/components/Scene.h"

using namespace unreal_fluid;

class ParserTestScene : public Scene {
public:
  double dt = 0.01;

  explicit ParserTestScene(const compositor::Compositor *compositor) : Scene(compositor) {
    objects.push_back(new AbstractObject({})); // TODO which descriptor should we use?
     for (auto & abstractObject : objects) {
       compositor->getSimulator()->addPhysicalObject(abstractObject->getPhysicalObject());
     }
  }

  void update() override {
      compositor->getSimulator()->simulate(dt);
  }

  void render() override {
      for (auto & object : objects) {
          object->parse();
          for (auto renderObject : object->getRenderObjects()) {
              /// TODO this should be done in parse()
              renderObject->shaderProgram = compositor->getRenderer()->GetShaderManager()->GetDefaultProgram();
          }
          compositor->getRenderer()->RenderAllObjects(object->getRenderObjects());
      }
  }

  ~ParserTestScene() override = default;
};
