/***************************************************************
 * Copyright (C) 2023
 *    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : Texture.h
 * FILE AUTHORS            : Serkov Alexander.
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#pragma once

#define GLEW_STATIC
#include "GL/glew.h"
#include <GL/gl.h>

#pragma comment(lib, "opengl32")

#include "../../../../Definitions.h"

namespace unreal_fluid::render {
  class Texture {
  private:
    int _width = -1;
    int _height = -1;
    int _depth = -1;

    GLenum _internalFormat = GL_RGBA;
    GLenum _format = GL_RGBA;
    GLenum _type = GL_UNSIGNED_BYTE;

    GLenum _dimensions = 0;

    GLuint _textureID = -1;

  private:
    void _initTexture(int width, int height, int depth, std::size_t components, std::size_t componentSize);

  public:
    /// Create empty texture
    /// @param components - number of components in the texture (1, 2, 3, 4 by default, 5 for depth component)
    /// @param componentSize - size of component (sizeof unsigned char by default)
    explicit Texture(std::size_t components = 4, std::size_t componentSize = sizeof(unsigned char));
    /// Create empty texture 2D
    /// @param width - width of the texture
    /// @param height - height of the texture
    /// @param components - number of components in the texture (1, 2, 3, 4 by default, 5 for depth component)
    /// @param componentSize - size of component (sizeof unsigned char by default)
    explicit Texture(int width, int height, std::size_t components = 4, std::size_t componentSize = sizeof(unsigned char));
    /// Create empty texture 3D
    /// @param width - width of the texture
    /// @param height - height of the texture
    /// @param depth - depth of the texture
    /// @param components - number of components in the texture (1, 2, 3, 4 by default, 5 for depth component)
    /// @param componentSize - size of component (sizeof unsigned char by default)
    explicit Texture(int width, int height, int depth, std::size_t components = 4, std::size_t componentSize = sizeof(unsigned char));
    /// Load texture from file
    /// @param path - path to the file
    /// @return true if texture was loaded, false otherwise
    Texture(std::string_view path);
    ~Texture();

    /// Load texture from file
    /// @param path - path to the file
    /// @return true if texture was loaded, false otherwise
    bool loadFromFile(std::string_view path);

    /// Resize this texture
    /// @param width - width of the texture
    /// @param height - height of the texture
    /// @param depth - depth of the texture (if 0, then texture is 2D)
    /// @attention The dimension of the texture can't be changed.
    /// @attention If you create 2D texture, than depth must be 0.
    void resize(int width, int height, int depth = 0);

    /// Write data to this texture
    /// @param data - data to write
    /// @param xOffset - x offset
    /// @param yOffset - y offset
    /// @attention The size of the data must be equal to the size of the texture.
    /// @attention The data must be in the format of the texture.
    void write(const void* data, int xOffset = 0, int yOffset = 0);

    /// Set pixel in this texture
    /// @param data - data to write
    /// @param x - x position
    /// @param y - y position
    /// @attention The size of the data must be equal to the size of the texture.
    /// @attention The data must be in the format of the texture.
    void setPixel(const void* data, int x, int y);

    /// Bind this texture
    /// @return true if texture was bound, false otherwise
    bool bind() const;

    /// Get id
    GLuint getID() const;
  };
}

// end of Texture.h
