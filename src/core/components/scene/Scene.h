#pragma once

#include "PhysicalScene.h"
#include "RenderScene.h"

namespace unreal_fluid {
  class Scene : public PhysicalScene, public RenderScene {
  public:
    explicit Scene(const compositor::SceneCompositor *compositor);
    /// @attention If you deallocate all the memory for objects by yourself, you mustn't call this destructor.
    ~Scene() override;

    /// Update scene.
    /// @details Update all objects in scene.
    void update() override;
    /// Render scene.
    /// @details Render all objects in scene.
    void render() override;

    /// Convert to RenderScene.
    /// @return RenderScene.
    template<typename T>
    [[nodiscard]] explicit operator T *() const {
      return (RenderScene *) this;
    }

    template<typename T>
    [[nodiscard]] explicit operator T &() const {
      return (RenderScene &) *this;
    }

  protected:
    /// Get renderer of compositor.
    /// @return Renderer.Render.
    [[nodiscard]] render::Renderer *getRenderer() const;
    /// Get core that owns this compositor.
    /// @return Core.
    [[nodiscard]] Core *getCore() const;

    /// Delete all objects in scene.
    /// @attention Also delete all memory allocated for objects.
    void deleteObjects();
  };
} // namespace unreal_fluid

// end of Scene.h
