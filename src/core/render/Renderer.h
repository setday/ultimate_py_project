/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Renderer.h
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
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
    RenderMode _renderMode;
    GLuint _fvbo;    // frame vertex buffer object
    GLuint _fvao;    // frame vertex array object
    GLuint _vbo;     // vertex buffer object for rendering objects
    GLuint _vao;     // vertex array object for rendering objects
    GLuint _ibo;     // index buffer object for rendering objects
    GLuint _rtubo;   // ray tracing uniform buffer object
    GLuint _fbo;     // frame buffer object
    GLuint _fbto[6]; // frame buffer texture object: 0 - color, 1 - depth, 2 - position, 3 - normal, 4 - reserved, 5 - reserved
    std::vector<const RenderObject *> _objectsToRender;

    utils::Timer _timer;

  public:
    Camera camera;

    Renderer();
    ~Renderer();

    void startFrame();
    /// render object.
    /// @param object Object to render.
    void renderObject(const render::RenderObject *object);
    /// render all objects.
    /// @param objects Objects to render.
    void renderAllObjects(const std::vector<render::RenderObject *> &objects);
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
    /// Bind object parameters to shader.
    /// @param shader Shader to bind object to.
    /// @param object Object to bind.
    void bindObjectToShader(const ShaderProgram *shader, const RenderObject *object) const;

    /// Draw vertex array.
    /// @param vertices Vertex array.
    /// @param indices Index array.
    void drawVertexes(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices = {});

    /// Render all objects in Ray Tracing mode.
    void drawRT();

    /// Added postprocessing effects to result image.
    void postProcess();
  }; // Renderer class
} // namespace unreal_fluid::render

// end of Renderer.h
