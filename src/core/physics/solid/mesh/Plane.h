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
    double length, width;
    vec3 normal;

    void simulate(double dt) override{};

  public:
    Plane(double length, double width, vec3 position, vec3 normal);
    IPhysicalObject::Type getType() override;
    void *getData() override;
  };
} // namespace unreal_fluid::physics::solid

// end of Plane.h