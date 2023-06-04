/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : CanyonScene.cxx
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "../src/core/Core.h"
#include "../src/core/components/AbstractObject.h"
#include "../src/core/components/scene/Scene.h"
#include "../src/core/physics/fluid/advanced_fluid/AdvancedFluidContainer.h"
#include "../src/core/physics/solid/mesh/Mesh.h"
#include "../src/core/components/Parser.h"

using namespace unreal_fluid;
using namespace physics;
using namespace render;

class CanyonScene : public Scene {
public:
    explicit CanyonScene(const compositor::SceneCompositor *compositor) : Scene(compositor) {

        dt = 0.003;

        auto fluid = new fluid::AdvancedFluidContainer({});
        objects.push_back(new AbstractObject(fluid));

        mesh::BasicMesh sourceMesh;
        //TODO load vertexes from file
        auto triangles = physics::Parser::parseRenderMesh(sourceMesh);
        auto mesh = new solid::Mesh(triangles);

        objects.push_back(new AbstractObject(mesh));

        for (auto &abstractObject: objects) {
            compositor->getSimulator()->addPhysicalObject(abstractObject->getPhysicalObject());
        }

        compositor->getRenderer()->camera.setPosition({0, 1, 0});
        compositor->getRenderer()->camera.setDirection({0, 0, -1});
    }
};
