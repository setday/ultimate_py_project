#pragma once

#include "Compositor.h"

namespace unreal_fluid {
  class Core {
  private:
    bool _isRunning;
    compositor::Compositor _compositor;

  public:
    Core();
    ~Core();

    void run();

  private:
    void init();
    void update();
    void render();
    void shutdown();
  }; // core class
} // namespace unreal_fluid
