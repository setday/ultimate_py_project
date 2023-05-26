/***************************************************************
 * Copyright (C) 2023
 *    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : Vertex.h
 * FILE AUTHORS            : Serkov Alexander.
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#pragma once

#include "../../../../Definitions.h"

namespace unreal_fluid::render {
  struct Vertex {
    vec3f position;
    vec3f normal;
    vec2f texCoord;

    Vertex() = default;
    Vertex(vec3f position, vec3f normal = {0, 1, 0}, vec2f texCoord = {0, 0}) :
      position(position), normal(normal), texCoord(texCoord) {}
  };
} // render

// end of Vertex.h
