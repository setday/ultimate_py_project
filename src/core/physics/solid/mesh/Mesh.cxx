/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : SolidMesh.cxx
 * PURPOSE   : Simple mesh plane which is static
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "Mesh.h"

using namespace unreal_fluid::physics::solid;

Mesh::Mesh(const std::vector<Triangle> &triangles) : triangles(triangles) {}

unreal_fluid::physics::IPhysicalObject::Type Mesh::getType() {
  return Type::SOLID_MESH;
}

void *Mesh::getData() {
  return &triangles;
}

// end of SolidMesh.cxx
