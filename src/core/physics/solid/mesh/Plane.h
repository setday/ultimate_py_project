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
  class Plane : ISolid {
    double length, width;
    vec3 normal;

    Plane(double length, double widht, vec3 position, vec3 normal);
  };
} // namespace unreal_fluid::physics::solid

// end of Plane.h