#pragma once

#include <vector>

#include "Object.h"

namespace unreal_fluid::render {
  class Scene {
    std::vector<Object> objects;

  public:
    Scene() = default;
    ~Scene() = default;

    void init();
    void update();
    void render();
    void clear();
  };
} // namespace unreal_fluid::render
