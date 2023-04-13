/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Cube.cxx
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "Cube.h"

using namespace unreal_fluid::render::mesh;

Cube::Cube(float size) {
  vertices = {
      // front
      {{ size,  size,  size}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
      {{-size,  size,  size}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
      {{ size, -size,  size}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
      {{-size, -size,  size}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
      // back
      {{ size,  size, -size}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},
      {{ size, -size, -size}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
      {{-size,  size, -size}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
      {{-size, -size, -size}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
      // left
      {{-size,  size,  size}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
      {{-size,  size, -size}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
      {{-size, -size,  size}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
      {{-size, -size, -size}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
      // right
      {{ size,  size,  size}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
      {{ size, -size,  size}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
      {{ size,  size, -size}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
      {{ size, -size, -size}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
      // top
      {{ size,  size,  size}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
      {{ size,  size, -size}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
      {{-size,  size,  size}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
      {{-size,  size, -size}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
      // bottom
      {{ size, -size,  size}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
      {{-size, -size,  size}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
      {{ size, -size, -size}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
      {{-size, -size, -size}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
  };

  indices = {
       0,  1,  2,  3, RESET_INDEX, // front
       4,  5,  6,  7, RESET_INDEX, // back
       8,  9, 10, 11, RESET_INDEX, // left
      12, 13, 14, 15, RESET_INDEX, // right
      16, 17, 18, 19, RESET_INDEX, // top
      20, 21, 22, 23, RESET_INDEX, // bottom
  };

  rtVertices = vertices;
  meshType = 3;
}

// end of Cube.cxx
