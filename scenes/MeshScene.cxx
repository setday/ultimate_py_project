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
#include "../src/core/physics/fluid/advanced_fluid/AdvancedFluidContainer.h"
#include "../src/core/physics/solid/mesh/SolidMesh.h"
using namespace unreal_fluid;

class MeshScene : public Scene {
public:
  explicit MeshScene(const compositor::SceneCompositor *compositor) : Scene(compositor) {
    using namespace physics;

    dt = 0.003;

    auto simpleFluid = new fluid::AdvancedFluidContainer({});
    objects.push_back(new AbstractObject(simpleFluid));

//    solid::Triangle t1{{0.5, 0, 0}, {-0.5, 0, -0.5}, {-0.1, 0, 0.5}};
    solid::Triangle t1{{1, 1, 0}, {-0.5, 1, -0.5}, {0, 0, 1}};

    auto triangles = new std::vector<solid::Triangle>{t1};
    auto solidMesh = new solid::SolidMesh(*triangles);

    objects.push_back(new AbstractObject(solidMesh));

    for (auto &abstractObject: objects) {
      compositor->getSimulator()->addPhysicalObject(abstractObject->getPhysicalObject());
    }

    compositor->getRenderer()->camera.setPosition({0, 1, 0});
    compositor->getRenderer()->camera.setDirection({0, 0, -1});
  }
};
