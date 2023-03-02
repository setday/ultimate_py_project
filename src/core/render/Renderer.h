#pragma once

#include <GL/gl.h>
#include <GL/glu.h>

#include "../../Definitions.h"

#include "components/RenderObject.h"

namespace unreal_fluid::render {
  class Renderer {
  public:
    Renderer() = default;
    ~Renderer() = default;

    void Init() const;
    void StartFrame() const;
    void RenderObject(const render::RenderObject *object) const;
    void Destroy() const;

  private:
    void InitGl() const;
  }; // Renderer class
} // namespace unreal_fluid::render
