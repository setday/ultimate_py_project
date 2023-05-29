/***************************************************************
 * Copyright (C) 2023
 *    UnrealFluid Team (https://github.com/setday/unreal_fluid) and
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT                 : UnrealFluid
 * AUTHORS OF THIS PROJECT : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev.
 * FILE NAME               : BasicMesh.h
 * FILE AUTHORS            : Serkov Alexander.
 *
 * No part of this file may be changed and used without
 * agreement of authors of this project.
 */

#pragma once

#include <vector>
#include "Vertex.h"

#define RESET_INDEX UINT_MAX

namespace unreal_fluid::render::mesh {
  struct BasicMesh {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    std::vector<Vertex> rtVertices;
    int meshType = 0;

    BasicMesh() = default;

    BasicMesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices) : vertices(vertices),
                                                                                               indices(indices) {}
  };
} // namespace unreal_fluid::render::mesh

// end of BasicMesh.h
