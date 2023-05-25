/***************************************************************
 * Copyright (C) 2023
 *    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : Texture.cxx
 * FILE AUTHORS            : Serkov Alexander.
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#include "Texture.h"

unreal_fluid::render::Texture::Texture(int width, int height) : _width(width), _height(height) {
  glGenTextures(1, &_textureID);

  glBindTexture(GL_TEXTURE_2D, _textureID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F,
               width, height,
               0, GL_RGBA, GL_FLOAT, nullptr);
  glGenerateMipmap(GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

unreal_fluid::render::Texture::~Texture() {
  if (_textureID == -1)
    return;

  glDeleteTextures(1, &_textureID);
}

void unreal_fluid::render::Texture::resize(int width, int height) {
  glBindTexture(GL_TEXTURE_2D, _textureID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F,
               width, height,
               0, GL_RGBA, GL_FLOAT, nullptr);
  glGenerateMipmap(GL_TEXTURE_2D);
}

void unreal_fluid::render::Texture::bind() {
  glBindTexture(GL_TEXTURE_2D, _textureID);
}

GLuint unreal_fluid::render::Texture::getID() {
  return _textureID;
}

// end of Texture.cxx
