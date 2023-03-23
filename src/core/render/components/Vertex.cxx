/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Vertex.cxx
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "Vertex.h"

using namespace unreal_fluid::render;

Vertex::Vertex(vec3f position, vec3f normal, vec3f color) {
  this->position = position;
  this->normal = normal;
  this->color = color;
}

// end of Vertex.cxx