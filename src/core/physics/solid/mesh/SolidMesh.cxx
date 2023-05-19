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

#include "SolidMesh.h"

using namespace unreal_fluid::physics::solid;

SolidMesh::SolidMesh(const std::vector<Triangle> &triangles) : triangles(triangles) {}

unreal_fluid::physics::IPhysicalObject::Type SolidMesh::getType() {
  return Type::SOLID_MESH;
}

void *SolidMesh::getData() {
  Logger::logInfo("from mesh", triangles.size());
  return &triangles;
}

void SolidMesh::simulate(double dt) {
  /// static mesh doesn't need any simulate implementation
}

// end of SolidMesh.cxx
