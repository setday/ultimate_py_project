/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Cube.h
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "../BasicMesh.h"

namespace unreal_fluid::render::mesh {
  struct Cube : BasicMesh {
  public:
    /// Creates cube with specified size.
    /// @param size Size of cube in each dimension.
    /// @param position Position of cube.
    Cube(vec3f size, vec3f position = {0, 0, 0});
  };
} // unreal_fluid::render::mesh

// end of Cube.h
