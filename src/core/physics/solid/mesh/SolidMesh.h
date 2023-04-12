/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : SolidMesh.cxx
 * PURPOSE   : Simple static mesh
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */


#pragma once
#include "../ISolid.h"
#include "Triangle.h"
#include "vector"

namespace unreal_fluid::physics::solid {
  class SolidMesh : public ISolid {

  private:
    std::vector<Triangle> triangles;

  public:
    explicit SolidMesh(const std::vector<Triangle> &triangles);

    void simulate(double dt) override;
    Type getType() override;
    void *getData() override;
  };
} // namespace unreal_fluid::physics::solid
