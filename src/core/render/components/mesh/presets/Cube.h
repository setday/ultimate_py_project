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
  class Cube : public BasicMesh {
  public:
    Cube(float size);
  };
} // unreal_fluid::render::mesh

// end of Cube.h
