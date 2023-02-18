#pragma once

#include "./render/window_manager/WindowCompositor.h"
#include "./render/Renderer.h"

namespace unreal_fluid::compositor {
  class Compositor {
  private:
    window::WindowCompositor *_windowCompositor;
    render::Renderer *_renderer;

  public:
    Compositor();
    ~Compositor();

    void init();
    void update();
    void render();
    void destroy();
  }; // compositor class
} // compositor
