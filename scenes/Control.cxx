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
  vec3f cameraSpeed = {0.f, 0.f, 0.f};
  vec2f cameraRotation = {0.f, M_PI};
  vec2f cameraRotationSpeed = {0.f, 0.f};

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

    if (key == GLFW_KEY_W)
      cameraSpeed += this->compositor->GetRenderer()->camera.getDirection() / 15;
    if (key == GLFW_KEY_S)
      cameraSpeed -= this->compositor->GetRenderer()->camera.getDirection() / 15;
    if (key == GLFW_KEY_D)
      cameraSpeed -= vec3f(0.f, 1.f, 0.f).cross(this->compositor->GetRenderer()->camera.getDirection()) / 15;
    if (key == GLFW_KEY_A)
      cameraSpeed += vec3f(0.f, 1.f, 0.f).cross(this->compositor->GetRenderer()->camera.getDirection()) / 15;

    if (key == GLFW_KEY_SPACE)
      cameraSpeed += vec3f(0.f, 1.f, 0.f) / 15;
    if (key == GLFW_KEY_LEFT_SHIFT)
      cameraSpeed -= vec3f(0.f, 1.f, 0.f) / 15;

    cameraSpeed.clampSelf(-0.1f, 0.1f);

    if (key == GLFW_KEY_UP)
      cameraRotationSpeed.x += 0.02f;
    if (key == GLFW_KEY_DOWN)
      cameraRotationSpeed.x -= 0.02f;
    if (key == GLFW_KEY_LEFT)
      cameraRotationSpeed.y += 0.02f;
    if (key == GLFW_KEY_RIGHT)
      cameraRotationSpeed.y -= 0.02f;

    cameraRotationSpeed.clampSelf(-0.2f, 0.2f);

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      this->compositor->GetCore()->Shutdown();

    if (key == GLFW_KEY_F2 && action == GLFW_PRESS) {
      this->compositor->GetRenderer()->ChangeRenderMode(render::Renderer::RenderMode::WIREFRAME);

      Logger::logInfo("Wireframe mode enabled");
    }
    if (key == GLFW_KEY_F1 && action == GLFW_PRESS) {
      this->compositor->GetRenderer()->ChangeRenderMode(render::Renderer::RenderMode::SOLID);

      Logger::logInfo("Solid mode enabled");
    }
    if (key == GLFW_KEY_F5 && action == GLFW_PRESS) {
      this->compositor->GetRenderer()->ChangeRenderMode(render::Renderer::RenderMode::RAY_TRACING);

      Logger::logInfo("Ray tracing mode enabled");
    }

    if (key == GLFW_KEY_F11 && action == GLFW_PRESS) {
      this->compositor->GetRenderer()->GetShaderManager()->ReloadShaders();
      render::DefaultShaderManager::ReloadShaders();

      Logger::logInfo("All shaders reloaded!");
    }
  }

  void resizeBindings(int width, int height) {
    this->compositor->GetRenderer()->changeResolution(width, height);
  }

  void Update() override {
    cameraPosition += cameraSpeed;
    if (cameraSpeed.len2() > 0.0001f) {
      this->compositor->GetRenderer()->camera.setPositionHard(cameraPosition);
    }
    cameraSpeed *= 0.9f;

    cameraRotation += cameraRotationSpeed;
    cameraRotation.x = std::min(std::max(cameraRotation.x, -1.57f), 1.57f);
    if (cameraRotationSpeed.len2() > 0.000001f) {
      this->compositor->GetRenderer()->camera.setDirection(cameraRotation.y, cameraRotation.x);
    }
    cameraRotationSpeed *= 0.85f;
  }

  ~Control() override = default;
};

// end of Control.cxx
