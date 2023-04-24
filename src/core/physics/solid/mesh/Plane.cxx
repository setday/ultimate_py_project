/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : ultimate_py_project
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Plane.cxx
 * PURPOSE   : class to create planes for bounding box
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "Plane.h"

using namespace unreal_fluid::physics::solid;

Plane::Plane(double length, double width, vec3 position, vec3 normal) : ISolid(position),
                                                                        width(width),
                                                                        length(length),
                                                                        normal(normal) {
}
