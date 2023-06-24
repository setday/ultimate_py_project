/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Gas3DScene.cxx
 * PURPOSE   : scene for basic 2d gas simulation and render
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "../src/core/Core.h"
#include "../src/core/components/AbstractObject.h"
#include "../src/core/components/scene/Scene.h"
#include "../src/core/physics/gas/GasContainer.h"

using namespace unreal_fluid;

class Gas3DScene : public Scene {
public:
  physics::gas::GasContainer *simpleGas;

  explicit Gas3DScene(const compositor::SceneCompositor *compositor) : Scene(compositor) {
    simpleGas = new physics::gas::GasContainer(10, 10, 10, 1000);
    objects.push_back(new AbstractObject(simpleGas));
    compositor->getSimulator()->addPhysicalObject(simpleGas);

    compositor->getRenderer()->camera.setPositionHard({0, 0, 2.2});
    compositor->getRenderer()->camera.setDirection({0, 0, -1});

    dt = 0.5;
  }
};

// end of Gas3DScene.cxx
