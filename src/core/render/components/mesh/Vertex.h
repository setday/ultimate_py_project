/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Vertex.h
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include "../../../../Definitions.h"

namespace unreal_fluid::render {
  struct Vertex {
    vec3f position;
    vec3f normal;
    vec2f texCoord;

    Vertex() = default;
    Vertex(vec3f position, vec3f normal, vec2f texCoord) : position(position), normal(normal), texCoord(texCoord) {}
  };
} // render

// end of Vertex.h
