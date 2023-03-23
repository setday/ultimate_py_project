/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Mesh.cxx
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "BasicMesh.h"

using namespace unreal_fluid::render::mesh;

BasicMesh::BasicMesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices) {
  this->vertices = vertices;
  this->indices = indices;
}

// end of Mesh.cxx
