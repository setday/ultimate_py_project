/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Shader.h
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#define GLEW_STATIC
#include "GL/glew.h"
#include <GL/gl.h>

#pragma comment(lib, "opengl32")

#include "../../../../Definitions.h"

namespace unreal_fluid::render {
  class Shader {
  public:
    enum class Type {
      VERTEX,
      FRAGMENT,
      GEOMETRY,
      TESS_CONTROL,
      TESS_EVALUATION,
      COMPUTE
    };

  private:
    GLuint _shaderID;
    Type _type;

  public:
    explicit Shader(Type _type);
    ~Shader();

    /// Load program from string
    /// @param source Source code
    /// @return True if success
    bool LoadProgram(std::string_view source);

    /// Execute program
    void ExecuteProgram() const;

    /// Get shader id
    /// @return Shader id
    GLuint GetShaderID() const;
    /// Get log
    /// @param log Log
    void GetLog(std::string &log) const;
  };
} // namespace unreal_fluid::render

// end of Shader.h
