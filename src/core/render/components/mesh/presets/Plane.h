/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Plane.h
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "../BasicMesh.h"

namespace unreal_fluid::render::mesh {
  class Plane : public BasicMesh {
  public:
    Plane(float width, float height, unsigned int widthSegments = 1, unsigned int heightSegments = 1,
          vec3f forward = {0.f, 0.f, 1.f}, vec3f right = {1.f, 0.f, 0.f});
  };
} // unreal_fluid::render::mesh

// end of Plane.h
