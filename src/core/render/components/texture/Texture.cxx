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

#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../../../utils/external/image_loader/stb_image.h"

void unreal_fluid::render::Texture::_generateTexture() {
  if (_textureID == -1)
    glGenTextures(1, &_textureID);

  glBindTexture(_dimensions, _textureID);
  switch (_dimensions) {
    case GL_TEXTURE_2D:
      glTexImage2D(GL_TEXTURE_2D, 0, _internalFormat,
                   _width, _height,
                   0, _format, _type, nullptr);
      break;
    case GL_TEXTURE_3D:
      glTexImage3D(GL_TEXTURE_3D, 0, _internalFormat,
                   _width, _height, _depth,
                   0, _format, _type, nullptr);
      break;
    default:
      assert(false);
  }

  if (_internalFormat == GL_DEPTH_COMPONENT)
    return;

  glGenerateMipmap(_dimensions);
  glTexParameteri(_dimensions, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(_dimensions, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(_dimensions, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(_dimensions, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void unreal_fluid::render::Texture::_initTexture(int width, int height, int depth, std::size_t components, std::size_t componentType) {
  switch (components) {
    case 1:
      _internalFormat = GL_R;
      _format = GL_RED;
      break;
    case 2:
      _internalFormat = GL_RG;
      _format = GL_RG;
      break;
    case 3:
      _internalFormat = GL_RGB;
      _format = GL_RGB;
      break;
    case 4:
      _internalFormat = GL_RGBA;
      _format = GL_RGBA;
      break;
    case 5:
      _internalFormat = GL_DEPTH_COMPONENT;
      _format = GL_DEPTH_COMPONENT;
      break;
    default:
      assert(false);
  }

  switch (componentType) {
    case 1:
      _type = GL_UNSIGNED_BYTE;
      break;
    case 4:
      _type = GL_FLOAT;
      break;
    default:
      assert(false);
  }

  resize(width, height, depth);
}

unreal_fluid::render::Texture::Texture(std::size_t components, std::size_t componentType) {
  _initTexture(0, 0, 0, components, componentType);
}

unreal_fluid::render::Texture::Texture(int width, int height, std::size_t components, std::size_t componentType) {
  _initTexture(width, height, 0, components, componentType);
}

unreal_fluid::render::Texture::Texture(int width, int height, int depth, std::size_t components, std::size_t componentType) {
  _initTexture(width, height, depth, components, componentType);
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

  if (_textureID == -1) {
    _dimensions = GL_TEXTURE_2D;
    if (depth > 0)
      _dimensions = GL_TEXTURE_3D;

    _generateTexture();

    return;
  }

  glBindTexture(_dimensions, _textureID);
  switch (_dimensions) {
    case GL_TEXTURE_2D:
      glTexImage2D(GL_TEXTURE_2D, 0, _internalFormat,
                   _width, _height,
                   0, _format, _type, nullptr);
      break;
    case GL_TEXTURE_3D:
      glTexImage3D(GL_TEXTURE_3D, 0, _internalFormat,
                   _width, _height, _depth,
                   0, _format, _type, nullptr);
      break;
    default:
      assert(false);
  }

  if (_internalFormat == GL_DEPTH_COMPONENT)
    return;

  glGenerateMipmap(_dimensions);
}

void unreal_fluid::render::Texture::write(const void *data) {
  assert(data != nullptr);

  glBindTexture(_dimensions, _textureID);
  switch (_dimensions) {
    case GL_TEXTURE_2D:
      glTexSubImage2D(_dimensions, 0, 0, 0,
                      _width, _height,
                      GL_RGBA, GL_UNSIGNED_BYTE, data);
      break;
    case GL_TEXTURE_3D:
      glTexSubImage3D(_dimensions, 0, 0, 0, 0,
                      _width, _height, _depth,
                      GL_RGBA, GL_UNSIGNED_BYTE, data);
      break;
    default:
      assert(false);
  }
  glGenerateMipmap(_dimensions);
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
