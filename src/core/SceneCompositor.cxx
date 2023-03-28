/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : SceneCompositor.cxx
 * PURPOSE   : This class is responsible for rendering.
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "SceneCompositor.h"

#include "components/scene/Scene.h"
#include "./../scenes/SceneLoader.cxx"

using namespace unreal_fluid::compositor;

SceneCompositor::SceneCompositor(Core *core) : _core(core) {
  Logger::logInfo("Creating compositor...");

  _renderer = new render::Renderer();

  _timer.pause();
  _timer.reset();

  Logger::logInfo("SceneCompositor created!");
}

SceneCompositor::~SceneCompositor() {
  delete _renderer;
}

void SceneCompositor::init() {
  Logger::logInfo("Initializing compositor...");

  _renderer->Init();

  loadScene<SceneLoader>();

  Logger::logInfo("SceneCompositor initialized!");
}

void SceneCompositor::update() {
  // _timer.resume();

  for (auto scene : _scenes) {
    if (scene != nullptr)
      scene->update();
  }

  // _timer.pause();
}

void SceneCompositor::render() {
  _timer.resume();

  _renderer->StartFrame();
  for (auto scene : _scenes) {
    if (scene != nullptr)
      scene->render();
  }
  _renderer->EndFrame();

  _timer.pause();
  _timer.incrementCounter();

  if (_timer.getCounter() >= 400 || _timer.getElapsedTime() >= 0.5) {
    Logger::logInfo("| Time to crate a frame: ", _timer.getAverageTime<utils::Timer::TimeType::MILLISECONDS>(), " ms",
            " | FPS: ", 1 / _timer.getAverageTime(), " |");
    _timer.reset();
  }
}

void SceneCompositor::destroy() {
  for (auto scene : _scenes)
    delete scene;

  _renderer->Destroy();
}

void SceneCompositor::unloadScene(IScene *scene) {
  for (auto it = _scenes.begin(); it != _scenes.end(); ++it) {
    if (*it == scene) {
      _scenes.erase(it);
      delete scene;
      break;
    }
  }
}

Core *SceneCompositor::getCore() const {
  return _core;
}

render::Renderer *SceneCompositor::getRenderer() const {
  return _renderer;
}

// end of SceneCompositor.cxx
