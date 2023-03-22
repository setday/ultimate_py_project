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
#include "../src/core/physics/solid/sphere/SolidSphere.h"

using namespace unreal_fluid;

class SimpleFluidScene : public Scene {
public:
    double dt = 0.02;

    explicit SimpleFluidScene(const compositor::Compositor *compositor) : Scene(compositor) {
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
        long long t = getMicroseconds();
        compositor->getSimulator()->simulate(dt);
        Logger::logInfo("Simulation time:    ", getMicroseconds() - t);
    }

    void render() override {
        long long t = getMicroseconds();
        for (auto &object: objects) {
            object->parse();
            for (auto renderObject: object->getRenderObjects()) {
                /// TODO this should be done in parse()
                renderObject->shaderProgram = compositor->getRenderer()->GetShaderManager()->GetDefaultProgram();
            }
        }
        Logger::logInfo("Parsing time:       ", getMicroseconds() - t);
        t = getMicroseconds();
        for (auto &object: objects) {
            for (auto &i: object->getRenderObjects()) {
                compositor->getRenderer()->RenderObject(i);
            }
        }
        Logger::logInfo("Rendering time:     ", getMicroseconds() - t);
    }

    ~SimpleFluidScene() override = default;
};
