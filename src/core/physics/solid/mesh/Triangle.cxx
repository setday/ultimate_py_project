/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : Triangle.cxx
 * PURPOSE   : Triangle class implementation
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */

#include "Triangle.h"

using namespace unreal_fluid::physics::solid;

Triangle::Triangle(vec3f v1, vec3f v2, vec3f v3) : v1(v1),
                                                   v2(v2),
                                                   v3(v3) {}

// end of Triangle.cxx
