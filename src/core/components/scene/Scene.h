#pragma once

#include "PhysicalScene.h"
#include "RenderScene.h"

namespace unreal_fluid {
class Scene : public PhysicalScene, public RenderScene {
  public:
    explicit Scene(compositor::SceneCompositor const *compositor);

    /// Update scene.
    /// @details Update all objects in scene.
    void update() override;
    /// Render scene.
    /// @details Render all objects in scene.
    void render() override;

    /// Convert to IScene.
    /// @return IScene.
    template<typename T>
    [[nodiscard]] explicit operator T *() const {
      return (RenderScene *)this;
    }
    template<typename T>
    [[nodiscard]] explicit operator T &() const {
      return (RenderScene &)*this;
    }

  protected:
    /// Get renderer of compositor.
    /// @return Renderer.
    [[nodiscard]] render::Renderer *getRenderer() const;
    /// Get core that owns this compositor.
    /// @return Core.
    [[nodiscard]] Core *getCore() const;
  };
} // namespace unreal_fluid

// end of Scene.h
