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
  vec2f cameraRotation = {0.f, M_PI};
  bool angleChanged = false;

  explicit Control(const compositor::Compositor *compositor) : Scene(compositor),
                                                               compositor(compositor) {
      compositor->getCore()->GetWindowCompositor()->addKeyboardCallback([this](int key, int action) {
      this->keyboardBindings(key, action);
    });
      compositor->getCore()->GetWindowCompositor()->addResizeCallback([this](int width, int height) {
      this->resizeBindings(width, height);
    });
  }

  void Render() override {
  }

  void keyboardBindings(int key, int action) {
    if (key == GLFW_KEY_F1 && action == GLFW_PRESS) {
      if (this->renderMode == render::Renderer::RenderMode::WIREFRAME) {
        this->renderMode = render::Renderer::RenderMode::SOLID;
      } else {
        this->renderMode = render::Renderer::RenderMode::WIREFRAME;
      }

        this->compositor->getRenderer()->ChangeRenderMode(this->renderMode);
    }

    positionChanged = false;

    if (key == GLFW_KEY_W) {
      cameraPosition += this->compositor->getRenderer()->camera.getDirection() / 4;
      positionChanged = true;
    }
    if (key == GLFW_KEY_S) {
      cameraPosition -= this->compositor->getRenderer()->camera.getDirection() / 4;
      positionChanged = true;
    }
    if (key == GLFW_KEY_D) {
      cameraPosition -= vec3f(0.f, 1.f, 0.f).cross(this->compositor->getRenderer()->camera.getDirection()) / 4;
      positionChanged = true;
    }
    if (key == GLFW_KEY_A) {
      cameraPosition += vec3f(0.f, 1.f, 0.f).cross(this->compositor->getRenderer()->camera.getDirection()) / 4;
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
      cameraRotation.x += 0.1f;
      angleChanged = true;
    }

    if (key == GLFW_KEY_DOWN) {
      cameraRotation.x -= 0.1f;
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
        this->compositor->getRenderer()->camera.setPosition(cameraPosition);
    }

    if (angleChanged) {
        this->compositor->getRenderer()->camera.setDirection(cameraRotation.y, cameraRotation.x);
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        this->compositor->getCore()->Shutdown();
    }

    if (key == GLFW_KEY_F2 && action == GLFW_PRESS) {
        this->compositor->getRenderer()->ChangeRenderMode(render::Renderer::RenderMode::WIREFRAME);

      Logger::logInfo("Wireframe mode enabled");
    }
    if (key == GLFW_KEY_F1 && action == GLFW_PRESS) {
        this->compositor->getRenderer()->ChangeRenderMode(render::Renderer::RenderMode::SOLID);

      Logger::logInfo("Solid mode enabled");
    }
    if (key == GLFW_KEY_F5 && action == GLFW_PRESS) {
        this->compositor->getRenderer()->ChangeRenderMode(render::Renderer::RenderMode::RAY_TRACING);

      Logger::logInfo("Ray tracing mode enabled");
    }

    if (key == GLFW_KEY_F11 && action == GLFW_PRESS) {
        this->compositor->getRenderer()->GetShaderManager()->ReloadShaders();

      Logger::logInfo("All shaders reloaded!");
    }
  }

  void resizeBindings(int width, int height) {
      this->compositor->getRenderer()->changeResolution(width, height);
  }

  ~Control() override = default;

    void Init() override;

    void Update() override;

    void Clear() override;
};

// end of Control.cxx

void Control::Init() {}

void Control::Update() {}

void Control::Clear() {}
