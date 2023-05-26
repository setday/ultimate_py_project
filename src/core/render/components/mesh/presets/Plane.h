/***************************************************************
* Copyright (C) 2023
*    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
*    HSE SPb (Higher school of economics in Saint-Petersburg).
***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : Plane.h
 * FILE AUTHORS            : Serkov Alexander.
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#pragma once

#include "../BasicMesh.h"

namespace unreal_fluid::render::mesh {
  struct Plane : BasicMesh {
  public:
    Plane(float width, float height, unsigned int widthSegments = 1, unsigned int heightSegments = 1, vec3f forward = {0.f, 0.f, 1.f}, vec3f right = {1.f, 0.f, 0.f});
  };
} // namespace unreal_fluid::render::mesh
