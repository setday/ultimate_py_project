/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Core.cxx
 * PURPOSE   : This is the main class of the project.
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "Core.h"
#include <iostream>

using namespace unreal_fluid;

Core::Core() : _windowCompositor(std::make_unique<window::WindowCompositor>()),
               _compositor(this) {}

void Core::run() {
  init();

  while (_isRunning) {
    update();
  }
}

window::WindowCompositor *Core::getWindowCompositor() const {
  return _windowCompositor.get();
}

void Core::init() {
  Logger::logInfo("Initializing core...");

  _isRunning = true;
  _windowCompositor->init(500, 500);
  _compositor.init();

  Logger::logInfo("Core initialized!");
}

void Core::update() {
  _compositor.update();
  _compositor.render();
  _windowCompositor->update();

  if (!_windowCompositor->isAlive()) {
    _isRunning = false;
  }
}

void Core::shutdown() {
  _compositor.destroy();
  _isRunning = false;
}

// end of Core.cxx
