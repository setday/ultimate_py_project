#pragma once

#include "../../Definitions.h"

#include "../managers/sub_programs_managers/shader_manager/ShaderManager.h"
#include "components/RenderObject.h"
#include "components/camera/Camera.h"

namespace unreal_fluid::render {
  class Renderer {
  public:
    enum class RenderMode {
      WIREFRAME,
      SOLID,
      TEXTURED
    };

  private:
    ShaderManager *_shaderManager;
    RenderMode _renderMode;

  public:
    Camera camera;

    Renderer() = default;
    ~Renderer() = default;

    void Init();
    void StartFrame() const;
    void RenderObject(const render::RenderObject *object) const;
    void Destroy();

    /// Get shader manager.
    /// @return Shader manager.
    [[nodiscard]] ShaderManager *GetShaderManager() const;

    /// Change render mode.
    /// @param mode New render mode.
    void ChangeRenderMode(RenderMode mode);
  private:
    void InitGl() const;
  }; // Renderer class
} // namespace unreal_fluid::render
