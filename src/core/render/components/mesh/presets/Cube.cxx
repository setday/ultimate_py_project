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
      {{-size, -size,  size}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
      {{ size, -size,  size}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
      {{ size,  size,  size}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
      {{-size,  size,  size}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
      // back
      {{-size, -size, -size}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
      {{ size, -size, -size}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
      {{ size,  size, -size}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},
      {{-size,  size, -size}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
      // left
      {{-size, -size, -size}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
      {{-size, -size,  size}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
      {{-size,  size,  size}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
      {{-size,  size, -size}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
      // right
      {{ size, -size, -size}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
      {{ size, -size,  size}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
      {{ size,  size,  size}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
      {{ size,  size, -size}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
      // top
      {{-size,  size, -size}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
      {{ size,  size, -size}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
      {{ size,  size,  size}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
      {{-size,  size,  size}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
      // bottom
      {{-size, -size, -size}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
      {{ size, -size, -size}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
      {{ size, -size,  size}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
      {{-size, -size,  size}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
  };

  indices = {
      0,  1,  2,  2,  3,  0,  // front
      6,  5,  4,  4,  7,  6,  // back
      8,  9,  10, 10, 11, 8,  // left
      14, 13, 12, 12, 15, 14,  // right
      18, 17, 16, 16, 19, 18,  // top
      20, 21, 22, 22, 23, 20,  // bottom
  };

  rtVertices = vertices;
  meshType = 3;
}

// end of Cube.cxx
