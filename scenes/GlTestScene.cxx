/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : GLTestScene.cxx
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include <cmath>
#include <unistd.h>

#include "../src/core/Core.h"
#include "../src/core/components/Scene.h"
#include "../src/core/render/components/material/MaterialFactory.h"
#include "../src/core/render/components/mesh/presets/Sphere.h"
#include "../src/core/render/components/mesh/presets/Plane.h"
#include "../src/core/render/components/mesh/presets/Cube.h"

using namespace unreal_fluid;

class GlTestScene : public Scene {
public:
  render::RenderObject *sphere;
  render::RenderObject *plane;
  render::RenderObject *cube;
  const compositor::Compositor *compositor;
  utils::Timer timer;

  explicit GlTestScene(compositor::Compositor const * compositor) : Scene(compositor), compositor(compositor) {
    sphere = new render::RenderObject();
    sphere->mesh = render::mesh::Sphere(.5f, 50, 50);
    sphere->modelMatrix =
            mat4::rotation(0.f, {0.f, 0.f, 1.f}) *
            mat4::translation({-.75f, 0.f, -5.f});
    sphere->material = render::material::MaterialFactory::createMaterial(
            render::material::MaterialFactory::MaterialType::WATTER
            );

    plane = new render::RenderObject();
    plane->mesh = render::mesh::Plane(2.5f, 2.5f, 10, 10);
    plane->modelMatrix =
            mat4::rotation(0.f, {0.f, 0.f, 1.f}) *
            mat4::translation({0.f, -1.f, -5.f});
    plane->material = render::material::MaterialFactory::createMaterial(
            render::material::MaterialFactory::MaterialType::CYAN_PLASTIC
    );

    cube = new render::RenderObject();
    cube->mesh = render::mesh::Cube(.5f);
    cube->modelMatrix =
            mat4::rotation(0.f, {0.f, 0.f, 1.f}) *
            mat4::translation({.75f, 0.f, -5.f});
    cube->material = render::material::MaterialFactory::createMaterial(
            render::material::MaterialFactory::MaterialType::RUBY
    );
  }

  void Update() override {
    auto time = utils::Timer::getCurrentTimeAsDouble();

    sphere->modelMatrix =
            mat4::rotationY(std::sin(time / 10) * 100) *
            mat4::translation({-.75f, 0.f, -5.f});

    cube->modelMatrix =
            mat4::rotationY(-std::sin(time / 10) * 100) *
            mat4::translation({.75f, 0.f, -5.f});
  }

  void Render() override {
    static int timer = 0;
    timer++;

    compositor->GetRenderer()->RenderAllObjects({cube, sphere, plane});

    if (timer % 200 == 0) {
      // compositor->GetRenderer()->GetShaderManager()->ReloadShaders();

      // Logger::logInfo("All shaders have been reloaded");
    }
  }

  ~GlTestScene() override = default;
};

// end of GLTestScene.cxx
