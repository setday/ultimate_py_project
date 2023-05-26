/***************************************************************
* Copyright (C) 2023
*    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
*    HSE SPb (Higher school of economics in Saint-Petersburg).
***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : Control.cxx
 * FILE AUTHORS            : Serkov Alexander.
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#include "../src/core/Core.h"
#include "../src/core/components/scene/Scene.h"

using namespace unreal_fluid;

class Control : public IScene {
public:
  vec3f cameraSpeed = {0.f, 0.f, 0.f};
  vec2f cameraRotationSpeed = {0.f, 0.f};

  explicit Control(compositor::SceneCompositor const * compositor) : IScene() {
    this->compositor = compositor;

    compositor->getCore()->getWindowCompositor()->addKeyboardCallback([this](int key, int action) {
      this->keyboardBindings(key, action);
    });
    compositor->getCore()->getWindowCompositor()->addResizeCallback([this](int width, int height) {
      this->resizeBindings(width, height);
    });
  }

  void keyboardBindings(int key, int action) {
    handleSpecialKeys(key, action);
    handleMoveKeys(key);
    handleRotationKeys(key);
    handleRenderingKeys(key, action);
  }

  void handleSpecialKeys(int key, int action) const {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      this->compositor->getCore()->shutdown();

    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
      if (compositor->getSimulator()->timer.getStatus() == utils::Timer::State::RUNNING)
        compositor->getSimulator()->timer.pause();
      else
        compositor->getSimulator()->timer.resume();
    }

    if (key == GLFW_KEY_F11 && action == GLFW_PRESS) {
      this->compositor->getRenderer()->getShaderManager()->ReloadShaders();
      render::DefaultShaderManager::ReloadShaders();

      Logger::logInfo("All shaders reloaded!");
    }
  }

  void handleMoveKeys(int key) {
    if (key == GLFW_KEY_W)
      cameraSpeed += this->compositor->getRenderer()->camera.getDirection() / 15;
    if (key == GLFW_KEY_S)
      cameraSpeed -= this->compositor->getRenderer()->camera.getDirection() / 15;
    if (key == GLFW_KEY_D)
      cameraSpeed += this->compositor->getRenderer()->camera.getRight() / 15;
    if (key == GLFW_KEY_A)
      cameraSpeed -= this->compositor->getRenderer()->camera.getRight() / 15;

    if (key == GLFW_KEY_SPACE)
      cameraSpeed += vec3f(0.f, 1.f, 0.f) / 15;
    if (key == GLFW_KEY_LEFT_SHIFT)
      cameraSpeed -= vec3f(0.f, 1.f, 0.f) / 15;

    cameraSpeed /= fmax(cameraSpeed.max(), 1.0f);
  }

  void handleRotationKeys(int key) {
    if (key == GLFW_KEY_UP)
      cameraRotationSpeed.x += 0.02f;
    if (key == GLFW_KEY_DOWN)
      cameraRotationSpeed.x -= 0.02f;
    if (key == GLFW_KEY_LEFT)
      cameraRotationSpeed.y += 0.02f;
    if (key == GLFW_KEY_RIGHT)
      cameraRotationSpeed.y -= 0.02f;

    cameraRotationSpeed /= fmax(cameraRotationSpeed.max(), 1.0f);
  }

  void handleRenderingKeys(int key, int action) const {
    if (key == GLFW_KEY_F2 && action == GLFW_PRESS) {
      this->compositor->getRenderer()->changeRenderMode(render::Renderer::RenderMode::WIREFRAME);

      Logger::logInfo("Wireframe mode enabled");
    }
    if (key == GLFW_KEY_F1 && action == GLFW_PRESS) {
      this->compositor->getRenderer()->changeRenderMode(render::Renderer::RenderMode::SOLID);

      Logger::logInfo("Solid mode enabled");
    }
    if (key == GLFW_KEY_F5 && action == GLFW_PRESS) {
      this->compositor->getRenderer()->changeRenderMode(render::Renderer::RenderMode::RAY_TRACING);

      Logger::logInfo("Ray tracing mode enabled");
    }
  }

  void resizeBindings(int width, int height) const {
    this->compositor->getRenderer()->changeResolution(width, height);
  }

  void update() override {
    vec3f cameraPosition = this->compositor->getRenderer()->camera.getPosition() + cameraSpeed;
    if (cameraSpeed.len2() > 0.0001f) {
      this->compositor->getRenderer()->camera.setPositionHard(cameraPosition);
    }
    cameraSpeed *= 0.9f;

    vec2f cameraRotation = this->compositor->getRenderer()->camera.getAngles() + cameraRotationSpeed;
    cameraRotation.x = std::min(std::max(cameraRotation.x, -1.57f), 1.57f);
    if (cameraRotationSpeed.len2() > 0.000001f) {
      this->compositor->getRenderer()->camera.setDirection(cameraRotation);
    }
    cameraRotationSpeed *= 0.85f;
  }

  void render() override {
    // The control scene doesn't render anything.
  }
};

// end of Control.cxx
