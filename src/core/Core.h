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

#include "Compositor.h"
#include "render/window_manager/WindowCompositor.h"

namespace unreal_fluid {
  class Core {
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
    /// @brief Shutdown core.
    /// @details Shutdown all components of core.
    void Shutdown();

    /// Get window compositor.
    /// @return Window compositor.
    [[nodiscard]] window::WindowCompositor *GetWindowCompositor() const;

  private:
    /// @brief Initialize core.
    /// @details Initialize all components of core.
    void Init();
    /// @brief Update core.
    /// @details Update all components of core.
    void Update();
  }; // core class
} // namespace unreal_fluid

// end of Core.h
