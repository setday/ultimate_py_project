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
    void attachShader(const Shader *shader);

    /// Link program
    /// @return True if success
    bool linkProgram() const;

    /// Reattach shaders
    void reattachShaders();

    /// Activate this program
    void activate() const;

    /// Get program ID
    /// @return Program ID
    [[nodiscard]]
    unsigned int getId() const;

    /// Get log
    /// @param log Log
    void getLog(std::string &log) const;
  };
} // namespace unreal_fluid::render

// end of ShaderProgram.h
