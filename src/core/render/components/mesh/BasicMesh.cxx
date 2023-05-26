/***************************************************************
 * Copyright (C) 2023
 *    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : BasicMesh.cxx
 * FILE AUTHORS            : Serkov Alexander.
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#include "BasicMesh.h"

using namespace unreal_fluid::render::mesh;

BasicMesh::BasicMesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices) {
  this->vertices = vertices;
  this->indices = indices;
}

// end of Mesh.cxx
