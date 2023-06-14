/***************************************************************
 * Copyright (C) 2023
 *    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : BakedMesh.h
 * FILE AUTHORS            : Serkov Alexander.
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#pragma once

#define GLEW_STATIC
#include "GL/glew.h"
#include <GL/gl.h>

#include "../mesh/BasicMesh.h"

namespace unreal_fluid::render::mesh {
  class BakedMesh {
  public:
    enum class Type {
      STATIC,
      DYNAMIC
    };

  private:
    GLuint _vao = -1;
    GLuint _vbo = -1;
    GLuint _ibo = -1;

    size_t _indicesCount = 0;

    Type _type = Type::STATIC;

  public:
    BasicMesh *mesh = nullptr;

  public:
    BakedMesh() = default;
    explicit BakedMesh(BasicMesh *basicMesh, Type type = Type::STATIC);
    ~BakedMesh();

    /// @brief Update buffered mesh
    /// @attention If you update mesh, you should call this method then
    void updateBufferedMesh();

    /// @brief Get vertex array object
    /// @return Vertex array object
    [[nodiscard]] GLuint getVAO() const;

    /// @brief Get vertex buffer object
    /// @return Vertex buffer object
    [[nodiscard]] GLuint getVBO() const;

    /// @brief Get index buffer object
    /// @return Index buffer object
    [[nodiscard]] GLuint getIBO() const;

    /// @brief Get indices count
    /// @return Indices count
    [[nodiscard]] size_t getIndicesCount() const;
  };
} // unreal_fluid::render::mesh

// end of BakedMesh.h
