#pragma once

// #include "./render/window_manager/WindowCompositor.h"
#include "./render/Renderer.h"
#include "./components/Scene.h"

namespace unreal_fluid {
  class Core;
}

namespace unreal_fluid::compositor {
  class Compositor {
  private:
    // window::WindowCompositor *_windowCompositor;
    render::Renderer *_renderer;
    std::vector<Scene *> _scenes;
    Core *_core;

  public:
    explicit Compositor(Core *core);
    ~Compositor();

    void Init();
    void Update();
    void Render();
    void Destroy();

    [[nodiscard]] Core *GetCore() const;
  }; // compositor class
} // namespace unreal_fluid::compositor
