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

WindowCompositor::WindowCompositor() {
  Logger::log(Logger::Level::INFO, "Initializing window compositor...");

  if (!glfwInit()) {
    Logger::log(Logger::Level::ERR, "Failed to initialize GLFW!");
    return;
  }

  glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

  Logger::log(Logger::Level::INFO, "Window compositor initialized!");
}

WindowCompositor::~WindowCompositor() {
  destroy();

  glfwTerminate();
}

void WindowCompositor::init(int width, int height) {
  Logger::log(Logger::Level::INFO, "Creating window with size " + std::to_string(width) + "x" + std::to_string(height) + "...");

  if (_isAlive) destroy();

  _window = glfwCreateWindow(width, height, "Unreal Fluid", nullptr, nullptr);
  if (!_window) {
    Logger::log(Logger::Level::ERR, "Failed to create window!");
    glfwTerminate();
    return;
  }

  glfwMakeContextCurrent(_window);
  glfwSwapInterval(1);

  glfwSetKeyCallback(_window, keyboardCallback);

  _isAlive = true;

  Logger::log(Logger::Level::INFO, "Window created!");
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

  Logger::log(Logger::Level::INFO, "Destroying window...");

  glfwDestroyWindow(_window);

  _isAlive = false;
}

void WindowCompositor::keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  for (auto& callback : _keyboardCallbacks) {
    callback(key, action);
  }
}

void WindowCompositor::addKeyboardCallback(std::function<void(int key, int action)> callback) {
  _keyboardCallbacks.push_back(callback);
}

void WindowCompositor::getSize(int& width, int& height) const {
  glfwGetWindowSize(_window, &width, &height);
}

// end of WindowCompositor.cxx
