#pragma once
#include "render/components/Scene.h"
#include <vector>

namespace unreal_fluid::compositor {
  class Compositor {
  public:
    std::vector<render::Scene *> scenes;

    Compositor();
    ~Compositor();

    void init();
    void update();
    void render();
    void destroy();
  }; // compositor class
} // namespace unreal_fluid::compositor
