/***************************************************************
 * Copyright (C) 2023
 *    HSE SPb (Higher school of economics in Saint-Petersburg).
 ***************************************************************/

/* PROJECT   : UnrealFluidPhysics
 * AUTHORS   : Serkov Alexander, Daniil Vikulov, Daniil Martsenyuk, Vasily Lebedev
 * FILE NAME : SolidSphere.h
 * PURPOSE   : ISolid class
 *
 * No part of this file may be changed and used without agreement of
 * authors of this project.
 */
#pragma once

#include "../../../../utils/math/MathHeaders"

namespace unreal_fluid::physics::solid {
    struct Triangle {
        vec3f v1, v2, v3;

        Triangle(const vec3f &v1, const vec3f &v2, const vec3f &v3);
        ~Triangle() = default;


    };
}