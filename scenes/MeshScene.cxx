/***************************************************************
* Copyright (C) 2023
*    HSE SPb (Higher school of economics in Saint-Petersburg).
***************************************************************/

/* PROJECT   : ultimate_py_project
* AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
* FILE NAME : MeshScene.cxx
* PURPOSE   : ${PURPOSE}
*
* No part of this file may be changed and used without agreement of
* authors of this project.
*/

#include "../src/core/Core.h"
#include "../src/core/components/AbstractObject.h"
#include "../src/core/components/scene/Scene.h"
#include "../src/core/physics/solid/mesh/SolidMesh.h"

using namespace unreal_fluid;

class MeshScene : public Scene {
public:
  explicit MeshScene(const compositor::SceneCompositor *compositor) : Scene(compositor) {
    using namespace physics::solid;

    auto simpleFluid = new physics::fluid::SimpleFluidContainer({});
    objects.push_back(new AbstractObject(simpleFluid));

    Triangle t1{{0.5, 0, 0}, {-0.5, 0, -0.5}, {-0.5, 0, 0.5}};

    auto triangles = new std::vector<Triangle>{t1};
    auto solidMesh = new SolidMesh(*triangles);

    objects.push_back(new AbstractObject(solidMesh));

    for (auto &abstractObject: objects) {
      compositor->getSimulator()->addPhysicalObject(abstractObject->getPhysicalObject());
    }

    compositor->getRenderer()->camera.setPosition({0, 0, 2});
    compositor->getRenderer()->camera.setDirection({0, 0, -1});
  }
};
