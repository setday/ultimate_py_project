#pragma once
#include "Compositor.h"

namespace unreal_fluid::compositor {

  Compositor::Compositor() = default;
  Compositor::~Compositor() = default;
  void Compositor::init() {
    for (auto scene: scenes) scene->init();
  }
  void Compositor::update() {
    for (auto scene: scenes) scene->update();
  }
  void Compositor::render() {
    for (auto scene: scenes) scene->render();
  }
  void Compositor::destroy() {
    for (auto scene: scenes) scene->clear();
  }
} // namespace unreal_fluid::compositor