#pragma once

#include <vector>

#include "../Compositor.h"
#include "../render/components/RenderObject.h"
#include "AbstractObject.h"

namespace unreal_fluid {
  class Scene {
    std::vector<AbstractObject *> objects;

  public:
    explicit Scene(compositor::Compositor const *) {};
    virtual ~Scene() = default;

    virtual void Init();
    virtual void Update();
    virtual void Render();
    virtual void Clear();
  };
} // namespace unreal_fluid
