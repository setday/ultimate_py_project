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
#include "../src/core/physics/solid/mesh/SolidMesh.h"
#include "../src/core/render/components/material/MaterialPresets.h"
#include "../src/core/render/components/mesh/presets/Plane.h"

using namespace unreal_fluid;

class TestScene : public Scene {
public:

  explicit TestScene(const compositor::SceneCompositor *compositor) : Scene(compositor) {
    auto sphere1 = new physics::solid::SolidSphere({0, 0, 0}, 0.3);
    objects.push_back(new AbstractObject(sphere1));

    auto sphere2 = new physics::solid::SolidSphere({0.3, -0.5, 0.3}, 0.3);
    objects.push_back(new AbstractObject(sphere2));

    auto simpleFluid = new physics::fluid::SimpleFluidContainer({});
    objects.push_back(new AbstractObject(simpleFluid));

    auto plane = new render::RenderObject;
    plane->mesh = render::mesh::Plane(500, 500);
    plane->material = render::material::Ruby();
    plane->material.diffuseColor = {0.08627f, 0.819607f, 0.20392f};
    plane->modelMatrix = mat4::translation({0, -1, 0});

//    auto plane2 = new render::RenderObject;
//    plane2->mesh = render::mesh::Plane(10, 10);
//    plane2->material = render::material::Basi;
//    plane2->modelMatrix = mat4::rotationX((float) math::PI_2) * mat4::translation({2, 0, 0});

    //    auto plane3 = new render::RenderObject;
    //    plane3->mesh = render::mesh::Plane(5, 5);
    //    plane3->material = render::material::Obsidian();
    //    plane3->modelMatrix = mat4::translation({-1, 0, 0});

    for (auto &abstractObject: objects) {
      if (abstractObject->getPhysicalObject() != nullptr)
        compositor->getSimulator()->addPhysicalObject(abstractObject->getPhysicalObject());
    }

    objects.push_back(new AbstractObject(nullptr, {plane})); //, plane3}));

    compositor->getRenderer()->camera.setPositionHard({0, 0, 3});
    compositor->getRenderer()->camera.setDirection({0, 0, -1});
    //compositor->getRenderer()->camera.setPositionHard({0, 1, 2});
    //compositor->getRenderer()->camera.setDirection({0, 0, -1});
  }
};
