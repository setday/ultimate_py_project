/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Plane.h
 * PURPOSE   : class to create planes for bounding box
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#pragma once
#include "../ISolid.h"

namespace unreal_fluid::physics::solid {
  class Plane : public ISolid {
    void simulate(double dt) override{};

  public:
    double height, width;
    vec3 normal, front, right;

    /// TODO get position in front
    Plane(double height, double width, vec3 position, vec3 normal = {0, 1, 0}, vec3 right = {0, 0, 1});
    IPhysicalObject::Type getType() override;
    void *getData() override;
  };
} // namespace unreal_fluid::physics::solid

// end of Plane.h