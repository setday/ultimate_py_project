/***************************************************************
* Copyright (C) 2023
*    HSE SPb (Higher school of economics in Saint-Petersburg).
***************************************************************/

/* PROJECT   : ultimate_py_project
* AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
* FILE NAME : TestScene.cxx
* PURPOSE   : demonstrate how basic fluid simulation works
*
* No part of this file may be changed and used without agreement of
* authors of this project.
*/

#include "../src/core/Core.h"
#include "../src/core/components/AbstractObject.h"
#include "../src/core/components/Scene.h"
#include "../src/utils/Tools.h"

using namespace unreal_fluid;

class TestScene : public Scene {
public:
  double dt = 0.02;

  explicit TestScene(const compositor::Compositor *compositor) : Scene(compositor) {
    objects.push_back(new AbstractObject({})); // TODO which descriptor should we use?
    for (auto &abstractObject: objects) {
      compositor->getSimulator()->addPhysicalObject(abstractObject->getPhysicalObject());
    }
    compositor->getRenderer()->camera.setPosition({0, 0, 2});
    compositor->getRenderer()->camera.setDirection({0, 0, -1});
  }

  void update() override {
    long long start_time = getMicroseconds();
    compositor->getSimulator()->simulate(dt);
    Logger::logInfo("Simulation time: ", getMicroseconds() - start_time);
  }

  void render() override {
    long long start_time = getMicroseconds();
    for (auto &object: objects) {
      object->parse();
      for (auto renderObject: object->getRenderObjects()) {
        /// TODO this should be done in parse()
        renderObject->shaderProgram = compositor->getRenderer()->GetShaderManager()->GetDefaultProgram();
      }
    }
    Logger::logInfo("Parsing time: ", getMicroseconds() - start_time);
    start_time = getMicroseconds();
    for (auto &object: objects) {
      for (auto &i: object->getRenderObjects()) {
        compositor->getRenderer()->RenderObject(i);
      }
    }
    Logger::logInfo("Rendering time:     ", getMicroseconds() - start_time);
  }

  ~TestScene() override = default;
};
