/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : WindowCompositor.cxx
 * PURPOSE   : This is wrapper class for the glfw.
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "WindowCompositor.h"

using namespace unreal_fluid::window;

std::vector<std::function<void(int key, int action)>> WindowCompositor::_keyboardCallbacks;
std::vector<std::function<void(int width, int height)>> WindowCompositor::_resizeCallbacks;

WindowCompositor::WindowCompositor() {
  Logger::logInfo("Initializing window compositor...");

  if (!glfwInit()) {
    Logger::logError("Failed to initialize GLFW!");
    return;
  }

  glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

  Logger::logInfo("Window compositor initialized!");
}

WindowCompositor::~WindowCompositor() {
  destroy();

  glfwTerminate();
}

void WindowCompositor::init(int width, int height) {
  Logger::logInfo("Creating window with size ", width, "x", height, "...");

  if (_isAlive) destroy();

  _window = glfwCreateWindow(width, height, "Unreal Fluid", nullptr, nullptr);
  if (!_window) {
    Logger::logError("Failed to create window!");
    glfwTerminate();
    return;
  }

  glfwMakeContextCurrent(_window);
  glfwSwapInterval(1);

  glfwSetKeyCallback(_window, keyboardCallback);
  glfwSetWindowSizeCallback(_window, resizeCallback);

  _isAlive = true;

  Logger::logInfo("Window created!");
}

void WindowCompositor::update() {
  if (!_isAlive) return;

  glfwSwapBuffers(_window);

  glfwPollEvents();

  if (glfwWindowShouldClose(_window)) {
    destroy();
  }
}

void WindowCompositor::resize(int width, int height) {
  if (!_isAlive) return;

  _width = width;
  _height = height;
}

void WindowCompositor::destroy() {
  if (!_isAlive) return;

  Logger::logInfo("Destroying window...");

  glfwDestroyWindow(_window);

  _isAlive = false;
}

void WindowCompositor::keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  for (auto& callback : _keyboardCallbacks) {
    callback(key, action);
  }
}

void WindowCompositor::addKeyboardCallback(std::function<void(int key, int action)> callback) {
  _keyboardCallbacks.emplace_back(callback);
}

void WindowCompositor::resizeCallback(GLFWwindow *window, int width, int height) {
  for (auto& callback : _resizeCallbacks) {
    callback(width, height);
  }
}

void WindowCompositor::addResizeCallback(std::function<void(int width, int height)> callback) {
  _resizeCallbacks.emplace_back(callback);
}

void WindowCompositor::getSize(int& width, int& height) const {
  glfwGetWindowSize(_window, &width, &height);
}

// end of WindowCompositor.cxx
