/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Mesh.h
 * PURPOSE   : ${PURPOSE}
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once

#include <vector>

#include "Vertex.h"

namespace unreal_fluid::render::mesh {
  class BasicMesh {
  public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    std::vector<Vertex> rtVertices;
    int meshType = 0;

  public:
    BasicMesh() = default;
    BasicMesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices);
  };
} // unreal_fluid::render::mesh

// end of Mesh.h
