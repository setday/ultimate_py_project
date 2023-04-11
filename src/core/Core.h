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

#include <memory>

#include "../Definitions.h"

#include "managers/sub_programs_managers/CL/CLManager.h"
#include "SceneCompositor.h"
#include "render/window_manager/WindowCompositor.h"

namespace unreal_fluid {
  class Core {
  public:
    manager::CLManager clManager;

  private:
    bool _isRunning = false;
    std::unique_ptr<window::WindowCompositor> _windowCompositor;
    compositor::SceneCompositor _compositor;

  public:
    Core();
    ~Core() = default;

    /// @brief run core.
    /// @details run main loop of core.
    void run();
    /// @brief shutdown core.
    /// @details shutdown all components of core.
    void shutdown();

    /// Get window compositor.
    /// @return Window compositor.
    [[nodiscard]] window::WindowCompositor *getWindowCompositor() const;

  private:
    /// @brief Initialize core.
    /// @details Initialize all components of core.
    void init();
    /// @brief update core.
    /// @details update all components of core.
    void update();
  }; // core class
} // namespace unreal_fluid

// end of Core.h
