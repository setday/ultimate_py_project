/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Compositor.h
 * PURPOSE   : This class is responsible for rendering.
 *
 * No part of this file may be changed and used without agreement of
 * authors of this pressureSolving.
 */

#pragma once

#include "../Definitions.h"

#include "./render/Renderer.h"

namespace unreal_fluid {
  class Core;
}

namespace unreal_fluid {
  class Scene;
}

namespace unreal_fluid::compositor {
  class Compositor {
  private:
    render::Renderer *_renderer;
    std::vector<Scene *> _scenes;
    Core *_core;

  public:
    explicit Compositor(Core *core);
    ~Compositor();

    /// @brief Initialize compositor.
    /// @details Initialize all components of compositor.
    void Init();
    /// @brief Update compositor.
    /// @details Update all components of compositor.
    void Update();
    /// @brief Render compositor.
    /// @details Render all components of compositor.
    void Render();
    /// @brief Destroy compositor.
    /// @details Destroy all components of compositor.
    void Destroy();

    /// Get core.
    /// @return Core.
    [[nodiscard]] Core *GetCore() const;

    /// Get renderer.
    /// @return Renderer.
    [[nodiscard]] render::Renderer *GetRenderer() const;
  }; // compositor class
} // namespace unreal_fluid::compositor

// end of Compositor.h
