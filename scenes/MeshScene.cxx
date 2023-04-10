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
#include "../src/core/components/Scene.h"
#include "../src/core/physics/solid/mesh/SolidMesh.h"

using namespace unreal_fluid;

class MeshScene : public Scene {
public:
 explicit MeshScene(const compositor::Compositor *compositor) : Scene(compositor) {
   using namespace physics::solid;
   Triangle t1{{0, 0, 0}, {1, 1, 1}, {1, 2, 3}}, t2{{0, 0, 0}, {1, 1, 1}, {1, 2, 3}},
           t3{{0, 0, 0}, {1, 1, 1}, {1, 2, 3}};
   std::vector<Triangle> triangles{t1, t2, t3};
   auto solidMesh = new physics::solid::SolidMesh(triangles);
   objects.push_back(new AbstractObject(solidMesh));
   for (auto &abstractObject: objects) {
     compositor->getSimulator()->addPhysicalObject(abstractObject->getPhysicalObject());
   }
   compositor->getRenderer()->camera.setPosition({0, 0, 2});
   compositor->getRenderer()->camera.setDirection({0, 0, -1});
 }

 void update() override {
   for (auto &object: objects) {
     object->parse();
   }
 }

 void render() override {
   for (auto &object: objects) {
     compositor->getRenderer()->RenderAllObjects(object->getRenderObjects());
   }
 }

 ~MeshScene() override = default;
};
