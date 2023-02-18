#pragma once

#include <vector>

#include "RenderObject.h"

namespace unreal_fluid::render {
  class Scene {
    std::vector<RenderObject *> objects;

  public:
    Scene() = default;
    ~Scene() = default;

    void init();
    void update();
    void render();
    void clear();
  };
} // namespace unreal_fluid::render
