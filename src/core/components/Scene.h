#pragma once

#include <vector>

#include "../Compositor.h"
#include "../render/components/RenderObject.h"
#include "AbstractObject.h"

namespace unreal_fluid {
  class Scene {
  protected:
    std::vector<AbstractObject *> objects;
    const compositor::Compositor *compositor;

  public:
    explicit Scene(const compositor::Compositor *compositor) : compositor(compositor) {}
    virtual ~Scene() = default;
    virtual void init();
    virtual void update();
    virtual void render();
    virtual void clear();
  };
} // namespace unreal_fluid
