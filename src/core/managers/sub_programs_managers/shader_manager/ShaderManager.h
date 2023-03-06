/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : ShaderManager.h
 * PURPOSE   : Compile and store shaders
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include <string>
#include <vector>

#include "../../../../Definitions.h"

#include "Shader.h"

namespace unreal_fluid::render {
  class ShaderManager {
  private:
    std::vector<Shader *> _shaders;
    std::vector<std::string> _shaderPaths;

  public:
    ShaderManager();
    ~ShaderManager();

    /// Load shader from file
    /// @param path Path to shader file
    /// @return Shader pointer
    const Shader * LoadShader(std::string_view path);

    /// Reload all shaders
    void ReloadShaders();
  };
} // namespace unreal_fluid::render

// end of ShaderManager.h
