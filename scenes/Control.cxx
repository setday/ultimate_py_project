/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Control.cxx
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "../src/core/Core.h"
#include "../src/core/components/Scene.h"

using namespace unreal_fluid;

class Control : public Scene {
public:
  const compositor::Compositor *compositor;
  render::Renderer::RenderMode renderMode = render::Renderer::RenderMode::SOLID;

  explicit Control(compositor::Compositor const * compositor) : Scene(compositor), compositor(compositor) {
    compositor->GetCore()->GetWindowCompositor()->addKeyboardCallback([this](int key, int action) {
      this->keyboardBindings(key, action);
    });
  }

  void keyboardBindings(int key, int action) {
    if (key == GLFW_KEY_W && action == GLFW_PRESS) {

      if (this->renderMode == render::Renderer::RenderMode::WIREFRAME) {
        this->renderMode = render::Renderer::RenderMode::SOLID;
      } else {
        this->renderMode = render::Renderer::RenderMode::WIREFRAME;
      }

      this->compositor->GetRenderer()->ChangeRenderMode(this->renderMode);
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
      this->compositor->GetCore()->Shutdown();
    }
  }

  ~Control() override = default;
};

// end of Control.cxx
