/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Compositor.cxx
 * PURPOSE   : This class is responsible for rendering.
 *
 * No part of this file may be changed and used without agreement of
 * authors of this pressureSolving.
 */

#include "Compositor.h"

#include "./components/Scene.h"

#include "../scenes/ClTestScene.cxx"
#include "../scenes/GlTestScene.cxx"
#include "../scenes/Control.cxx"

using namespace unreal_fluid::compositor;

Compositor::Compositor(Core *core) : _core(core) {
  Logger::logInfo("Creating compositor...");

  _renderer = new render::Renderer();

  Logger::logInfo("Compositor created!");
}

Compositor::~Compositor() {
  delete _renderer;
}

void Compositor::Init() {
  Logger::logInfo("Initializing compositor...");

  _renderer->Init();
  _scenes.push_back(new ClTestScene(this));
  _scenes.push_back(new GlTestScene(this));
  _scenes.push_back(new Control(this));

  Logger::logInfo("Compositor initialized!");
}

void Compositor::Update() {
  for (auto scene : _scenes) {
    scene->Update();
  }
}

void Compositor::Render() {
  _renderer->StartFrame();
  for (auto scene : _scenes) {
    scene->Render();
  }
  _renderer->EndFrame();
}

void Compositor::Destroy() {
  _renderer->Destroy();
  for (auto scene : _scenes) {
    scene->Clear();
    delete scene;
  }
}

Core *Compositor::GetCore() const {
  return _core;
}

render::Renderer *Compositor::GetRenderer() const {
  return _renderer;
}

// end of Compositor.cxx
