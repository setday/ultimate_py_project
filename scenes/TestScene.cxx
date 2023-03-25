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

using namespace unreal_fluid;

class TestScene : public Scene {
public:
  double dt = 0.02;
  utils::Timer timer;

  explicit TestScene(const compositor::Compositor *compositor) : Scene(compositor) {
    auto sphere = new physics::solid::SolidSphere({0,0,0}, 0.3);
    objects.push_back(new AbstractObject(sphere));
    auto simpleFluid = new physics::fluid::SimpleFluidContainer({});
    objects.push_back(new AbstractObject(simpleFluid));
    for (auto &abstractObject: objects) {
      compositor->getSimulator()->addPhysicalObject(abstractObject->getPhysicalObject());
    }
    compositor->getRenderer()->camera.setPosition({0, 0, 2});
    compositor->getRenderer()->camera.setDirection({0, 0, -1});
  }

  void update() override {
    compositor->getSimulator()->simulate(dt);
    for (auto &object: objects) {
      object->parse();
    }

    timer.incrementCounter();

    if (timer.getCounter() == 100) {
      auto &particles = *static_cast<std::vector<physics::fluid::Particle *> *>(((physics::fluid::SimpleFluidContainer *) objects[1]->getPhysicalObject())->getData());
      std::cout << "Number of particles: " << particles.size() << std::endl;
      timer.reset();
    }
  }

  void render() override {
    for (auto &object: objects) {
      compositor->getRenderer()->RenderAllObjects(object->getRenderObjects());
    }
  }

  ~TestScene() override = default;
};
