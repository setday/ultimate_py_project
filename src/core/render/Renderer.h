/***************************************************************
 * Copyright (C) 2023
 *    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : Renderer.h
 * FILE AUTHORS            : Serkov Alexander.
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#pragma once

#include <memory>

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
    std::unique_ptr<ShaderManager> _shaderManager;
    RenderMode _renderMode = RenderMode::SOLID;
    GLuint _fvbo = -1;                  // frame vertex buffer object
    GLuint _fvao = -1;                  // frame vertex array object
    GLuint _vbo = -1;                   // vertex buffer object for rendering objects
    GLuint _vao = -1;                   // vertex array object for rendering objects
    GLuint _ibo = -1;                   // index buffer object for rendering objects
    GLuint _rtubo = -1;                 // ray tracing uniform buffer object
    GLuint _fbo = -1;                   // frame buffer object
    std::unique_ptr<Texture> _fbdt;     // frame buffer depth texture
    std::unique_ptr<Texture> _fbto[5];  // 0 - color, 1 - position, 2 - normal, 3 - reserved, 4 - reserved
    std::vector<const RenderObject *> _objectsToRender;

    utils::Timer _timer{};

  public:
    Camera camera;

    Renderer();
    ~Renderer();

    void startFrame();
    /// render objects.
    /// @param objects Objects to render.
    /// @attention If you are using ray tracing mode the objects will only be rendered after calling endFrame().
    /// @attention So you should not change objects after calling this method.
    void renderObjects(const std::vector<render::RenderObject *> &objects);
    /// End rendering frame.
    void endFrame();

    /// Get shader manager.
    /// @return Shader manager.
    [[nodiscard]] ShaderManager *getShaderManager() const;

    /// Change render mode.
    /// @param mode New render mode.
    void changeRenderMode(RenderMode mode);

    /// Change render resolution
    /// @param width - width of camera
    /// @param height - height of camera
    void changeResolution(int width, int height);
  private:
    /// Initialize all essential OpenGL parameters and rendering properties.
    void initGl() const;
    /// Initialize all buffers essential for rendering.
    void initBuffers();

    /// Bind camera to shader.
    /// @param shader Shader to bind camera to.
    void bindCameraToShader(const ShaderProgram *shader) const;

    /// Draw vertex array.
    /// @param vertices Vertex array.
    /// @param indices Index array.
    void drawVertexes(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices = {});

    /// Draw screen quad.
    void drawScreenQuad() const;

    /// Render all objects in Ray Tracing mode.
    void drawRT();

    /// Added postprocessing effects to result image.
    void postProcess();
  }; // Renderer class
} // namespace unreal_fluid::render

// end of Renderer.h
