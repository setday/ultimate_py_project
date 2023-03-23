/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : SimpleFluidContainer.cxx
 * PURPOSE   : Simple fluid simulation class, which implements ASS collision
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */


#include "SolidMesh.h"

#include <utility>

unreal_fluid::physics::solid::SolidMesh::SolidMesh(std::vector<Triangle> triangles) : triangles(std::move(triangles)) {}

unreal_fluid::physics::IPhysicalObject::Type unreal_fluid::physics::solid::SolidMesh::getType() {
    return Type::SOLID_MESH;
}

void *unreal_fluid::physics::solid::SolidMesh::getData() {
    return &triangles;
}

void unreal_fluid::physics::solid::SolidMesh::simulate(double dt) {}
