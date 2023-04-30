/***************************************************************
 * Copyright (C) 2023
 *    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : Vertex.cxx
 * FILE AUTHORS            : Serkov Alexander.
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#include "Vertex.h"

using namespace unreal_fluid::render;

Vertex::Vertex(vec3f position, vec3f normal, vec2f texCoord) {
  this->position = position;
  this->normal = normal;
  this->texCoord = texCoord;
}

// end of Vertex.cxx