/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : ShaderProgram.cxx
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
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

void ShaderProgram::activate() const {
  GLint success;
  glGetProgramiv(_programID, GL_LINK_STATUS, &success);
  if (!success) {
    return;
  }

  glValidateProgram(_programID);
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

// end of ShaderProgram.cxx
