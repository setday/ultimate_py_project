
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
 * authors of this project.
 */

#pragma once

#include "../Definitions.h"
#include "./render/Renderer.h"
#include "physics/Simulator.h"

namespace unreal_fluid {
  class Core;
  class Scene;
}

namespace unreal_fluid::compositor {
  class Compositor {
  private:
    render::Renderer *_renderer;
    physics::Simulator *_simulator;
    std::vector<Scene *> _scenes;
    Core *_core;

    utils::Timer _timer;
    utils::Timer _renderingTimer;
    utils::Timer _simulationTimer;

  public:
    explicit Compositor(Core *core);
    ~Compositor();

    /// @brief Initialize compositor.
    /// @details Initialize all components of compositor.
    void init();
    /// @brief update compositor.
    /// @details update all components of compositor.
    void update();
    /// @brief render compositor.
    /// @details render all components of compositor.
    void render();
    /// @brief destroy compositor.
    /// @details destroy all components of compositor.
    void destroy();

    /// Get core.
    /// @return Core.
    [[nodiscard]] Core *getCore() const;

    /// Get renderer.
    /// @return Renderer.
    [[nodiscard]] render::Renderer *getRenderer() const;
    [[nodiscard]] physics::Simulator *getSimulator() const;
  }; // compositor class
} // namespace unreal_fluid::compositor

// end of Compositor.h
