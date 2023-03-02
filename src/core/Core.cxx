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

  Shutdown();
}

void Core::Init() {
  Logger::log(Logger::Level::INFO, "Initializing core...");

  _isRunning = true;
  _windowCompositor->init(500, 500);
  _compositor.Init();

  Logger::log(Logger::Level::INFO, "Core initialized!");
}

void Core::Update() {
  _compositor.Update();
  _compositor.Render();
  _windowCompositor->update();

  if (!_windowCompositor->isAlive()) {
    _isRunning = false;
  }
}

void Core::Shutdown() {
  _compositor.Destroy();
  _isRunning = false;
}

// end of Core.cxx
