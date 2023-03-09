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
  vec3f cameraPosition = {0.f, 0.f, 0.f};
  bool positionChanged = false;
  vec2f cameraRotation = {0.f, 0.f};
  bool angleChanged = false;

  explicit Control(compositor::Compositor const * compositor) : Scene(compositor), compositor(compositor) {
    compositor->GetCore()->GetWindowCompositor()->addKeyboardCallback([this](int key, int action) {
      this->keyboardBindings(key, action);
    });
    compositor->GetCore()->GetWindowCompositor()->addResizeCallback([this](int width, int height) {
      this->resizeBindings(width, height);
    });
  }

  void keyboardBindings(int key, int action) {
    if (key == GLFW_KEY_F1 && action == GLFW_PRESS) {
      if (this->renderMode == render::Renderer::RenderMode::WIREFRAME) {
        this->renderMode = render::Renderer::RenderMode::SOLID;
      } else {
        this->renderMode = render::Renderer::RenderMode::WIREFRAME;
      }

      this->compositor->GetRenderer()->ChangeRenderMode(this->renderMode);
    }

    if (key == GLFW_KEY_F5 && action == GLFW_PRESS) {
      this->compositor->GetRenderer()->ChangeRenderMode(render::Renderer::RenderMode::RAY_TRACING);
    }

    positionChanged = false;

    if (key == GLFW_KEY_W) {
      cameraPosition -= this->compositor->GetRenderer()->camera.getDirection() / 4;
      positionChanged = true;
    }
    if (key == GLFW_KEY_S) {
      cameraPosition += this->compositor->GetRenderer()->camera.getDirection() / 4;
      positionChanged = true;
    }
    if (key == GLFW_KEY_D) {
      cameraPosition += vec3f(0.f, 1.f, 0.f).cross(this->compositor->GetRenderer()->camera.getDirection()) / 4;
      positionChanged = true;
    }
    if (key == GLFW_KEY_A) {
      cameraPosition -= vec3f(0.f, 1.f, 0.f).cross(this->compositor->GetRenderer()->camera.getDirection()) / 4;
      positionChanged = true;
    }

    if (key == GLFW_KEY_SPACE) {
      cameraPosition += vec3f(0.f, 1.f, 0.f) / 4;
      positionChanged = true;
    }
    if (key == GLFW_KEY_LEFT_SHIFT) {
      cameraPosition -= vec3f(0.f, 1.f, 0.f) / 4;
      positionChanged = true;
    }

    if (key == GLFW_KEY_UP) {
      cameraRotation.x -= 0.1f;
      angleChanged = true;
    }

    if (key == GLFW_KEY_DOWN) {
      cameraRotation.x += 0.1f;
      angleChanged = true;
    }

    if (key == GLFW_KEY_LEFT) {
      cameraRotation.y += 0.1f;
      angleChanged = true;
    }

    if (key == GLFW_KEY_RIGHT) {
      cameraRotation.y -= 0.1f;
      angleChanged = true;
    }

    if (positionChanged) {
      this->compositor->GetRenderer()->camera.setPosition(cameraPosition);
    }

    if (angleChanged) {
      this->compositor->GetRenderer()->camera.setDirection(cameraRotation.y, cameraRotation.x);
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
      this->compositor->GetCore()->Shutdown();
    }
  }

  void resizeBindings(int width, int height) {
    this->compositor->GetRenderer()->changeResolution(width, height);
  }

  ~Control() override = default;
};

// end of Control.cxx
