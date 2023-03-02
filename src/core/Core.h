/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Core.h
 * PURPOSE   : This is the main class of the project.
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "../Definitions.h"

#include "managers/sub_programs_managers/CL/CLManager.h"
#include "render/window_manager/WindowCompositor.h"
#include "Compositor.h"

namespace unreal_fluid {
  class Core {
  public:
    manager::CLManager clManager;

  private:
    bool _isRunning = false;
     window::WindowCompositor *_windowCompositor;
    compositor::Compositor _compositor;

  public:
    Core();
    ~Core();

    /// @brief Run core.
    /// @details Run main loop of core.
    void Run();

  private:
    /// @brief Initialize core.
    /// @details Initialize all components of core.
    void Init();
    /// @brief Update core.
    /// @details Update all components of core.
    void Update();
    /// @brief Shutdown core.
    /// @details Shutdown all components of core.
    void Shutdown();
  }; // core class
} // namespace unreal_fluid

// end of Core.h
