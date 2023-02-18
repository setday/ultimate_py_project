//
// Copyright (c) 2023 Unreal Fluid. All rights reserved.
//

#include "WindowCompositor.h"

using namespace unreal_fluid::window;

WindowCompositor::WindowCompositor() {
  if (!glfwInit()) {
    std::cout << "Failed to initialize GLFW" << std::endl;
    return;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

WindowCompositor::~WindowCompositor() {
  destroy();

  glfwTerminate();
}

void WindowCompositor::init(int width, int height) {
  if (_isAlive) destroy();

  _window = glfwCreateWindow(width, height, "Unreal Fluid", nullptr, nullptr);
  if (!_window) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return;
  }

  glfwMakeContextCurrent(_window);
  glfwSwapInterval(1);

  _width = width;
  _height = height;

  _isAlive = true;
}

void WindowCompositor::swapBuffers() {
  if (!_isAlive) return;

  glfwSwapBuffers(_window);
}

void WindowCompositor::resize(int width, int height) {
  if (!_isAlive) return;

  _width = width;
  _height = height;
}

void WindowCompositor::destroy() {
  if (!_isAlive) return;

  glfwDestroyWindow(_window);

  _isAlive = false;
}
