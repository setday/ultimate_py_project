#pragma once

#include "managers/sub_programs_managers/CLManager.h"
#include "Compositor.h"

namespace unreal_fluid {
  class Core {
  private:
    bool _isRunning{};
    compositor::Compositor _compositor;
    manager::CLManager clManager;

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
