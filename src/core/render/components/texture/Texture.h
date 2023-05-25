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

    GLuint _textureID = -1;

  public:
    /// @param width - width of the texture
    /// @param height - height of the texture
    Texture(int width, int height);
    ~Texture();

    /// Resize this texture
    /// @param width - width of the texture
    /// @param height - height of the texture
    void resize(int width, int height);

    /// Bind this texture
    void bind();

    /// Get id
    GLuint getID();
  };
}

// end of Texture.h
