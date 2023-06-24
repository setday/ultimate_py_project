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

#define TEXTURE_PATH "../assets/textures/"

#define GL_TEX_IMAGE_2D(width, height, format, type, data) \
  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, type, data)
#define GL_TEX_IMAGE_3D(width, height, depth, format, type, data) \
  glTexImage3D(GL_TEXTURE_3D, 0, format, width, height, depth, 0, format, type, data)

#define GL_TEX_SUB_IMAGE_2D(xoffset, yoffset, width, height, format, type, data) \
  glTexSubImage2D(GL_TEXTURE_2D, 0, xoffset, yoffset, width, height, format, type, data)
#define GL_TEX_SUB_IMAGE_3D(xoffset, yoffset, zoffset, width, height, depth, format, type, data) \
  glTexSubImage3D(GL_TEXTURE_3D, 0, xoffset, yoffset, zoffset, width, height, depth, format, type, data)

#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../../../utils/external/image_loader/stb_image.h"

void unreal_fluid::render::Texture::_initTexture(int width, int height, int depth, std::size_t components, std::size_t componentSize) {
  static GLenum internalFormatTable[5][2] = {
      /// ubyte     float
      {GL_R8,     GL_R32F},     // 1 component
      {GL_RG8,    GL_RG32F},    // 2 components
      {GL_RGB8,   GL_RGB32F},   // 3 components
      {GL_RGBA8,  GL_RGBA32F},  // 4 components
      {GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT32F}  // 5 components
  };
  static GLenum formatTable[5] = {
      GL_RED,   // 1 component
      GL_RG,    // 2 components
      GL_RGB,   // 3 components
      GL_RGBA,  // 4 components
      GL_DEPTH_COMPONENT  // 5 components
  };
  static GLenum typeTable[2] = {
      GL_UNSIGNED_BYTE, // 1 byte
      GL_FLOAT          // 4 bytes
  };

  int typeID = (componentSize == 1) ? 0 : 1;

  _dimensions = (depth == 0) ? GL_TEXTURE_2D : GL_TEXTURE_3D;

  _internalFormat = internalFormatTable[components - 1][typeID];
  _format = formatTable[components - 1];
  _type = typeTable[typeID];

  resize(width, height, depth);

  if (_internalFormat == GL_DEPTH_COMPONENT)
    return;

  glTexParameteri(_dimensions, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /// TODO: add option to change this
  glTexParameteri(_dimensions, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /// TODO: add option to change this
  glTexParameteri(_dimensions, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(_dimensions, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  glTexParameteri(_dimensions, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
}

unreal_fluid::render::Texture::Texture(std::size_t components, std::size_t componentSize) {
  _initTexture(0, 0, 0, components, componentSize);
}

unreal_fluid::render::Texture::Texture(int width, int height, std::size_t components, std::size_t componentSize) {
  _initTexture(width, height, 0, components, componentSize);
}

unreal_fluid::render::Texture::Texture(int width, int height, int depth,
                                       std::size_t components, std::size_t componentSize) {
  _initTexture(width, height, depth, components, componentSize);
}

unreal_fluid::render::Texture::Texture(std::string_view path) {
  loadFromFile(path);
}

unreal_fluid::render::Texture::~Texture() {
  if (_textureID == -1)
    return;

  glDeleteTextures(1, &_textureID);

  _textureID = -1;
}

bool unreal_fluid::render::Texture::loadFromFile(std::string_view path) {
  assert(!path.empty());

  std::string realPath = std::string(TEXTURE_PATH) + path.data();

  int channels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char* data = stbi_load(realPath.data(), &_width, &_height, &channels, 4);

  if (data == nullptr)
    return false;

  resize(_width, _height);
  write(data);

  stbi_image_free(data);

  return true;
}

void unreal_fluid::render::Texture::resize(int width, int height, int depth) {
  assert(width >= 0 && height >= 0 && depth >= 0);

  _width = width;
  _height = height;
  _depth = depth;

  if (_textureID == -1)
    glGenTextures(1, &_textureID);

  glBindTexture(_dimensions, _textureID);
  if (_dimensions == GL_TEXTURE_2D)
    GL_TEX_IMAGE_2D(_width, _height, _format, _type, nullptr);
  else if (_dimensions == GL_TEXTURE_3D)
    GL_TEX_IMAGE_3D(_width, _height, _depth, _format, _type, nullptr);
  else
    assert(false);

  if (_internalFormat == GL_DEPTH_COMPONENT)
    return;

  glGenerateMipmap(_dimensions);
}

void unreal_fluid::render::Texture::write(const void *data, int xOffset, int yOffset) {
  assert(data != nullptr);

  glBindTexture(_dimensions, _textureID);
  if (_dimensions == GL_TEXTURE_2D)
    GL_TEX_SUB_IMAGE_2D(xOffset, yOffset,
                        _width - xOffset, _height - yOffset,
                        _format, _type, data);
  else if (_dimensions == GL_TEXTURE_3D)
    GL_TEX_SUB_IMAGE_3D(xOffset, yOffset, 0,
                        _width - xOffset, _height - yOffset, _depth,
                        _format, _type, data);
  else
    assert(false);
  glGenerateMipmap(_dimensions);
}

void unreal_fluid::render::Texture::setPixel(const void *data, int x, int y) {
  assert(data != nullptr);

  glBindTexture(_dimensions, _textureID);
  if (_dimensions == GL_TEXTURE_2D)
    GL_TEX_SUB_IMAGE_2D(x, y,
                        1, 1,
                        _format, _type, data);
  else if (_dimensions == GL_TEXTURE_3D)
    GL_TEX_SUB_IMAGE_3D(x, y, 0,
                        1, 1, 1,
                        _format, _type, data);
  else
    assert(false);

  // glGenerateMipmap(_dimensions);
}

bool unreal_fluid::render::Texture::bind() const {
  if (_textureID == -1)
    return false;

  glBindTexture(_dimensions, _textureID);

  return true;
}

GLuint unreal_fluid::render::Texture::getID() const {
  return _textureID;
}

// end of Texture.cxx
