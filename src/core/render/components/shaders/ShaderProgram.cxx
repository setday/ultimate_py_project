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

#include "ShaderProgram.h"

using namespace unreal_fluid::render;

ShaderProgram::ShaderProgram() {
  _programID = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
  glDeleteProgram(_programID);
}

void ShaderProgram::AttachShader(const Shader *shader) {
  glAttachShader(_programID, shader->GetShaderID());

  _attachedShaders.push_back(shader);
}

void ShaderProgram::ReattachShaders() {
  glDeleteProgram(_programID);

  _programID = glCreateProgram();

  for (const auto &shader : _attachedShaders) {
    glAttachShader(_programID, shader->GetShaderID());
  }

  glLinkProgram(_programID);
}

bool ShaderProgram::LinkProgram() const {
  glLinkProgram(_programID);

  GLint success;
  glGetProgramiv(_programID, GL_LINK_STATUS, &success);

  return success;
}

void ShaderProgram::Execute() const {
  GLint success;
  glGetProgramiv(_programID, GL_LINK_STATUS, &success);
  if (!success) {
    return;
  }

  glValidateProgram(_programID);
  glUseProgram(_programID);
}

unsigned int ShaderProgram::GetProgramID() const {
  return _programID;
}

void ShaderProgram::GetLog(std::string &log) const {
  GLint length;

  glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &length);

  if (length > 0) {
    char *logBuffer = new char[length];

    glGetProgramInfoLog(_programID, length, nullptr, logBuffer);

    log = logBuffer;
    delete[] logBuffer;
  }
}

// end of ShaderProgram.cxx
