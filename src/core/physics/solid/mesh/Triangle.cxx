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

#include "Triangle.h"

<<<<<<<< HEAD:src/core/physics/solid/mesh/Triangle.cxx
unreal_fluid::physics::solid::Triangle::Triangle(const vec3 &v1, const vec3 &v2, const vec3 &v3) : v1(v1), v2(v2), v3(v3) {}
========
#include "Vector3.h"
#include "Vector2.h"
#include "Operator.h"
#include "Matrix4x4.h"

using vec3 = unreal_fluid::math::Vector3<double>;
using vec3f = unreal_fluid::math::Vector3<float>;

using vec2 = unreal_fluid::math::Vector2<double>;
using vec2f = unreal_fluid::math::Vector2<float>;

using mat4 = unreal_fluid::math::Matrix4x4<float>;

//using intvec3 = unreal_fluid::math::Vector3<int>;
>>>>>>>> dev:src/utils/math/MathHeaders
