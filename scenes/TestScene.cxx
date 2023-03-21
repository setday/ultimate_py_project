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
  long long timer = 0;

  explicit TestScene(const compositor::Compositor *compositor) : Scene(compositor) {
    objects.push_back(new AbstractObject({}, compositor)); // TODO which descriptor should we use?
    for (auto &abstractObject: objects) {
      compositor->getSimulator()->addPhysicalObject(abstractObject->getPhysicalObject());
    }
    compositor->getRenderer()->camera.setPosition({0, 0, 2});
    compositor->getRenderer()->camera.setDirection({0, 0, -1});
  }

  void update() override {
    timer++;
    static long long update_start_time = getMicroseconds();
    long long time = getMicroseconds();
    compositor->getSimulator()->simulate(dt);
    update_start_time += getMicroseconds() - time;
    if (timer % 30 == 0) {
      Logger::logInfo("Simulation time: ", (getMicroseconds() - update_start_time) / 30);
      update_start_time = getMicroseconds();
    }
  }

  void render() override {
    for (auto &object: objects) {
      object->parse();
    }
    static long long render_start_time = getMicroseconds();
    long long time = getMicroseconds();
    for (auto &object: objects) {
      compositor->getRenderer()->RenderAllObjects(object->getRenderObjects());
    }
    render_start_time += getMicroseconds() - time;
    if (timer % 30 == 0) {
      Logger::logInfo("Rendering time: ", (getMicroseconds() - render_start_time) / 30);
      render_start_time = getMicroseconds();
      timer = 0;
    }
  }

  ~TestScene() override = default;
};
