/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : GLTestScene.cxx
 *
 * No part of this file may be changed and used without agreement of
 * authors of this pressureSolving.
 */

#include <cmath>

#include "../src/core/Core.h"
#include "../src/core/components/Scene.h"

using namespace unreal_fluid;

class GlTestScene : public Scene {
public:
  render::RenderObject *renderObject;
  const compositor::Compositor *compositor;

  explicit GlTestScene(compositor::Compositor const * compositor) : Scene(compositor), compositor(compositor) {
    renderObject = new render::RenderObject();
    renderObject->vertices = {
      {-0.6f, -0.4f, 0.f},
      {0.6f, -0.4f, 0.f},
      {0.f, 0.6f, 0.f}
    };
    renderObject->colors = {
      {1.f, 0.f, 0.f},
      {0.f, 1.f, 0.f},
      {0.f, 0.f, 1.f}
    };
    renderObject->zAxisAngle = 0.f;
  }

  void Update() override {
    auto time = std::chrono::system_clock::now().time_since_epoch().count() / 1000000000.0;

    renderObject->zAxisAngle = std::sin(time) * 200;
  }

  void Render() override {
    compositor->GetRenderer()->RenderObject(renderObject);
  }

  ~GlTestScene() override = default;
};

// end of GLTestScene.cxx
