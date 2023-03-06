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

#define SHADERS_PATH "src/sub_programs/shaders/"

using namespace unreal_fluid::render;

ShaderManager::ShaderManager() {
  _shaders.reserve(10);
  _shaderPaths.reserve(10);

  glewInit();
}

ShaderManager::~ShaderManager() {
  for (auto *shader : _shaders) {
    delete shader;
  }
}

const Shader *ShaderManager::LoadShader(std::string_view path) {
  _shaderPaths.push_back(path.data());

  std::string realPath = std::string(SHADERS_PATH) + path.data();

  std::ifstream file(realPath);
  if (!file.is_open()) {
    LOG_ERROR("ShaderManager : Can't open shader file: " + realPath);

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
    LOG_ERROR("ShaderManager : Unknown shader type: " + std::string(path));
    return nullptr;
  }

  if (!shader->LoadProgram(shaderSource)) {
    std::string infoLog;

    shader->GetLog(infoLog);
    LOG_ERROR("ShaderManager : Shader (" + std::string(path) + ") compilation failed: " + std::string(infoLog));

    delete shader;

    return nullptr;
  }

  _shaders.push_back(shader);

  return shader;
}

void ShaderManager::ReloadShaders() {
  for (auto *shader : _shaders) {
    delete shader;
  }

  _shaders.clear();

  std::vector<std::string> paths;
  std::copy(_shaderPaths.begin(), _shaderPaths.end(), std::back_inserter(paths));
  _shaderPaths.clear();

  for (auto &path : paths) {
    LoadShader(path);
  }
}

// end of ShaderManager.cxx
