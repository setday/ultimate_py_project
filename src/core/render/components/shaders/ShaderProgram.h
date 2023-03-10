/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : ShaderProgram.h
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "Shader.h"

namespace unreal_fluid::render {
  class ShaderProgram {
  private:
    unsigned int _programID;
    std::vector<const Shader *> _attachedShaders;

  public:
    explicit ShaderProgram();
    ~ShaderProgram();

    /// Attach shader
    /// @param shader Shader
    void AttachShader(const Shader *shader);

    /// Link program
    /// @return True if success
    bool LinkProgram() const;

    /// Reattach shaders
    void ReattachShaders();

    /// Execute program
    void Execute() const;

    /// Get program ID
    /// @return Program ID
    unsigned int GetProgramID() const;

    /// Get log
    /// @param log Log
    void GetLog(std::string &log) const;
  };
} // namespace unreal_fluid::render

// end of ShaderProgram.h
