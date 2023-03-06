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

#include "../src/core/Core.h"
#include "../src/core/components/Scene.h"
#include "../src/core/render/components/meshes/Sphere.h"
#include "../src/core/render/components/meshes/Plane.h"

using namespace unreal_fluid;

class GlTestScene : public Scene {
public:
  render::RenderObject *sphere;
  render::RenderObject *plane;
  const compositor::Compositor *compositor;
  const render::Shader *shader;

  explicit GlTestScene(compositor::Compositor const * compositor) : Scene(compositor), compositor(compositor) {
    sphere = new render::RenderObject();
    sphere->mesh = render::mesh::Sphere(.5f, 50, 50);
    sphere->position = {-.75f, 0.f, -5.f};
    sphere->zAxisAngle = 0.f;

    plane = new render::RenderObject();
    plane->mesh = render::mesh::Plane(2.5f, 2.5f, 10, 10);
    plane->position = {0.f, -1.f, -5.f};
    plane->zAxisAngle = 0.f;

    shader = compositor->GetRenderer()->GetShaderManager()->LoadShader("test/triangle.vert");
  }

  void Update() override {
    auto time = std::chrono::system_clock::now().time_since_epoch().count() / 1000000000.0;

    sphere->zAxisAngle = std::sin(time) * 200;
  }

  void Render() override {
    compositor->GetRenderer()->RenderObject(sphere);
    compositor->GetRenderer()->RenderObject(plane);

    // shader->ExecuteProgram();
  }

  ~GlTestScene() override = default;
};

// end of GLTestScene.cxx
