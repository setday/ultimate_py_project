/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : ShaderManager.cxx
 * PURPOSE   : Compile and store shaders
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include <fstream>

#include "ShaderManager.h"

#define SHADERS_PATH "../src/sub_programs/shaders/"

using namespace unreal_fluid::render;

ShaderManager::ShaderManager() {
  _shaders.reserve(10);
  _shaderPaths.reserve(10);
  _programs.reserve(10);

  glewInit();

  // Load default shaders
  const Shader *vertBase = LoadShader("default/simple.vert");
  const Shader *fragBase = LoadShader("default/simple.frag");

  if (vertBase == nullptr || fragBase == nullptr)
    Logger::logFatal("ShaderManager : Can't load default shaders");

  _defaultProgram = CreateProgram({vertBase, fragBase});

  // Load ray tracing shaders
  const Shader *vertRT = LoadShader("rt/rt.vert");
  const Shader *fragRT = LoadShader("rt/rt.frag");

  if (fragRT == nullptr || vertRT == nullptr)
    Logger::logFatal("ShaderManager : Can't load ray tracing shaders");

  _rtProgram = CreateProgram({vertRT, fragRT});
}

ShaderManager::~ShaderManager() {
  for (auto *shader : _shaders) {
    delete shader;
  }
  for (auto *program : _programs) {
    delete program;
  }
}

const Shader *ShaderManager::LoadShader(std::string_view path) {
  _shaderPaths.push_back(path.data());

  std::string realPath = std::string(SHADERS_PATH) + path.data();

  std::ifstream file(realPath);
  if (!file.is_open()) {
    LOG_ERROR("ShaderManager : Can't open shader file: ", realPath);

    return nullptr;
  }

  std::string shaderSource;
  std::string line;

  while (std::getline(file, line)) {
    shaderSource += line + '\n';
  }

  file.close();

  auto fileType = std::string(path.substr(path.find_last_of('.') + 1));
  Shader *shader;

  if (fileType == "vert") {
    shader = new Shader(Shader::Type::VERTEX);
  } else if (fileType == "frag") {
    shader = new Shader(Shader::Type::FRAGMENT);
  } else {
    LOG_ERROR("ShaderManager : Unknown shader type: ", path);
    return nullptr;
  }

  if (!shader->LoadProgram(shaderSource)) {
    std::string infoLog;

    shader->GetLog(infoLog);
    LOG_ERROR("ShaderManager : Shader (", path, ") compilation failed: ", infoLog);

    delete shader;

    return nullptr;
  }

  _shaders.push_back(shader);

  return shader;
}

const ShaderProgram *ShaderManager::GetDefaultProgram() const {
  return _defaultProgram;
}

const ShaderProgram *ShaderManager::GetRayTracingProgram() const {
  return _rtProgram;
}

const ShaderProgram *ShaderManager::CreateProgram(const std::vector<const Shader *> &shaders) {
  auto *program = new ShaderProgram();

  _programs.push_back(program);

  for (auto *shader : shaders) {
    program->AttachShader(shader);
  }

  if (!program->LinkProgram()) {
    std::string infoLog;

    program->GetLog(infoLog);
    LOG_ERROR("ShaderManager : Program linking failed: ", infoLog);

    delete program;

    return nullptr;
  }

  return program;
}

void ShaderManager::ReloadShader(Shader *shader) {
  int index = -1;

  for (int i = 0; i < _shaders.size(); ++i) {
    if (_shaders[i] == shader) {
      index = i;
      break;
    }
  }

  if (index == -1) {
    LOG_ERROR("ShaderManager : Can't find shader to reload");
    return;
  }

  std::string path = std::string(SHADERS_PATH) + _shaderPaths[index];

  std::fstream file(path);
  if (!file.is_open()) {
    LOG_ERROR("ShaderManager : Can't open shader file: ", path);
    return;
  }

  std::string shaderSource;
  std::string line;

  while (std::getline(file, line)) {
    shaderSource += line + '\n';
  }

  file.close();

  if (!shader->LoadProgram(shaderSource)) {
    std::string infoLog;

    shader->GetLog(infoLog);
    LOG_ERROR("ShaderManager : Shader (", path, ") compilation failed: ", infoLog);

    return;
  }
}

void ShaderManager::ReloadShaders() {
  for (auto & _shader : _shaders) {
    ReloadShader(_shader);
  }

  for (auto & _program : _programs) {
    _program->ReattachShaders();
  }
}

// end of ShaderManager.cxx
