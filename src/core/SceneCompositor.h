/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : SceneCompositor.h
 * PURPOSE   : This class is responsible for rendering.
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include <memory>

#include "../Definitions.h"

#include "./render/Renderer.h"
#include "physics/Simulator.h"

namespace unreal_fluid {
  class Core;
}

namespace unreal_fluid {
  class IScene;
}

namespace unreal_fluid::compositor {
  class SceneCompositor {
  private:
    std::unique_ptr<render::Renderer> _renderer;
    physics::Simulator *_simulator;
    std::vector<IScene *> _scenes;
    Core *_core;

    utils::Timer _timer;
    utils::Timer _renderingTimer;
    utils::Timer _simulationTimer;

  public:
    explicit SceneCompositor(Core *core);
    ~SceneCompositor() = default;

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

    /// Load scene.
    /// @param scene Scene.
    template<typename S>
    void loadScene() {
      static_assert(std::is_base_of<IScene, S>::value, "Scene must be derived from Scene class");
      _scenes.emplace_back(new S(this));
    }
    /// Unload scene.
    /// @param scene Scene.
    void unloadScene(IScene *scene);

    /// Get core.
    /// @return Core.
    [[nodiscard]] Core *getCore() const;

    /// Get renderer.
    /// @return Renderer.Render.
    [[nodiscard]] render::Renderer *getRenderer() const;
    [[nodiscard]] physics::Simulator *getSimulator() const;
  }; // compositor class
} // namespace unreal_fluid::compositor

// end of SceneCompositor.h
