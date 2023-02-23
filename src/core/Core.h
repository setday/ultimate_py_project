#pragma once

#include "managers/sub_programs_managers/CL/CLManager.h"
#include "Compositor.h"

namespace unreal_fluid {
  class Core {
  public:
    manager::CLManager clManager;

  private:
    bool _isRunning = false;
    compositor::Compositor _compositor;

  public:
    Core();
    ~Core();

    void Run();

  private:
    void Init();
    void Update();
    void Shutdown();
  }; // core class
} // namespace unreal_fluid
