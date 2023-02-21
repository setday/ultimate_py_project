#pragma once

// #include "./render/window_manager/WindowCompositor.h"
#include "./render/Renderer.h"
#include "./components/Scene.h"

namespace unreal_fluid::compositor {
  class Compositor {
  private:
    // window::WindowCompositor *_windowCompositor;
    render::Renderer *_renderer;


  public:
    std::vector<Scene *> scenes;

    Compositor();
    ~Compositor();

    void init();
    void update();
    void render();
    void destroy();
  }; // compositor class
} // namespace unreal_fluid::compositor
