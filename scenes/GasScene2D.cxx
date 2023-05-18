/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : GasScene2D.cxx
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "../src/core/Core.h"
#include "../src/core/components/AbstractObject.h"
#include "../src/core/components/scene/Scene.h"
#include "../src/core/physics/gas/GasContainer2D.h"

using namespace unreal_fluid;

class GasScene2D : public Scene {
public:

  explicit GasScene2D(const compositor::SceneCompositor *compositor) : Scene(compositor) {
    auto sphere = new physics::solid::SolidSphere({0, 0, 0}, 0.3);
    objects.push_back(new AbstractObject(sphere));

    auto simpleFluid = new physics::fluid::SimpleFluidContainer({});
    objects.push_back(new AbstractObject(simpleFluid));

    for (auto &abstractObject: objects) {
      compositor->getSimulator()->addPhysicalObject(abstractObject->getPhysicalObject());
    }

    compositor->getRenderer()->camera.setPosition({0, 0, 2});
    compositor->getRenderer()->camera.setDirection({0, 0, -1});
  }
};
