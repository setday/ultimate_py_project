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
#include "../src/core/components/scene/Scene.h"
#include "../src/core/physics/solid/mesh/Plane.h"
#include "../src/core/physics/solid/mesh/SolidMesh.h"
#include "../src/core/physics/solid/sphere/SolidSphere.h"
#include "../src/core/physics/fluid/advanced_fluid/AdvancedFluidContainer.h"

using namespace unreal_fluid;

class TestScene : public Scene {
public:
  explicit TestScene(const compositor::SceneCompositor *compositor) : Scene(compositor) {
    auto sphere1 = new physics::solid::SolidSphere({0, 0, 0}, 0.3);
    objects.push_back(new AbstractObject(sphere1));

    auto sphere2 = new physics::solid::SolidSphere({0.5, -0.5, 0}, 0.3);
    objects.push_back(new AbstractObject(sphere2));

    auto fluid = new physics::fluid::AdvancedFluidContainer({});
    objects.push_back(new AbstractObject(fluid));

    auto plane = new physics::solid::Plane(2, 2, {0, -1, 0}, {0, 1, 0});
    objects.push_back(new AbstractObject(plane));

    for (auto &abstractObject: objects) {
      if (abstractObject->getPhysicalObject())
        compositor->getSimulator()->addPhysicalObject(abstractObject->getPhysicalObject());
    }

    compositor->getRenderer()->camera.setPositionHard({0, 1, 2});
    compositor->getRenderer()->camera.setDirection({0, 0, -1});
  }
};
