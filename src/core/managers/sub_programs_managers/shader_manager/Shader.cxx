/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Shader.cxx
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "Shader.h"

using namespace unreal_fluid::render;

Shader::Shader(Type _type) {
  unsigned int glType = 0;

  switch (_type) {
    case Type::VERTEX:
      glType = GL_VERTEX_SHADER;
      break;
    case Type::FRAGMENT:
      glType = GL_FRAGMENT_SHADER;
      break;
    case Type::GEOMETRY:
      glType = GL_GEOMETRY_SHADER;
      break;
    case Type::COMPUTE:
      glType = GL_COMPUTE_SHADER;
      break;
    default:
      break;
  }

  _shaderId = glCreateShader(glType);
}

Shader::~Shader() {
  glDetachShader(_programId, _shaderId);
  glDeleteProgram(_programId);
  glDeleteShader(_shaderId);
}

bool Shader::LoadProgram(std::string_view source) {
  const char *sourcePtr = source.data();

  glShaderSource(_shaderId, 1, &sourcePtr, nullptr);
  glCompileShader(_shaderId);

  GLint success;
  glGetShaderiv(_shaderId, GL_COMPILE_STATUS, &success);
  if (!success) {
    return false;
  }

  _programId = glCreateProgram();

  glAttachShader(_programId, _shaderId);
  glLinkProgram(_programId);
  glGetProgramiv(_programId, GL_LINK_STATUS, &success);
  if (!success) {
    return false;
  }

  return true;
}

void Shader::ExecuteProgram() const {
  if (_programId == 0) {
    return;
  }

  glUseProgram(_programId);
}

GLuint Shader::GetShaderId() const {
  return _shaderId;
}

void Shader::GetLog(std::string &log) const {
  GLint logLength;
  glGetShaderiv(_shaderId, GL_INFO_LOG_LENGTH, &logLength);

  log.resize(logLength);
  glGetShaderInfoLog(_shaderId, logLength, nullptr, log.data());
}

// end of Shader.cxx
