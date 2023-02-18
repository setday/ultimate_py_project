#pragma once

#include <GL/gl.h>
#include <GL/glu.h>

#include "components/RenderObject.h"

namespace unreal_fluid::render {
  class Renderer {
  public:
    Renderer() = default;
    ~Renderer() = default;

    void init();
    void renderObject(RenderObject *object);
    void destroy();

  private:
    void initGL();
  }; // Renderer class
} // namespace unreal_fluid::render
