#pragma once

#include "managers/sub_programs_managers/CL/CLManager.h"
#include "Compositor.h"

namespace unreal_fluid {
  class Core {
  public:
    manager::CLManager clManager;

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
