/***************************************************************
* Copyright (C) 2023
*    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
*    HSE SPb (Higher school of economics in Saint-Petersburg).
***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : Cube.cxx
 * FILE AUTHORS            : Serkov Alexander.
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#include "Cube.h"

using namespace unreal_fluid::render::mesh;

Cube::Cube(vec3f size, vec3f position) {
  size /= 2.0f;

  float x = size.x;
  float y = size.y;
  float z = size.z;

  float dx = position.x;
  float dy = position.y;
  float dz = position.z;

  float left =   -x + dx;
  float right =   x + dx;
  float bottom = -y + dy;
  float top =     y + dy;
  float back =   -z + dz;
  float front =   z + dz;

  vertices = {
      // front
      {{right,    top, front}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
      {{ left,    top, front}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
      {{right, bottom, front}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
      {{ left, bottom, front}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
      // back
      {{right,    top,  back}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},
      {{right, bottom,  back}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
      {{ left,    top,  back}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
      {{ left, bottom,  back}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
      // left
      {{ left,    top, front}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
      {{ left,    top,  back}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
      {{ left, bottom, front}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
      {{ left, bottom,  back}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
      // right
      {{right,    top, front}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
      {{right, bottom, front}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
      {{right,    top,  back}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
      {{right, bottom,  back}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
      // top
      {{right,    top, front}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
      {{right,    top,  back}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
      {{ left,    top, front}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
      {{ left,    top,  back}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
      // bottom
      {{right, bottom, front}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
      {{ left, bottom, front}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
      {{right, bottom,  back}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
      {{ left, bottom,  back}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
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
