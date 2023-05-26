/***************************************************************
* Copyright (C) 2023
*    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
*    HSE SPb (Higher school of economics in Saint-Petersburg).
***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : Sphere.h
 * FILE AUTHORS            : Serkov Alexander.
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#pragma once

#include "../BasicMesh.h"

namespace unreal_fluid::render::mesh {
  struct Sphere : BasicMesh {
  public:
    Sphere(float radius, unsigned int rings, unsigned int sectors);
  };
} // unreal_fluid::render::mesh

// end of Sphere.h
