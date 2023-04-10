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
 * authors of this project.
 */

#include "Compositor.h"
#include "../scenes/Control.cxx"
#include "../scenes/GlTestScene.cxx"
#include "../scenes/TestScene.cxx"

using namespace unreal_fluid::compositor;

Compositor::Compositor(Core *core) : _core(core) {
  Logger::logInfo("Creating compositor...");
  _simulator = new physics::Simulator;
  _renderer = new render::Renderer();

  _timer.pause();
  _timer.reset();
  _renderingTimer.pause();
  _renderingTimer.reset();

  Logger::logInfo("Compositor created!");
}

Compositor::~Compositor() {
  delete _renderer;
}

void Compositor::init() {
  Logger::logInfo("Initializing compositor...");

  _renderer->Init();
//  _scenes.push_back(new GlTestScene(this));
  _scenes.push_back(new TestScene(this));
  _scenes.push_back(new Control(this));

  Logger::logInfo("Compositor initialized!");
}

void Compositor::update() {
  _timer.resume();
  _simulationTimer.resume();

  for (auto scene : _scenes) {
    scene->update();
  }

  _simulationTimer.pause();
  _timer.pause();
  _simulationTimer.incrementCounter();
}

void Compositor::render() {
  _timer.resume();
  _renderingTimer.resume();

  _renderer->StartFrame();
  for (auto scene: _scenes) {
    scene->render();
  }
  _renderer->EndFrame();

  _renderingTimer.pause();
  _timer.pause();
  _renderingTimer.incrementCounter();
  _timer.incrementCounter();

  if (_timer.getCounter() >= 400 || _timer.getElapsedTime() >= 1.5) {
    Logger::logInfo(
            "\n", "-------------------------------------------->\n",
            "| Time to crate a frame: ", _timer.getAverageTime<utils::Timer::TimeType::MILLISECONDS>(), " ms\n",
            "| FPS: ", 1 / _timer.getAverageTime(), "\n",
            "-------------------------------------------->\n",
            "| Time to render a frame: ", _renderingTimer.getAverageTime<utils::Timer::TimeType::MILLISECONDS>(), " ms\n",
            "| Time to simulate a frame: ", _simulationTimer.getAverageTime<utils::Timer::TimeType::MILLISECONDS>(), " ms\n",
            "-------------------------------------------->"
            );
    _timer.reset();
    _renderingTimer.reset();
    _simulationTimer.reset();
  }
}

void Compositor::destroy() {
  _renderer->Destroy();
  for (auto scene: _scenes) {
    scene->clear();
    delete scene;
  }
}

Core *Compositor::getCore() const {
  return _core;
}

render::Renderer *Compositor::getRenderer() const {
  return _renderer;
}

physics::Simulator *Compositor::getSimulator() const {
    return _simulator;
}

// end of Compositor.cxx
