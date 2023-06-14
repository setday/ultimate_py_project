/***************************************************************
* Copyright (C) 2023
*    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
*    HSE SPb (Higher school of economics in Saint-Petersburg).
***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : ShaderManager.cxx
 * FILE AUTHORS            : Serkov Alexander.
 * PURPOSE                 : Compile and store shaders
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#include <filesystem>
#include <fstream>
#include <unordered_map>

#include "ShaderManager.h"

#define SHADERS_PATH "../src/sub_programs/shaders/"

using namespace unreal_fluid::render;

ShaderManager::ShaderManager() {
  _shaders.reserve(10);
  _shaderPaths.reserve(10);
  _programs.reserve(10);
}

const Shader *ShaderManager::LoadShader(std::string_view path) {
  _shaderPaths.emplace_back(path.data());

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
  std::unique_ptr<Shader> shader;

  if (fileType == "vert") {
    shader = std::make_unique<Shader>(Shader::Type::VERTEX);
  } else if (fileType == "frag") {
    shader = std::make_unique<Shader>(Shader::Type::FRAGMENT);
  } else {
    LOG_ERROR("ShaderManager : Unknown shader type: ", path);
    return nullptr;
  }

  if (!shader->build(shaderSource)) {
    std::string infoLog;

    shader->getLog(infoLog);
    LOG_ERROR("ShaderManager : Shader (", path, ") compilation failed: ", infoLog);

    return nullptr;
  }

  _shaders.push_back(std::move(shader));

  return _shaders.back().get();
}

ShaderProgram *ShaderManager::CreateProgram(const std::vector<const Shader *> &shaders) {
  std::unique_ptr<ShaderProgram> program = std::make_unique<ShaderProgram>();

  for (auto *shader : shaders) {
    program->attachShader(shader);
  }

  if (!program->linkProgram()) {
    std::string infoLog;

    program->getLog(infoLog);
    LOG_ERROR("ShaderManager : Program linking failed: ", infoLog);

    return nullptr;
  }

  _programs.push_back(std::move(program));

  return _programs.back().get();
}

ShaderProgram *ShaderManager::LoadProgram(const std::vector<std::string> &paths) {
  std::vector<const Shader *> loaded(paths.size());

  for (int i = 0; i < paths.size(); ++i) {
    loaded[i] = LoadShader(paths[i]);

    if (!loaded[i]) {
      for (int j = 0; j < i; ++j) {
        delete loaded[j];
      }

      return nullptr;
    }
  }

  std::unordered_map<Shader::Type, int> types;

  for (auto *shader : loaded) {
    types[shader->getType()]++;

    if (types[shader->getType()] > 1) {
      LOG_ERROR("ShaderManager : Can't load program with multiple shaders of the same type");

      return nullptr;
    }
  }

  return CreateProgram(loaded);
}

ShaderProgram *ShaderManager::LoadProgram(std::string_view dir) {
  std::vector<std::string> paths;
  std::string realPath = std::string(SHADERS_PATH) + dir.data();
  std::filesystem::directory_iterator dirIt(realPath);

  for (auto &file : dirIt) {
    paths.push_back(dir.data() + file.path().filename().string());
  }

  return LoadProgram(paths);
}

void ShaderManager::ReloadShader(Shader *shader) {
  int index = -1;

  for (int i = 0; i < _shaders.size(); ++i) {
    if (_shaders[i].get() == shader) {
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

  if (!shader->build(shaderSource)) {
    std::string infoLog;

    shader->getLog(infoLog);
    LOG_ERROR("ShaderManager : Shader (", path, ") compilation failed: ", infoLog);

    return;
  }
}

void ShaderManager::ReloadShaders() {
  for (auto const & _shader : _shaders) {
    ReloadShader(_shader.get());
  }

  for (auto const & _program : _programs) {
    _program->reattachShaders();
  }
}

ShaderProgram *DefaultShaderManager::_defaultProgram = nullptr;
ShaderProgram *DefaultShaderManager::_rtProgram = nullptr;
ShaderProgram *DefaultShaderManager::_postProcessingProgram = nullptr;
DefaultShaderManager DefaultShaderManager::_instance = DefaultShaderManager();

ShaderProgram *DefaultShaderManager::GetDefaultProgram() {
  if (_defaultProgram != nullptr)
    return _defaultProgram;

  _defaultProgram = _instance.LoadProgram("default/");

  if (_defaultProgram == nullptr)
    Logger::logFatal("DefaultShaderManager : Default program is not loaded!",
                     "It can cause a segmentation fault, so the program will be closed!");

  Logger::logInfo("DefaultShaderManager : Default program is loaded!");

  return _defaultProgram;
}

ShaderProgram *DefaultShaderManager::GetRayTracingProgram() {
  if (_rtProgram != nullptr)
    return _rtProgram;

  _rtProgram = _instance.LoadProgram("rt/");

  if (_rtProgram == nullptr)
    Logger::logFatal("DefaultShaderManager : Ray tracing program is not loaded!",
                     "It can cause a segmentation fault, so the program will be closed!");

  Logger::logInfo("DefaultShaderManager : Ray tracing program is loaded!");

  return _rtProgram;
}

ShaderProgram *DefaultShaderManager::GetPostProcessingProgram() {
  if (_postProcessingProgram != nullptr)
    return _postProcessingProgram;

  _postProcessingProgram = _instance.LoadProgram("pp/");

  if (_postProcessingProgram == nullptr)
    Logger::logFatal("DefaultShaderManager : Post processing program is not loaded!",
                     "It can cause a segmentation fault, so the program will be closed!");

  Logger::logInfo("DefaultShaderManager : Post processing program is loaded!");

  return _postProcessingProgram;
}

ShaderProgram *DefaultShaderManager::GetGasProgram() {
  static ShaderProgram *program = nullptr;

  if (program != nullptr)
    return program;

  program = _instance.LoadProgram("gas/");

  if (program == nullptr)
    Logger::logFatal("DefaultShaderManager : Gas program is not loaded!",
                     "It can cause a segmentation fault, so the program will be closed!");

  Logger::logInfo("DefaultShaderManager : Gas program is loaded!");

  return program;
}

void DefaultShaderManager::ReloadShaders() {
  static_cast<ShaderManager &>(_instance).ReloadShaders();
}

// end of ShaderManager.cxx
