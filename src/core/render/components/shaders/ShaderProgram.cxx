/***************************************************************
 * Copyright (C) 2023
 *    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : ShaderProgram.cxx
 * FILE AUTHORS            : Serkov Alexander.
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#include <memory>

#include "ShaderProgram.h"

using namespace unreal_fluid::render;

ShaderProgram::ShaderProgram() {
  _programID = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
  glDeleteProgram(_programID);
}

void ShaderProgram::attachShader(const Shader *shader) {
  glAttachShader(_programID, shader->getShaderId());

  _attachedShaders.push_back(shader);
}

void ShaderProgram::reattachShaders() {
  glDeleteProgram(_programID);

  _programID = glCreateProgram();

  for (const auto &shader : _attachedShaders) {
    glAttachShader(_programID, shader->getShaderId());
  }

  glLinkProgram(_programID);
}

bool ShaderProgram::linkProgram() const {
  glLinkProgram(_programID);

  GLint success;
  glGetProgramiv(_programID, GL_LINK_STATUS, &success);

  return success;
}

void ShaderProgram::activate() {
  // GLint success;
  // glGetProgramiv(_programID, GL_LINK_STATUS, &success);
  // if (!success) {
  //   return;
  // }

  // glValidateProgram(_programID);

  _currentTextureId = 0;

  glUseProgram(_programID);
}

[[nodiscard]]
unsigned int ShaderProgram::getId() const {
  return _programID;
}

void ShaderProgram::getLog(std::string &log) const {
  GLint length;

  glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &length);

  if (length > 0) {
    auto logBuffer = std::unique_ptr<char[]>(new char[length]);

    glGetProgramInfoLog(_programID, length, nullptr, logBuffer.get());

    log = logBuffer.get();
  }
}

void ShaderProgram::bindUniformAttribute(std::string_view name, int attribute) const {
  GLint location = glGetUniformLocation(_programID, name.data());
  if (location == -1)
    return;
  glUniform1i(location, attribute);
}

void ShaderProgram::bindUniformAttribute(std::string_view name, float attribute) const {
  GLint location = glGetUniformLocation(_programID, name.data());
  if (location == -1)
    return;
  glUniform1f(location, attribute);
}

void ShaderProgram::bindUniformAttribute(std::string_view name, const vec2f &attribute) const {
  GLint location = glGetUniformLocation(_programID, name.data());
  if (location == -1)
    return;
  glUniform2f(location, attribute.x, attribute.y);
}

void ShaderProgram::bindUniformAttribute(std::string_view name, const vec3f &attribute) const {
  GLint location = glGetUniformLocation(_programID, name.data());
  if (location == -1)
    return;
  glUniform3f(location, attribute.x, attribute.y, attribute.z);
}

void ShaderProgram::bindUniformAttribute(std::string_view name, const mat4 &attribute, bool inverseView) const {
  GLint location = glGetUniformLocation(_programID, name.data());
  if (location == -1)
    return;
  if (inverseView) {
    Logger::logError("Inverse view is not supported yet");
    // glUniformMatrix4fv(location, 1, GL_FALSE, attribute.inverse_data()); /// TODO: made inverse view
  } else {
    glUniformMatrix4fv(location, 1, GL_FALSE, attribute.data());
  }
}

void ShaderProgram::bindUniformAttribute(std::string_view name, const Texture *attribute) {
  if (attribute == nullptr)
    return;

  GLint location = glGetUniformLocation(_programID, name.data());
  if (location == -1)
    return;

  glActiveTexture(GL_TEXTURE0 + _currentTextureId);
  attribute->bind();
  glUniform1i(location, _currentTextureId);

  _currentTextureId++;
}

void ShaderProgram::bindTexturesNumber() const {
  bindUniformAttribute("texturesCount", _currentTextureId);
}

// end of ShaderProgram.cxx
