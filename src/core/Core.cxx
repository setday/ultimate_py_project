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

#include <iostream>

#include "Core.h"

using namespace unreal_fluid;

Core::Core() : _compositor(this) {
  _windowCompositor = new window::WindowCompositor();
}

Core::~Core() {
  delete _windowCompositor;
};

void Core::Run() {
  Init();

  while (_isRunning) {
    Update();
  }
}

window::WindowCompositor *Core::GetWindowCompositor() const {
  return _windowCompositor;
}

void Core::Init() {
  Logger::logInfo("Initializing core...");

  _isRunning = true;
  _windowCompositor->init(500, 500);
  _compositor.init();

  Logger::logInfo("Core initialized!");
}

void Core::Update() {
  _compositor.update();
  _compositor.render();
  _windowCompositor->update();

  if (!_windowCompositor->isAlive()) {
    _isRunning = false;
  }
}

void Core::Shutdown() {
  _compositor.destroy();
  _isRunning = false;
}

// end of Core.cxx
