#pragma once

#include <vector>
#include "../render/components/RenderObject.h"
#include "AbstractObject.h"

namespace unreal_fluid::compositor {
  class Compositor;
}

namespace unreal_fluid {
  class Scene {
    std::vector<AbstractObject *> objects;

  public:
    Scene(compositor::Compositor *compositor) {};
    ~Scene() = default;

    virtual void init();
    virtual void update();
    virtual void render();
    virtual void clear();
  };
} // namespace unreal_fluid
