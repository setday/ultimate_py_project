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
      TEXTURED,
      RAY_TRACING
    };

  private:
    ShaderManager *_shaderManager;
    RenderMode _renderMode;
    GLuint _fvbo;  // frame vertex buffer object
    GLuint _fvao;  // frame vertex array object
    GLuint _vbo;   // vertex buffer object for rendering objects
    GLuint _vao;   // vertex array object for rendering objects
    GLuint _ibo;   // index buffer object for rendering objects
    GLuint _rtubo; // ray tracing uniform buffer object

  public:
    Camera camera;

    Renderer() = default;
    ~Renderer() = default;

    void Init();
    void Destroy();

    void StartFrame() const;
    /// Render object.
    /// @param object Object to render.
    /// @attention projection only! If you render objects using ray tracing, you should use RenderAllObjects() instead.
    void RenderObject(const render::RenderObject *object) const;
    /// Render all objects.
    /// @param objects Objects to render.
    void RenderAllObjects(const std::vector<render::RenderObject *> &objects) const;
    /// End rendering frame.
    void EndFrame() const;

    /// Get shader manager.
    /// @return Shader manager.
    [[nodiscard]] ShaderManager *GetShaderManager() const;

    /// Change render mode.
    /// @param mode New render mode.
    void ChangeRenderMode(RenderMode mode);

    /// Change render resolution
    /// @param width - width of camera
    /// @param height - height of camera
    void changeResolution(int width, int height);
  private:
    void InitGl() const;
  }; // Renderer class
} // namespace unreal_fluid::render
